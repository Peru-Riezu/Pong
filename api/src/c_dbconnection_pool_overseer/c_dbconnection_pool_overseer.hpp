/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_dbconnection_pool_overseer.hpp                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/24 23:53:09                                            */
/*   Updated:  2024/08/06 04:42:26                                            */
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

class c_client_connection_handlers_overseer;
class c_io_uring_overseer;
class c_listening_socket_overseer;

extern c_client_connection_handlers_overseer *g_client_connection_handlers_overseer;
extern c_listening_socket_overseer           *g_listenning_socket_overseer;

class c_dbconnection_pool_overseer;
inline c_dbconnection_pool_overseer *g_dbconnection_pool_overseer = nullptr;

class c_dbconnection_pool_overseer
{
	private:
		class c_dbconnection;

		c_dbconnection *available_head;
		c_dbconnection *available_tail;
		int             available_request_slot_count = DBCONN_POOL_SIZE;
		int             must_retry_request_number = 0;
		int             must_retry_index[MAX_CONN_PER_WORKER];

	public:
		c_dbconnection_pool_overseer(void);
		~c_dbconnection_pool_overseer(void);

		void notify_ring_completion(struct io_uring_cqe *cqe);
		void make_request(char const *statement_name, char const **params, int param_number, int issuer_index);
		void notify_query_completion(void *result, int issuer_index);
		void send_retry_request_messages(void);
};

#pragma GCC diagnostic pop
