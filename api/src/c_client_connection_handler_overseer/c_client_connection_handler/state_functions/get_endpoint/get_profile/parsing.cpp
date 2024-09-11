/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parsing.cpp                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/21 21:17:53                                            */
/*   Updated:  2024/09/09 12:38:06                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../../c_client_connection_handler.hpp"
#include "../../../decode_query_params.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <optional>

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

void c_client_connection_handlers_overseer::c_client_connection_handler::get_endpoint::get_profile::parsing(
	c_client_connection_handler *t)
{

	s_fcgi_params *const     request_params = t->get_memory_for_params_from_shared_mem();
	c_token                  name_value;
	c_token                  session_token;
	c_token                  subject_name;
	std::optional<uint64_t>  decoded_name_value;
	std::optional<c_uint256> decoded_session_token;
	std::optional<uint64_t>  decoded_subject_name;

	name_value = get_token_value(request_params->query_string.get_beginning(), request_params->query_string.get_end());
	if (name_value.is_valid() == false)
	{
		t->handle_malformed_request();
		return;
	}
	session_token = get_token_value(name_value.get_end() + 1, request_params->query_string.get_end());
	if (session_token.is_valid() == false)
	{
		t->handle_malformed_request();
		return;
	}
	subject_name = get_token_value(session_token.get_end() + 1, request_params->query_string.get_end());
	if (subject_name.is_valid() == false)
	{
		t->handle_malformed_request();
		return;
	}
	decoded_name_value = decode_7_numeral(name_value);
	decoded_session_token = decode_44_numeral(session_token);
	decoded_subject_name = decode_7_numeral(subject_name);
	if (decoded_name_value.has_value() == false || decoded_session_token.has_value() == false ||
		decoded_subject_name.has_value() == false)
	{
		t->handle_malformed_request();
		return;
	}
	std::cerr << "here\n";
}

#pragma GCC diagnostic pop
