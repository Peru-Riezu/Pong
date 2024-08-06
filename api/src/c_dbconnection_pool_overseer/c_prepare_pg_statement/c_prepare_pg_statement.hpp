/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_prepare_pg_statement.hpp                                     */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/09 17:27:36                                            */
/*   Updated:  2024/08/06 03:42:50                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <postgresql/libpq-fe.h>
#include <vector>

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
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
;

class c_prepare_pg_statement
{
	private:
		static inline std::vector<char const *> statement_names = {"noop"};
		static inline std::vector<char const *> statements = {""};
		static inline std::vector<int>          param_numbers = {0};

	public:
		c_prepare_pg_statement(char const *statement_name, char const *statement, int param_number)
		{
			statement_names.push_back(statement_name);
			statements.push_back(statement);
			param_numbers.push_back(param_number);
		}

		static void c_prepare_pg_statement_destructor(void)
		{
			statements.clear();
			param_numbers.clear();
			statement_names.shrink_to_fit();
			statements.shrink_to_fit();
			param_numbers.shrink_to_fit();
		}

		static PGresult *get_result_of_statement_preparaitions(PGconn *conn)
		{
			for (size_t i = 0; true; i++)
			{
				PGresult *res = PQprepare(conn, statement_names[i], statements[i], param_numbers[i], nullptr);
				i++;
				if (PQresultStatus(res) != PGRES_COMMAND_OK || i == statement_names.size())
				{
					return (res);
				}
				PQclear(res);
			}
		}
};

#pragma GCC diagnostic pop
