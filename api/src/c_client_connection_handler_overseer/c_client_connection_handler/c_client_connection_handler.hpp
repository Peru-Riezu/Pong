/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler.hpp                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/24 16:25:15                                            */
/*   Updated:  2024/08/10 21:12:51                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../c_client_connection_handler_overseer.hpp"
#include "../c_token/c_token.hpp"
#include <cstdint>

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
class c_io_uring_overseer;

class c_client_connection_handlers_overseer::c_client_connection_handler
{
	private:
		typedef int                  t_e_handler_state;

		c_client_connection_handler *next_available;
		t_e_handler_state            current_state;
		unsigned int                 index;
		unsigned int                 memory_held_by_the_codec; // starts at memory_shared_with_the_ring
		unsigned int memory_held_by_the_handler; // starts at memory_shared_with_the_ring - memory_held_by_the_handler
		uint8_t     *memory_shared_with_the_ring;

// all posible paramters of all endpoint in a union
#include "u_params.hpp" // yea, it's an include amid a class definition, don't question my methods
		u_params params;

		struct s_fcgi_params
		{
				c_token request_method;
				c_token fastcgi_script_name;
				c_token query_string;
				c_token content_length;
		};

	public:
		c_client_connection_handler *get_next_available(void) const;
		unsigned int                 get_index(void) const;

		void                         set_next_available(c_client_connection_handler *next_available_exemplum);
		void                         set_index(unsigned int index_exemplum);
		void                         set_memory_shared_with_the_ring(uint8_t *memory_shared_with_the_ring_exemplum);
		void                         set_current_state(t_e_handler_state current_state_exemplum);
		void                         notify_io_completion(struct io_uring_cqe *cqe);
		void                         notify_query_completion(void *result);
		void                         parse_headers_and_get_new_state(void);


		void                         waiting_for_connection(struct io_uring_cqe *cqe)

		// all posible client_connection_handler states in a enum
		struct e_handler_state;


};

#pragma GCC diagnostic pop
