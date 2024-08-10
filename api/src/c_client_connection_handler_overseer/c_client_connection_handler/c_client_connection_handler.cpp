/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler.cpp                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/06 01:11:55                                            */
/*   Updated:  2024/08/10 21:02:14                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_client_connection_handler.hpp"
#include "../../api.hpp"
#include "../../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "e_handler_state.hpp"
// #include "fcgi_defs.hpp"
#include <cassert>
#include <cstdint>
#include <liburing.h>
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
#pragma GCC diagnostic ignored "-Wswitch-default"
;

void c_client_connection_handlers_overseer::c_client_connection_handler::set_index(unsigned int index_exemplum)
{
	index = index_exemplum;
}

void c_client_connection_handlers_overseer::c_client_connection_handler::set_next_available(
	c_client_connection_handler *next_available_exemplum)
{
	next_available = next_available_exemplum;
}

c_client_connection_handlers_overseer::c_client_connection_handler *
	c_client_connection_handlers_overseer::c_client_connection_handler::get_next_available(void) const
{
	return (next_available);
}

unsigned int c_client_connection_handlers_overseer::c_client_connection_handler::get_index(void) const
{
	return (index);
}

void c_client_connection_handlers_overseer::c_client_connection_handler::set_memory_shared_with_the_ring(
	uint8_t *memory_shared_with_the_ring_exemplum)
{
	memory_shared_with_the_ring = memory_shared_with_the_ring_exemplum;
}

void c_client_connection_handlers_overseer::c_client_connection_handler::set_current_state(
	t_e_handler_state current_state_exemplum)
{
	current_state = current_state_exemplum;
}

void c_client_connection_handlers_overseer::c_client_connection_handler::waiting_for_connection(struct io_uring_cqe *cqe)
{
	struct io_uring_sqe *sqe;

	current_state = e_handler_state::waiting_for_headers;
	sqe = g_io_uring_overseer->get_sqe();
	assert(sqe != nullptr);
	io_uring_prep_read_fixed(sqe, static_cast<int>(index), memory_shared_with_the_ring, MEM_PER_CONN, 0, 0);
	sqe->flags |= IOSQE_FIXED_FILE;
	sqe->user_data = index;
	available_head = next_available;
}

void c_client_connection_handlers_overseer::c_client_connection_handler::notify_io_completion(struct io_uring_cqe *cqe)
{

	switch (current_state)
	{
		case (e_handler_state::waiting_for_connection):
		{
			break;
		}
		case (e_handler_state::waiting_for_headers):
		{
			// write(STDOUT_FILENO, memory_shared_with_the_ring, static_cast<size_t>(cqe->res));
			// write(STDOUT_FILENO, "\n", 1);
		}
	}
}

#pragma GCC diagnostic pop
