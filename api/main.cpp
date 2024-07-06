/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.cpp                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/05 23:46:55                                            */
/*   Updated:  2024/07/06 05:14:07                                            */
/*                                                                            */
/* ************************************************************************** */

#include "/usr/include/postgresql/libpq-fe.h"
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#define NO_EXPAND_DBNAME  0
#define RESULTS_IN_TEXT   0
#define RESULTS_IN_BINARY 1

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


//	res = PQexecParams(dbconnection, "update user_t set session_token = $1::char(32) where name = $2::char(7);", 2,
//				   nullptr, (char *[]){"42", ""}, nullptr, nullptr, RESULTS_IN_TEXT);
//	res = PQexecParams(dbconnection, "select * from user_t;", 0, nullptr, nullptr, nullptr, nullptr, RESULTS_IN_TEXT);
//	if (PQresultStatus(res) != PGRES_TUPLES_OK)
//	{
//		std::cerr << "Database command failed: " << PQresultErrorMessage(res);
//	}
//	result_to_terminal(res);
//	PQclear(res);

int main(int argc, char **argv)
{
	PGconn *const dbconnection =
		PQconnectdbParams((char *[]){"dbname", nullptr}, (char *[]){"db", nullptr}, NO_EXPAND_DBNAME);

	if (argc != 2)
	{
		std::cerr << "Usage: ./api resource_uri\n";
	}
	if (dbconnection == nullptr)
	{
		std::cerr << "Api could not connect to the database: not enough memory left on device\n";
	}
	if (PQstatus(dbconnection) != CONNECTION_OK)
	{
		std::cerr << "Api could not connect to the database: " << PQerrorMessage(dbconnection);
	}
	
	return (EXIT_FAILURE);
}

#pragma GCC diagnostic pop
