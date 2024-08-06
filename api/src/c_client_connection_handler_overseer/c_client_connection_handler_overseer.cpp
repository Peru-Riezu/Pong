/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler_overseer.cpp                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/03 18:46:47                                            */
/*   Updated:  2024/08/06 04:53:37                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_client_connection_handler_overseer.hpp"
#include "../api.hpp"
#include "../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../c_worker_id_to_text.hpp"
#include "../internal_strerror.hpp"
#include "c_client_connection_handler/c_client_connection_handler.hpp"
#include <cstdlib>
#include <iostream>

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

c_client_connection_handlers_overseer::c_client_connection_handlers_overseer(void)
{
	available_head = reinterpret_cast<c_client_connection_handler *>(
		calloc(MAX_CONN_PER_WORKER, sizeof(c_client_connection_handler)));
	if (available_head == nullptr)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" +
						 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to allocate the connection handlers: " + internal_strerror(errno);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	available_tail = available_head + MAX_CONN_PER_WORKER - 1;
	for (size_t i = 0; i < MAX_CONN_PER_WORKER; i++)
	{
		available_head[i].set_index(static_cast<int>(i));
		available_head[i].set_next_available(&available_head[i + 1]);
		available_head[i].set_memory_shared_with_the_ring(g_io_uring_overseer->get_shared_buffer() + i * MEM_PER_CONN);
		available_head[i].set_current_state(c_client_connection_handler::e_handler_state::waiting_for_connection);
	}
	available_tail->set_next_available(nullptr);
	g_client_connection_handlers_overseer = this;
}

c_client_connection_handlers_overseer::~c_client_connection_handlers_overseer(void)
{
}

#pragma GCC diagnostic pop
