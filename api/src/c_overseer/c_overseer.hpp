/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_overseer.hpp                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/14 12:28:12                                            */
/*   Updated:  2024/07/14 15:59:20                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../api.hpp"
#include <postgresql/libpq-fe.h>
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

class c_overseer
{
	private:
		static inline c_overseer      *listenning_socket_overseer;
		static inline c_overseer      *dbconnection_overseer;
		static inline PGconn          *dbconnection; 
		static inline c_overseer      *aviable_head;
		static inline c_overseer      *aviable_tail;
		static inline struct io_uring *ring;
		static inline int             completion_ring_aviable_entries = CQ_SIZE;
		static inline int             submisioin_ring_aviable_entries = SQ_SIZE;
		c_overseer                    *next_aviable;
		int                            relative_index;
		t_e_state                      current_state;
		uint8_t                       *memory_shared_whit_ring;

	public:
		void set_new_state(t_e_state new_state);
		void set_memory_shared_whit_ring(uint8_t *memory);
		void set_relative_index(int index);
		void set_next_avialbe(c_overseer *overseer);
		void make_aviable(void);
		void notify_db_result(void *res);
		void notify_ring_result(struct io_uring_cqe *cqe, c_overseer *overseers);
		static void notify_pipeline_not_empty(void);
		static void set_listenning_socket_overseer(c_overseer *overseer);
		static void set_dbconnection_overseer(c_overseer *overseer);
		static void set_dbconnection(PGconn *dbconnection_exemplum);
		static void set_ring(struct io_uring *ring_exemplum);
		static void set_aviable_head(c_overseer *overseer);
		static void set_aviable_tail(c_overseer *overseer);
};

#pragma GCC diagnostic pop
