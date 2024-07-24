/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_dbconnection.hpp                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/25 00:16:54                                            */
/*   Updated:  2024/07/25 01:06:07                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <postgresql/libpq-fe.h>

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

class c_io_uring_overseer;
extern c_io_uring_overseer                   *g_io_uring_overseer;

class c_dbconnection
{
	private:
		typedef int t_e_dbconnection_state;

		t_e_dbconnection_state       current_state;
		c_dbconnection               *next_aviable;
		PGconn                       *dbconnection;
		int                           index;
		int                           reques_issuer_index;

	public:
		c_dbconnection *get_next_aviable(void) const;
		int get_index(void) const;

		void set_next_aviable(c_dbconnection *next_aviable_exemplum);
		void set_dbconnection(PGconn *dbconnection_exemplum);
		void set_index(PGconn *index_exemplum);
		void notify_query_assigned(char const *statement_name, char const **params, int param_number, int issuer_index);
		void notify_io_commpletion(struct io_uring_cqe *completion);
};

#pragma GCC diagnostic pop
