/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: handlers.cpp                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/08 13:39:29                                            */
/*   Updated:  2024/07/08 17:42:37                                            */
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

void get_profile_handler(char *buffer)
{
	std::cout << "get_profile_handler called \n";
}

void get_group_subscriptions_handler(char *buffer)
{
	std::cout << "get_group_subscriptions_handler called \n";
}

void get_tournament_subscriptions_handler(char *buffer)
{
	std::cout << "get_tournament_subscriptions_handler called \n";
}

void get_contacts_handler(char *buffer)
{
	std::cout << "get_contacts_handler called \n";
}

void get_match_history_handler(char *buffer)
{
	std::cout << "get_match_history_handler called \n";
}

void get_messages_handler(char *buffer)
{
	std::cout << "get_messages_handler called \n";
}

void get_group_messages_handler(char *buffer)
{
	std::cout << "get_group_messages_handler called \n";
}

void get_match_events_handler(char *buffer)
{
	std::cout << "get_match_events_handler called \n";
}

void get_pending_messages_handler(char *buffer)
{
	std::cout << "get_pending_messages_handler called \n";
}

void get_pending_match_events_handler(char *buffer)
{
	std::cout << "get_pending_match_events_handler called \n";
}

#pragma GCC diagnostic pop
