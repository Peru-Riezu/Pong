/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_io_uring_overseer.hpp                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/24 23:16:50                                            */
/*   Updated:  2024/07/25 00:14:21                                            */
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

class c_listenning_socket_overseer;
class c_dbconnection_pool_overseer;
class c_client_connection_handlers_overseer;

extern c_listenning_socket_overseer          *g_listenning_socket_overseer;
extern c_dbconnection_pool_overseer          *g_dbconnection_pool_overseer;
extern c_client_connection_handlers_overseer *g_client_connection_handlers_overseer;

class c_io_uring_overseer;
inline c_io_uring_overseer *g_io_uring_overseer = nullptr;

class c_io_uring_overseer
{
	private:
		struct io_uring *ring;

	public:
		c_io_uring_overseer(void);
		~c_io_uring_overseer(void);

		void make_request(struct io_usring_sqe *sqe);
		void start_loop(void);
};

#pragma GCC diagnostic pop
