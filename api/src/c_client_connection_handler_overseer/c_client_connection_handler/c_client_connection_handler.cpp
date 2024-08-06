/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler.cpp                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/06 01:11:55                                            */
/*   Updated:  2024/08/06 04:54:21                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_client_connection_handler.hpp"

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

void c_client_connection_handlers_overseer::c_client_connection_handler::set_index(int index_exemplum)
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

int c_client_connection_handlers_overseer::c_client_connection_handler::get_index(void) const
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

#pragma GCC diagnostic pop
