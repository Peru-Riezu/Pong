/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_dbconnection_pool_overseer.cpp                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/03 22:31:54                                            */
/*   Updated:  2024/08/06 03:15:24                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_dbconnection_pool_overseer.hpp"
#include "../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../c_worker_id_to_text.hpp"
#include "../internal_strerror.hpp"
#include "c_dbconnection/c_dbconnection.hpp"
#include "c_prepare_pg_statement/c_prepare_pg_statement.hpp"
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <stdlib.h>
#include <string>

;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wwritable-strings"
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#pragma GCC diagnostic ignored "-Wpre-c++20-compat-pedantic"
#pragma GCC diagnostic ignored "-Wc++20-designator"
#pragma GCC diagnostic ignored "-Wc++98-compat-extra-semi"
#pragma GCC diagnostic ignored "-Wc99-extensions"
;

static PGconn *new_dbconnection(void)
{
	PGconn *const dbconnection = PQconnectdbParams((char *[]){"host", "dbname", nullptr},
												   (char *[]){"/var/run/pong_db", "pongdb", nullptr}, NO_EXPAND_DBNAME);
	int           status;
	PGresult     *res;

	if (dbconnection == nullptr)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "could not connect to the database: not enough memory left on device\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	if (PQstatus(dbconnection) != CONNECTION_OK)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "could not connect to the database: " + PQerrorMessage(dbconnection);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = c_prepare_pg_statement::get_result_of_statement_preparaitions(
		dbconnection); // a little bit hacky but
					   // this allows us to prepare statements through global constructors
	status = PQresultStatus(res);
	if (status != PGRES_COMMAND_OK)
	{
		if (status == PGRES_BAD_RESPONSE)
		{
			std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
							 c_worker_id_to_text::get_name_from_id(worker_id) +
							 "\nMESSAGE=" + "internal database error\n";
		}
		else
		{
			std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
							 c_worker_id_to_text::get_name_from_id(worker_id) +
							 "\nMESSAGE=" + "prepare statement failed: "
					  << PQresultErrorMessage(res);
		}
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	PQclear(res);
	if (PQsetnonblocking(dbconnection, 1) == -1) // set connection to nonblocking mode
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + ":failed to set database connection to nonblocking mode\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (dbconnection);
}

c_dbconnection_pool_overseer::c_dbconnection_pool_overseer(void)
{
	aviable_head = reinterpret_cast<c_dbconnection *>(calloc(DBCONN_POOL_SIZE, sizeof(c_dbconnection)));
	if (aviable_head == nullptr)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to allocate memory for the dbconnections: " + internal_strerror(errno);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	aviable_tail = aviable_head + DBCONN_POOL_SIZE - 1;
	for (unsigned int i = 0; i < DBCONN_POOL_SIZE; i++)
	{
		aviable_head[i].set_next_aviable(&aviable_head[i + 1]);
		aviable_head[i].set_current_state(c_dbconnection::e_dbconnection_state::waiting_for_request);
		aviable_head[i].set_dbconnection(new_dbconnection());
		g_io_uring_overseer->register_file(PQsocket(aviable_head[i].get_dbconnection()), i + 1);
		aviable_head[i].set_index(i);
	}
	c_prepare_pg_statement::c_prepare_pg_statement_destructor();
	aviable_tail->set_next_aviable(nullptr);
	g_dbconnection_pool_overseer = this;
}

c_dbconnection_pool_overseer::~c_dbconnection_pool_overseer(void)
{
}

#pragma GCC diagnostic pop
