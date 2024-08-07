/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.cpp                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/05 23:46:55                                            */
/*   Updated:  2024/08/06 16:59:50                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_client_connection_handler_overseer/c_client_connection_handler_overseer.hpp"
#include "c_dbconnection_pool_overseer/c_dbconnection_pool_overseer.hpp"
#include "c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "c_listening_socket_overseer/c_listening_socket_overseer.hpp"

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
#pragma GCC diagnostic ignored "-Wc99-extensions"
#pragma GCC diagnostic ignored "-Wreserved-identifier"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
;

int main(void)
{
	c_io_uring_overseer                   io_uring_overseer;
	c_listening_socket_overseer           listening_socket_overseer;
	c_dbconnection_pool_overseer          dbconnection_pool_overseer;
	c_client_connection_handlers_overseer client_connection_handler_overseer;

	io_uring_overseer.start_loop();

	return (EXIT_SUCCESS);
}

#pragma GCC diagnostic pop
