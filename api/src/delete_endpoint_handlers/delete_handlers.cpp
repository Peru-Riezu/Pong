/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: delete_handlers.cpp                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/08 13:42:14                                            */
/*   Updated:  2024/07/08 17:42:23                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../api.hpp"
#include <iostream>

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

void delete_account_handler(char *buffer)
{
	std::cout << "delete_account_handler called \n";
}

void remove_contact_handler(char *buffer)
{
	std::cout << "remove_contact_handler called \n";
}

void unban_handler(char *buffer)
{
	std::cout << "unban_handler called \n";
}

void leave_group_chat_handler(char *buffer)
{
	std::cout << "leave_group_chat_handler called \n";
}

#pragma GCC diagnostic pop
