/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: handlers.cpp                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/08 13:36:46                                            */
/*   Updated:  2024/07/09 06:17:11                                            */
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

void set_session_token_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "set_session_token_handler called \n";
}

void set_nick_name_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "set_nick_name_handler called \n";
}

void set_profile_picture_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "set_profile_picture_handler called \n";
}

void set_bio_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "set_bio_handler called \n";
}

void set_password_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "set_password_handler called \n";
}

void invalidate_invite_to_group_chat_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "invalidate_invite_to_group_chat_handler called \n";
}

void invalidate_invite_to_match_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "invalidate_invite_to_match_handler called \n";
}

void invalidate_invite_to_tournament_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "invalidate_invite_to_tournament_handler called \n";
}

void accept_invite_to_group_chat_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "accept_invite_to_group_chat_handler called \n";
}

void accept_invite_to_tournament_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "accept_invite_to_tournament_handler called \n";
}

void accept_invite_to_match_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "accept_invite_to_match_handler called \n";
}

void leave_tournament_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "leave_tournament_handler called \n";
}

void send_direct_message_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "send_direct_message_handler called \n";
}

void send_group_message_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "send_group_message_handler called \n";
}

void send_match_events_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "send_match_events_handler called \n";
}

void acknowledge_direct_message_recived_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "acknowledge_direct_message_recived_handler called \n";
}

void acknowledge_direct_message_read_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "acknowledge_direct_message_read_handler called \n";
}

void acknowledge_group_message_read_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "acknowledge_group_message_read_handler called \n";
}

void promote_group_user_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "promote_group_user_handler called \n";
}

void demote_group_user_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	std::cout << "demote_group_user_handler called \n";
}

#pragma GCC diagnostic pop
