/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: waiting_for_connection.cpp                                     */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/16 12:03:54                                            */
/*   Updated:  2024/08/21 18:00:45                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../../api.hpp"
#include "../../../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../c_client_connection_handler.hpp"
#include "../e_handler_state.hpp"
#include "assert.h"

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

void c_client_connection_handlers_overseer::c_client_connection_handler::waiting_for_connection(
	struct io_uring_cqe __attribute__((unused)) * cqe)
{
	struct io_uring_sqe *sqe;

	sqe = g_io_uring_overseer->get_sqe();
	assert(sqe != nullptr);
	io_uring_prep_read_fixed(sqe, static_cast<int>(index), memory_shared_with_the_ring, MEM_PER_CONN, 0, 0);
	sqe->flags |= IOSQE_FIXED_FILE;
	sqe->user_data = index;
	available_head = next_available;
	current_state = e_handler_state::waiting_for_headers;
}

#pragma GCC diagnostic pop
