/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_dbconnection.cpp                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/06 01:01:41                                            */
/*   Updated:  2024/08/06 01:10:07                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_dbconnection.hpp"
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

void c_dbconnection_pool_overseer::c_dbconnection::set_next_aviable(c_dbconnection *next_aviable_exemplum)
{
	next_aviable = next_aviable_exemplum;
}

void c_dbconnection_pool_overseer::c_dbconnection::set_current_state(t_e_dbconnection_state current_state_exemplum)
{
	current_state = current_state_exemplum;
}

void c_dbconnection_pool_overseer::c_dbconnection::set_dbconnection(PGconn *dbconnection_exemplum)
{
	dbconnection = dbconnection_exemplum;
}

PGconn *c_dbconnection_pool_overseer::c_dbconnection::get_dbconnection(void) const
{
	return (dbconnection);
}

void c_dbconnection_pool_overseer::c_dbconnection::set_index(unsigned int index_exemplum)
{
	index = index_exemplum;
}

#pragma GCC diagnostic pop
