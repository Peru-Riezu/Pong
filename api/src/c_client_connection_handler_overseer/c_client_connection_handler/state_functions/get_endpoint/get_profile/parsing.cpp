/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parsing.cpp                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/21 21:17:53                                            */
/*   Updated:  2024/08/21 22:28:02                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../../c_client_connection_handler.hpp"
#include <cstdint>
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
	s_fcgi_params *const          request_params = t->get_memory_for_params_from_shared_mem();
	const c_token                 name_value = get_first_param_value(request_params->query_string);
	const c_token                 session_token = get_param_value(name_value);
	const c_token                 subject_name = get_param_value(session_token);
	const std::optional<uint64_t> decoded_name_value = decode_name_value(name_value);
	const std::optional<uint64_t> decoded_session_token = decode_session_token(session_token);
	const std::optional<uint64_t> decoded_subject_name = decode_subject_name(name_value);

	if ((name_value.is_valid() == false || session_token.is_valid() == false || subject_name.is_valid() == false)
		|| (name_value.get_size() != 7 || session_token.get_size() != 44 || subject_name.get_size() != 7)
		|| (decoded_name_value.has_value() == false || decoded_session_token.has_value() == false
			|| decoded_subject_name.has_value() == false))
	{
		t->handle_malformed_request();
		return;
	}

}

#pragma GCC diagnostic pop
