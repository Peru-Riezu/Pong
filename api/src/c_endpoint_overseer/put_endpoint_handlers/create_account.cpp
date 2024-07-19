/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: create_account.cpp                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/14 11:23:30                                            */
/*   Updated:  2024/07/19 19:10:43                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../c_prepare_pg_statement/c_prepare_pg_statement.hpp"

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
;

static c_prepare_pg_statement add_user_qry("add_user",
										   "insert into user_t (name, password, nick_name)"
										   "values ($1::char(7), $2::char(44), $3::varchar(30))",
										   3);

#pragma GCC diagnostic        pop
