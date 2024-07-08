/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: handlers.cpp                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/08 13:40:52                                            */
/*   Updated:  2024/07/08 17:42:55                                            */
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

void create_tournament_handler(char *buffer)
{
	std::cout << "create_tournament_handler called \n";
}

void create_group_chat_handler(char *buffer)
{
	std::cout << "create_group_chat_handler called \n";
}

void acknowledge_group_message_recived_handler(char *buffer)
{
	std::cout << "acknowledge_group_message_recived_handler called \n";
}

void ban_handler(char *buffer)
{
	std::cout << "ban_handler called \n";
}

void add_contact_handler(char *buffer)
{
	std::cout << "add_contact_handler called \n";
}

void create_account_handler(char *buffer)
{
	std::cout << "create_account_handler called \n";
}

void invite_to_group_chat_handler(char *buffer)
{
	std::cout << "invite_to_group_chat_handler called \n";
}

void invite_to_tournament_handler(char *buffer)
{
	std::cout << "invite_to_tournament_handler called \n";
}

void invite_to_match_handler(char *buffer)
{
	std::cout << "invite_to_match_handler called \n";
}

#pragma GCC diagnostic pop
