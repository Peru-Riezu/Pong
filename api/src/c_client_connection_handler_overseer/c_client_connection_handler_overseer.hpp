/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler_overseer.hpp                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/14 12:28:12                                            */
/*   Updated:  2024/08/07 03:56:29                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

class c_listening_socket_overseer;
class c_dbconnection_pool_overseer;
class c_io_uring_overseer;

extern c_listening_socket_overseer  *g_listenning_socket_overseer;
extern c_dbconnection_pool_overseer *g_dbconnection_pool_overseer;
extern c_io_uring_overseer          *g_io_uring_overseer;

class c_client_connection_handlers_overseer;
inline c_client_connection_handlers_overseer *g_client_connection_handlers_overseer = nullptr;

class c_client_connection_handlers_overseer
{
	private:
		class c_client_connection_handler;

		c_client_connection_handler *handler_array;
		static inline c_client_connection_handler *available_head;
		static inline c_client_connection_handler *available_tail;

	public:
		c_client_connection_handlers_overseer(void);
		~c_client_connection_handlers_overseer(void);

		void         notify_handler_free(c_client_connection_handler *handler);
		void         notify_completion(struct io_uring_cqe *cqe);
		void         notify_query_completion(void *result, unsigned int original_issuer_index);
		int unsigned get_next_connection_handler_index(void) const;
};

#pragma GCC diagnostic pop
