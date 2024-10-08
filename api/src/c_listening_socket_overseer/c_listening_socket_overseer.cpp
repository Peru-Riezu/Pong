/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_listening_socket_overseer.cpp                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/03 03:49:19                                            */
/*   Updated:  2024/08/12 06:25:25                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_listening_socket_overseer.hpp"
#include "../c_client_connection_handler_overseer/c_client_connection_handler_overseer.hpp"
#include "../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../c_worker_id_to_text.hpp"
#include "../internal_strerror.hpp"
#include <asm-generic/socket.h>
#include <cassert>
#include <iostream>
#include <limits.h>
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
;

c_listening_socket_overseer::c_listening_socket_overseer(void)
{
	int const          listening_sock = socket(AF_UNIX, SOCK_STREAM, AF_UNIX);
	struct sockaddr_un server_addr;
	int const          slen = sizeof(server_addr);

	if (listening_sock == -1)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" +
						 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to create listening socket: " + internal_strerror(errno);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, c_worker_id_to_text::get_socket_name_from_id(worker_id));
	unlink(c_worker_id_to_text::get_socket_name_from_id(worker_id));
	if (bind(listening_sock, reinterpret_cast<struct sockaddr *>(&server_addr), slen) == -1)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" +
						 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) + "\nMESSAGE=" +
						 "failed to bind listening socket to the file system: " + internal_strerror(errno);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	if (listen(listening_sock, INT_MAX) == -1)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" +
						 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to beginning listening in api socket: " + internal_strerror(errno);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	g_io_uring_overseer->register_file(listening_sock, 0);
	close(listening_sock);
	g_listening_socket_overseer = this;
}

void c_listening_socket_overseer::notify_completion(struct io_uring_cqe *cqe)
{
	struct io_uring_sqe *sqe;

	if (cqe->res < 0)
	{
		std::cerr << std::string("PRIORITY=4\n") + "SYSLOG_FACILITY=3\n" +
						 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=accept failed: " + " " + internal_strerror(-cqe->res);
		sqe = g_io_uring_overseer->get_sqe();
		assert(sqe != nullptr);
		io_uring_prep_accept_direct(sqe, 0, nullptr, nullptr, 0,
									c_client_connection_handlers_overseer::get_next_connection_handler_index());
		sqe->flags |= IOSQE_FIXED_FILE;
		sqe->user_data = 0;
		return;
	}
	available_handler_count--;
	cqe->user_data = c_client_connection_handlers_overseer::get_next_connection_handler_index();
	g_client_connection_handlers_overseer->notify_completion(cqe);
	if (available_handler_count > 0)
	{
		sqe = g_io_uring_overseer->get_sqe();
		assert(sqe != nullptr);
		io_uring_prep_accept_direct(sqe, 0, nullptr, nullptr, 0,
									c_client_connection_handlers_overseer::get_next_connection_handler_index());
		sqe->flags |= IOSQE_FIXED_FILE;
		sqe->user_data = 0;
	}
}

void c_listening_socket_overseer::inform_connection_handler_freed(void)
{
	struct io_uring_sqe *sqe;

	available_handler_count++;
	if (available_handler_count == 1)
	{
		sqe = g_io_uring_overseer->get_sqe();
		assert(sqe != nullptr);
		io_uring_prep_accept_direct(sqe, 0, nullptr, nullptr, 0,
									c_client_connection_handlers_overseer::get_next_connection_handler_index());
		sqe->flags |= IOSQE_FIXED_FILE;
		sqe->user_data = 0;
	}
}

c_listening_socket_overseer::~c_listening_socket_overseer(void)
{
}

#pragma GCC diagnostic pop
