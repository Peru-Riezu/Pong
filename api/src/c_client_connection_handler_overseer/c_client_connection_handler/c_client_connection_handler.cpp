/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler.cpp                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/06 01:11:55                                            */
/*   Updated:  2024/08/21 21:29:45                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_client_connection_handler.hpp"
#include "../../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../../c_listening_socket_overseer/c_listening_socket_overseer.hpp"
#include "e_handler_state.hpp"
#include "fcgi_defs.hpp"
#include <cassert>
#include <cstdint>
#include <cstring>
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
#pragma GCC diagnostic ignored "-Wc99-designator"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
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

void c_client_connection_handlers_overseer::c_client_connection_handler::close_connection(
	c_client_connection_handler *t)
{
	struct io_uring_sqe *sqe;

	sqe = g_io_uring_overseer->get_sqe();
	assert(sqe != nullptr);
	io_uring_prep_close_direct(sqe, t->index);
	sqe->user_data = t->index;
	t->current_state = e_handler_state::waiting_for_close_completion;
}

void c_client_connection_handlers_overseer::c_client_connection_handler::handle_malformed_request(void)
{
	struct io_uring_sqe *sqe;
	char const          *response = "Status: 400 Bad Request\r\n\r\n";
	s_fcgi_header       *begin_stdout_header = reinterpret_cast<s_fcgi_header *>(memory_shared_with_the_ring);
	s_fcgi_header       *end_stdout_header =
		reinterpret_cast<s_fcgi_header *>(memory_shared_with_the_ring + strlen(response) + FCGI_HEADER_LEN);
	s_fcgi_end_request_record *end_request_record = reinterpret_cast<s_fcgi_end_request_record *>(
		memory_shared_with_the_ring + strlen(response) + static_cast<uintptr_t>(FCGI_HEADER_LEN * 2));

	pending_write_size =
		static_cast<unsigned int>(strlen(response)) + FCGI_HEADER_LEN * 2 + sizeof(s_fcgi_end_request_record);

	*begin_stdout_header = s_fcgi_header{.version = 1,
										 .type = FCGI_STDOUT,
										 .request_id_b1 = 0,
										 .request_id_b0 = 1,
										 .content_length_b1 = 0,
										 .content_length_b0 = static_cast<unsigned char>(strlen(response)),
										 .padding_length = 0};
	*end_stdout_header = s_fcgi_header{.version = 1,
									   .type = FCGI_STDOUT,
									   .request_id_b1 = 0,
									   .request_id_b0 = 1,
									   .content_length_b1 = 0,
									   .content_length_b0 = 0,
									   .padding_length = 0};
	*end_request_record = s_fcgi_end_request_record{.header.version = 1,
													.header.type = FCGI_END_REQUEST,
													.header.request_id_b1 = 0,
													.header.request_id_b0 = 1,
													.header.content_length_b1 = 0,
													.header.content_length_b0 = sizeof(s_fcgi_end_request_body),
													.header.padding_length = 0,
													.body.app_status_b3 = 0,
													.body.app_status_b2 = 0,
													.body.app_status_b1 = 0,
													.body.app_status_b0 = 0,
													.body.protocol_status = 0};
	memory_held_by_the_handler = 0;
	memory_held_by_the_codec = 0;
	next_sate = e_handler_state::closing;
	memcpy(memory_shared_with_the_ring + FCGI_HEADER_LEN, response, strlen(response));
	sqe = g_io_uring_overseer->get_sqe();
	assert(sqe != nullptr);
	io_uring_prep_send(sqe, static_cast<int>(index), memory_shared_with_the_ring, pending_write_size, 0);
	sqe->flags |= IOSQE_FIXED_FILE;
	sqe->flags |= IORING_RECVSEND_FIXED_BUF;
	sqe->buf_index = 0;
	sqe->user_data = index;
	current_state = e_handler_state::waiting_for_write_completion;
}

void c_client_connection_handlers_overseer::c_client_connection_handler::notify_io_completion(struct io_uring_cqe *cqe)
{
	void (c_client_connection_handler::*table[])(struct io_uring_cqe *cqe) = {
		[e_handler_state::waiting_for_connection] = &c_client_connection_handler::waiting_for_connection,
		[e_handler_state::waiting_for_headers] = &c_client_connection_handler::waiting_for_headers,
		[e_handler_state::waiting_for_close_completion] = &c_client_connection_handler::waiting_for_close,
		[e_handler_state::waiting_for_write_completion] = &c_client_connection_handler::waiting_for_write_completion};

	(this->*table[current_state])(cqe);
}

void c_client_connection_handlers_overseer::c_client_connection_handler::notify_internal_step_completion(void)
{
	void (*table[])(c_client_connection_handler *) = {
		[e_handler_state::closing] = &c_client_connection_handler::close_connection,
		[e_handler_state::get_endpoint::get_profile::parsing] =
			&c_client_connection_handler::get_endpoint::get_profile::parsing};

	table[next_sate](this);
}

#pragma GCC diagnostic pop
