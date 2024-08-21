/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: waiting_for_headers.cpp                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/16 12:21:23                                            */
/*   Updated:  2024/08/21 21:34:18                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../../api.hpp"
#include "../../../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../../../c_worker_id_to_text.hpp"
#include "../../../internal_strerror.hpp"
#include "../c_client_connection_handler.hpp"
#include "../e_handler_state.hpp"
#include "../fcgi_defs.hpp"
#include "assert.h"
#include <cstddef>
#include <cstdint>
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

static s_fcgi_begin_request_record *get_beginning_record_from_shared_mem(uint8_t *memory_shared_with_the_ring)
{
	return (reinterpret_cast<s_fcgi_begin_request_record *>(memory_shared_with_the_ring));
}

static s_fcgi_params_record *get_param_records_from_begin_record(s_fcgi_begin_request_record *begin_record)
{
	return (reinterpret_cast<s_fcgi_params_record *>(reinterpret_cast<uint8_t *>(begin_record) +
													 sizeof(s_fcgi_begin_request_record) +
													 begin_record->header.padding_length));
}

static s_fcgi_name_value_pair *get_name_value_pair_from_params_record(s_fcgi_params_record *params_record)
{
	return (reinterpret_cast<s_fcgi_name_value_pair *>(reinterpret_cast<uint8_t *>(params_record) +
													   sizeof(s_fcgi_params_record)));
}

static c_token get_value_as_token_from_name_value_pair(s_fcgi_name_value_pair const *sizes)
{
	return (c_token{reinterpret_cast<char const *>(reinterpret_cast<uint8_t const *>(sizes) +
												   sizeof(s_fcgi_name_value_pair) + sizes->name_length_b0),
					reinterpret_cast<char const *>(reinterpret_cast<uint8_t const *>(sizes) +
												   sizeof(s_fcgi_name_value_pair) + sizes->name_length_b0 +
												   sizes->value_length_b0 - 1)});
}

static s_fcgi_name_value_pair const *get_name_value_pair_from_token_end(char const *token_end)
{
	return (reinterpret_cast<s_fcgi_name_value_pair const *>(token_end + 1));
}

static s_fcgi_params_record const *get_param_records_from_previus_record(s_fcgi_params_record *params_record)
{
	return (reinterpret_cast<s_fcgi_params_record const *>(reinterpret_cast<uint8_t *>(params_record) +
														   params_record->get_size()));
}

static unsigned int get_memory_held_by_the_codec_after_flush(uint8_t                    *memory_shared_with_the_ring,
															 s_fcgi_params_record const *empty_params_record,
															 int                         read_size)
{
	return (
		static_cast<unsigned int>(read_size - (reinterpret_cast<uint8_t const *>(empty_params_record) +
											   empty_params_record->get_size() - 1 - memory_shared_with_the_ring + 1)));
}

c_client_connection_handlers_overseer::c_client_connection_handler::s_fcgi_params *
	c_client_connection_handlers_overseer::c_client_connection_handler::get_memory_for_params_from_shared_mem(
		void) const
{
	return (reinterpret_cast<s_fcgi_params *>(
		(memory_shared_with_the_ring + MEM_PER_CONN - sizeof(s_fcgi_params) - 1) -
		(reinterpret_cast<size_t>(memory_shared_with_the_ring + MEM_PER_CONN - sizeof(s_fcgi_params) - 1) %
		 alignof(s_fcgi_params))));
}

void c_client_connection_handlers_overseer::c_client_connection_handler::waiting_for_headers(struct io_uring_cqe *cqe)
{
	s_fcgi_params *const               request_params = get_memory_for_params_from_shared_mem();
	s_fcgi_begin_request_record *const begin_record = get_beginning_record_from_shared_mem(memory_shared_with_the_ring);
	s_fcgi_params_record *const        params_record = get_param_records_from_begin_record(begin_record);
	s_fcgi_name_value_pair *const      sizes1 = get_name_value_pair_from_params_record(params_record);
	c_token                            request_method = get_value_as_token_from_name_value_pair(sizes1);
	s_fcgi_name_value_pair const *const sizes2 = get_name_value_pair_from_token_end(request_method.get_end());
	c_token                             script_filename = get_value_as_token_from_name_value_pair(sizes2);
	s_fcgi_name_value_pair const *const sizes3 = get_name_value_pair_from_token_end(script_filename.get_end());
	c_token                             query_string = get_value_as_token_from_name_value_pair(sizes3);
	s_fcgi_name_value_pair const *const sizes4 = get_name_value_pair_from_token_end(query_string.get_end());
	c_token                             content_length = get_value_as_token_from_name_value_pair(sizes4);
	s_fcgi_params_record const *const   empty_params_record = get_param_records_from_previus_record(params_record);

	request_params->request_method = request_method;
	request_params->fastcgi_script_name = script_filename;
	request_params->query_string = query_string;
	request_params->content_length = content_length;
	memory_held_by_the_handler = static_cast<unsigned int>((memory_shared_with_the_ring + MEM_PER_CONN) -
														   reinterpret_cast<uint8_t *>(request_params));
	if (cqe->res <
		static_cast<int>(begin_record->get_size() + params_record->get_size() + empty_params_record->get_size()))
	{
		if (log_level >= LOG_INFO && cqe->res < 0)
		{
			std::cerr << std::string("PRIORITY=6\n") + "SYSLOG_FACILITY=3\n" +
							 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) +
							 "\nMESSAGE=" + "failed to accept connection: " + internal_strerror(errno);
		}
		close_connection(this);
		return;
	}
	if ((sizes1->value_length_b0 >= 128) || (sizes2->value_length_b0 >= 128) || (sizes3->value_length_b0 >= 128) ||
		(sizes4->value_length_b0 >= 128))
	{
		handle_malformed_request();
		return;
	}
	memory_held_by_the_codec =
		get_memory_held_by_the_codec_after_flush(memory_shared_with_the_ring, empty_params_record, cqe->res);
	if (memory_held_by_the_codec > 0)
	{
		memmove(memory_shared_with_the_ring, content_length.get_end(), memory_held_by_the_codec);
	}
	next_sate = parse_headers_and_get_new_state(request_params);
	if (next_sate == e_handler_state::invalid_state)
	{
		handle_malformed_request();
		return;
	}
	notify_internal_step_completion();
}

#pragma GCC diagnostic pop
