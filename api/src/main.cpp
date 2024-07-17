/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.cpp                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/05 23:46:55                                            */
/*   Updated:  2024/07/17 18:29:44                                            */
/*                                                                            */
/* ************************************************************************** */

#include "api.hpp"
#include "c_overseer/c_overseer.hpp"
#include "c_prepare_pg_statement/c_prepare_pg_statement.hpp"
#include "c_worker_id_to_text.hpp"
#include <asm-generic/socket.h>
#include <bits/types/struct_iovec.h>
#include <cctype>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <liburing.h>
#include <liburing/io_uring.h>
#include <postgresql/libpq-fe.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

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
#pragma GCC diagnostic ignored "-Wreserved-identifier"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
;

static PGconn *connect_to_database(int worker_id)
{
	int           status;
	PGresult     *res;
	PGconn *const dbconnection =
		PQconnectdbParams((char *[]){"dbname", nullptr}, (char *[]){"pongdb", nullptr}, NO_EXPAND_DBNAME);

	if (dbconnection == nullptr)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": could not connect to the database: not enough memory left on device\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	if (PQstatus(dbconnection) != CONNECTION_OK)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": could not connect to the database: " << PQerrorMessage(dbconnection);
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
			std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id)
					  << ": internal database error\n";
		}
		else
		{
			std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id)
					  << ": prepare statement failed: " << PQresultErrorMessage(res);
		}
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	PQclear(res);
	if (PQsetnonblocking(dbconnection, 1) == -1) // set connection to nonblocking mode
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ":failed to set database connection to nonblocking mode\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (dbconnection);
}

static int enlarge_connection_buffers_and_get_fd(PGconn *dbconnection, int worker_id)
{
	int const connection_fd = PQsocket(dbconnection);

	if (setsockopt(connection_fd, SOL_SOCKET, SO_SNDBUF, (int[]){DB_SOCK_WRITE_BUFF_SIZE}, sizeof(int)) == -1 ||
		setsockopt(connection_fd, SOL_SOCKET, SO_RCVBUF, (int[]){DB_SOCK_READ_BUFF_SIZE}, sizeof(int)) == -1)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": failed to increase database connection buffer sizes\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (connection_fd);
}

static int get_listening_socket(int worker_id)
{
	int const          listening_sock = socket(AF_UNIX, SOCK_STREAM, AF_UNIX);
	struct sockaddr_un server_addr;
	int const          slen = sizeof(server_addr);

	if (listening_sock == -1)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to create listening socket");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, c_worker_id_to_text::get_socket_name_from_id(worker_id));
	unlink(c_worker_id_to_text::get_socket_name_from_id(worker_id));
	if (bind(listening_sock, reinterpret_cast<struct sockaddr *>(&server_addr), slen) == -1)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to bind listening socket to the file system");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	if (listen(listening_sock, INT_MAX) == -1)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to beginning listening in api socket");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (listening_sock);
}

static struct io_uring get_ring(int dbconnection_fd, int listening_sock_fd, struct iovec shared_buffer, int worker_id)
{
	struct io_uring_params params = {
		.sq_entries = SQ_SIZE,
		.cq_entries = CQ_SIZE,
		.flags = IORING_SETUP_CQSIZE | IORING_SETUP_SUBMIT_ALL | IORING_SETUP_COOP_TASKRUN | IORING_SETUP_SINGLE_ISSUER,
	};
	struct io_uring ring;
	int             res;

	res = io_uring_queue_init_params(SQ_SIZE, &ring, &params);
	if (res < 0)
	{
		errno = -res;
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to create io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_ring_fd(&ring);
	if (res < 0)
	{
		errno = -res;
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to register io uring fd in io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_files_sparse(&ring, MAX_CONN_PER_WORKER);
	if (res < 0)
	{
		errno = -res;
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to register fd table io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_files_update(&ring, 0, (int[2]){dbconnection_fd, listening_sock_fd}, 2);
	if (res < 0)
	{
		errno = -res;
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to register the fd of the database connection in io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_buffers(&ring, &shared_buffer, 1);
	if (res < 0)
	{
		errno = -res;
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to register the shared buffers in io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (ring);
}

static struct iovec get_shared_buffer(int worker_id)
{
	struct iovec shared_buffer = {.iov_base = calloc(MAX_CONN_PER_WORKER, MEM_PER_CONN),
								  .iov_len = static_cast<size_t>(MAX_CONN_PER_WORKER) * MEM_PER_CONN};

	if (shared_buffer.iov_base == nullptr)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to allocate the shared buffer");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (shared_buffer);
}
static c_overseer *get_overseers(PGconn *dbconnection, struct io_uring *ring, void *shared_buffer, int worker_id)
{
	c_overseer *const  overseers = static_cast<c_overseer *>(calloc(API_WORKER_COUNT + 2, sizeof(c_overseer)));

	if (overseers == nullptr)
	{
		std::cerr << "daemon: err: " << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": failed to allocate the array of overseers");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
//	overseers[0].set_new_state(overseer_state::dbconnection::waiting_to_read_from_db);
	overseers[0].set_relative_index(0);
//	overseers[1].set_new_state(overseer_state::dbconnection::waiting_to_read_from_db);
	overseers[1].set_relative_index(1);
	c_overseer::set_listenning_socket_overseer(&overseers[1]);
	c_overseer::set_dbconnection_overseer(&overseers[0]);
	c_overseer::set_dbconnection(dbconnection);
	c_overseer::set_ring(ring);
	c_overseer::set_aviable_head(&overseers[2]);
	c_overseer::set_aviable_tail(&overseers[API_WORKER_COUNT - 1]);
	for (size_t i = 0; i < API_WORKER_COUNT; i++)
	{
		overseers[i + 2].set_memory_shared_whit_ring(static_cast<uint8_t *>(shared_buffer) + (i * MEM_PER_CONN));
		overseers[i + 2].set_relative_index(static_cast<int>(i) + 2);
		overseers[i + 2].set_next_avialbe(&overseers[i + 1 + 2]);
	}
	overseers[API_WORKER_COUNT - 1 + 2].set_next_avialbe(nullptr);
	return (overseers);
}

int main(void)
{
	int                worker_id = 1;
	PGconn *const      dbconnection = connect_to_database(worker_id);                                    // may exit
	int const          dbconnection_fd = enlarge_connection_buffers_and_get_fd(dbconnection, worker_id); // may exit
	int const          listening_sock_fd = get_listening_socket(worker_id);                              // may exit
	const struct iovec shared_buffer = get_shared_buffer(worker_id);                                     // may exit
	struct io_uring    ring = get_ring(dbconnection_fd, listening_sock_fd, shared_buffer, worker_id);    // may exit
	c_overseer *const  overseers = get_overseers(dbconnection, &ring, shared_buffer.iov_base, worker_id);

	pause();
	PQfinish(dbconnection);
	free(shared_buffer.iov_base);
	free(overseers);
	return (EXIT_SUCCESS);
}

#pragma GCC diagnostic pop
