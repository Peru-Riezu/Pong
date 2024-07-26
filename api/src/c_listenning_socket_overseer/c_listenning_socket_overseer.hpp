/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_listenning_socket_overseer.hpp                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/24 23:38:19                                            */
/*   Updated:  2024/07/27 01:54:39                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../api.hpp"

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

class c_dbconnection_pool_overseer;
class c_client_connection_handlers_overseer;
class c_io_uring_overseer;

extern c_dbconnection_pool_overseer          *g_dbconnection_pool_overseer;
extern c_client_connection_handlers_overseer *g_client_connection_handlers_overseer;
extern c_io_uring_overseer                   *g_io_uring_overseer;

class c_listenning_socket_overseer;
inline c_listenning_socket_overseer *g_listenning_socket_overseer = nullptr;

class c_listenning_socket_overseer
{
	private:
		int aviable_handler_count = MAX_CONN_PER_WORKER;

	public:
		c_listenning_socket_overseer(void); // io_uring_overseer must be constructed before this object is constructed
		~c_listenning_socket_overseer(void);

		void inform_connection_handler_freed(void);
		void notify_commpletion(struct io_uring_cqe *cqe);
};

#pragma GCC diagnostic pop
