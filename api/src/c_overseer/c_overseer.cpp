/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_overseer.cpp                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/14 13:12:43                                            */
/*   Updated:  2024/07/15 16:53:10                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_overseer.hpp"
#include <liburing.h>
#include <liburing/io_uring.h>

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

void c_overseer::set_new_state(t_e_state new_state)
{

}

void c_overseer::set_memory_shared_whit_ring(uint8_t *memory)
{
	memory_shared_whit_ring = memory;
}

void c_overseer::set_relative_index(int index)
{
	relative_index = index;
}

void c_overseer::set_next_avialbe(c_overseer *overseer)
{
	next_aviable = overseer;
}

void c_overseer::make_aviable(void)
{
	aviable_tail->next_aviable = this;
	aviable_tail = this;
	next_aviable = nullptr;
	if (listenning_socket_overseer->current_state == overseer_state::listenning_socket::waiting_for_closed_connections)
	{
		listenning_socket_overseer->current_state
			= overseer_state::listenning_socket::preparing_to_listen_for_connections;
//		listenning_socket_overseer->preparing_to_listen_for_connections();
	}
}

void c_overseer::notify_pipeline_not_empty(void)
{
//	switch (dbconnection_overseer->current_state)
//	{
//		case (overseer_state::dbconnection::waiting_to_read_from_db):
//		{
//			dbconnection_overseer->current_state = overseer_state::dbconnection::waiting_to_read_and_syncing_whit_db;
//			// there is no need to call the syncing_whit_db function as it will be done allways after all cqe have been
//			// processed
//			break;
//		}
//		case (overseer_state::dbconnection::waiting_to_read_and_write_from_db):
//		{
//			dbconnection_overseer->current_state =
//				overseer_state::dbconnection::waiting_to_read_write_and_syncing_whit_db;
//			break;
//		}
//		default: // nothing to do
//		{
//		}
//	}
}

void c_overseer::notify_db_result(void *res)
{

}

void c_overseer::notify_ring_result(struct io_uring_cqe *cqe, c_overseer *overseers)
{
	switch (overseers[static_cast<int>(cqe->user_data)].current_state)
	{
		case (overseer_state::listenning_socket::listenning_for_connections):
		{
//			overseers[static_cast<int>(cqe->user_data)].accept_connection();
			break;
		}
		case (overseer_state::closing_connection):
		{
			// on linux the fd is guarantied to be close regardles of the result of close
			// so there is no need to check it
			overseers[static_cast<int>(cqe->user_data)].make_aviable();
			break;
		}
		case (overseer_state::waiting_for_headers):
		{
			overseers[static_cast<int>(cqe->user_data)].current_state =
				parse_headers_and_get_new_state(
						reinterpret_cast<char *>(overseers[static_cast<int>(cqe->user_data)].memory_shared_whit_ring));
//			parse_query_params(static_cast<int>(cqe->user_data));
			break;
		}
//		case (overseer_state::dbconnection::waiting_to_read_and_write_from_db):
//		{
//			if ((cqe->user_data >> 32U) == 1)
//			{
//				overseers[static_cast<int>(cqe->user_data)].db_read_aviable();
//			}
//			else
//			{
//				overseers[static_cast<int>(cqe->user_data)].db_write_aviable();
//			}
//			break ;
//		}
//		case (overseer_state::dbconnection::waiting_to_read_from_db):
//		{
//			overseers[static_cast<int>(cqe->user_data)].db_read_aviable();
//			break;
//		}
	}
}

void c_overseer::set_listenning_socket_overseer(c_overseer *overseer)
{
	listenning_socket_overseer = overseer;
}

void c_overseer::set_dbconnection_overseer(c_overseer *overseer)
{
	dbconnection_overseer = overseer;
}

void c_overseer::set_dbconnection(PGconn *dbconnection_exemplum)
{
	dbconnection = dbconnection_exemplum;
}

void c_overseer::set_ring(struct io_uring *ring_exemplum)
{
	ring = ring_exemplum;
}

void c_overseer::set_aviable_head(c_overseer *overseer)
{
	aviable_head = overseer;
}

void c_overseer::set_aviable_tail(c_overseer *overseer)
{
	aviable_tail = overseer;
}

#pragma GCC diagnostic pop
