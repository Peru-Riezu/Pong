/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: waiting_for_close.cpp                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/16 17:18:50                                            */
/*   Updated:  2024/08/21 18:19:42                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../../../c_listening_socket_overseer/c_listening_socket_overseer.hpp"
#include "../c_client_connection_handler.hpp"
#include "../e_handler_state.hpp"

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

void c_client_connection_handlers_overseer::c_client_connection_handler::waiting_for_close(struct io_uring_cqe
																						   __attribute__((unused)) *
																						   cqe)
{
	available_tail->next_available = this;
	available_tail = this;
	next_available = nullptr;
	g_listening_socket_overseer->inform_connection_handler_freed();
	current_state = e_handler_state::waiting_for_connection;
}

#pragma GCC diagnostic pop
