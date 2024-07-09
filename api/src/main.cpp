/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.cpp                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/05 23:46:55                                            */
/*   Updated:  2024/07/09 18:25:19                                            */
/*                                                                            */
/* ************************************************************************** */

#include "api.hpp"
#include "c_prepare_pg_statement/c_prepare_pg_statement.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <postgresql/libpq-fe.h>
#include <stdexcept>
#include <unistd.h>
#include <utility>

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
#pragma GCC diagnostic ignored "-Wc99-extensions"
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
#pragma GCC diagnostic ignored "-Wreserved-identifier"
;

static c_token get_method_token(char const *buffer)
{
	char const *beginning;
	size_t      i;

	i = 0;
	while (isspace(buffer[i]) != 0)
	{
		i++;
	}
	beginning = &buffer[i];
	while (isupper(buffer[i]) != 0)
	{
		i++;
	}
	if (i == 0)
	{
		return (c_token(beginning, beginning));
	}
	return (c_token(beginning, &buffer[i - 1]));
}

static c_token get_endpoint_token(char const *buffer)
{
	char const *beginning;
	size_t      i;

	i = 0;
	while (isspace(buffer[i]) != 0)
	{
		i++;
	}
	beginning = &buffer[i];
	i++;
	while (islower(buffer[i]) != 0 || buffer[i] == '_')
	{
		i++;
	}
	if (i == 0)
	{
		return (c_token(beginning, beginning));
	}
	return (c_token(beginning, &buffer[i - 1]));
}

static void handle_request(char *buffer, PGconn *const dbconnection)
{
	static std::map<std::pair<c_token, c_token>, t_handler_function> const endpoint_to_handler = {
		{				 {c_token{"POST"}, c_token{"/set_session_token"}},                  set_session_token_handler},
		{					 {c_token{"POST"}, c_token{"/set_nick_name"}},                      set_nick_name_handler},
		{			   {c_token{"POST"}, c_token{"/set_profile_picture"}},                set_profile_picture_handler},
		{						   {c_token{"POST"}, c_token{"/set_bio"}},                            set_bio_handler},
		{					  {c_token{"POST"}, c_token{"/set_password"}},                       set_password_handler},
		{   {c_token{"POST"}, c_token{"/invalidate_invite_to_group_chat"}},    invalidate_invite_to_group_chat_handler},
		{        {c_token{"POST"}, c_token{"/invalidate_invite_to_match"}},         invalidate_invite_to_match_handler},
		{   {c_token{"POST"}, c_token{"/invalidate_invite_to_tournament"}},    invalidate_invite_to_tournament_handler},
		{       {c_token{"POST"}, c_token{"/accept_invite_to_group_chat"}},        accept_invite_to_group_chat_handler},
		{       {c_token{"POST"}, c_token{"/accept_invite_to_tournament"}},        accept_invite_to_tournament_handler},
		{			{c_token{"POST"}, c_token{"/accept_invite_to_match"}},             accept_invite_to_match_handler},
		{				  {c_token{"POST"}, c_token{"/leave_tournament"}},                   leave_tournament_handler},
		{			   {c_token{"POST"}, c_token{"/send_direct_message"}},                send_direct_message_handler},
		{				{c_token{"POST"}, c_token{"/send_group_message"}},                 send_group_message_handler},
		{				 {c_token{"POST"}, c_token{"/send_match_events"}},                  send_match_events_handler},
		{{c_token{"POST"}, c_token{"/acknowledge_direct_message_recived"}}, acknowledge_direct_message_recived_handler},
		{   {c_token{"POST"}, c_token{"/acknowledge_direct_message_read"}},    acknowledge_direct_message_read_handler},
		{    {c_token{"POST"}, c_token{"/acknowledge_group_message_read"}},     acknowledge_group_message_read_handler},
		{				{c_token{"POST"}, c_token{"/promote_group_user"}},                 promote_group_user_handler},
		{				 {c_token{"POST"}, c_token{"/demote_group_user"}},                  demote_group_user_handler},
		{						{c_token{"GET"}, c_token{"/get_profile"}},                        get_profile_handler},
		{			{c_token{"GET"}, c_token{"/get_group_subscriptions"}},            get_group_subscriptions_handler},
		{       {c_token{"GET"}, c_token{"/get_tournament_subscriptions"}},       get_tournament_subscriptions_handler},
		{					   {c_token{"GET"}, c_token{"/get_contacts"}},                       get_contacts_handler},
		{				  {c_token{"GET"}, c_token{"/get_match_history"}},                  get_match_history_handler},
		{					   {c_token{"GET"}, c_token{"/get_messages"}},                       get_messages_handler},
		{				 {c_token{"GET"}, c_token{"/get_group_messages"}},                 get_group_messages_handler},
		{				   {c_token{"GET"}, c_token{"/get_match_events"}},                   get_match_events_handler},
		{			   {c_token{"GET"}, c_token{"/get_pending_messages"}},               get_pending_messages_handler},
		{		   {c_token{"GET"}, c_token{"/get_pending_match_events"}},           get_pending_match_events_handler},
		{				  {c_token{"PUT"}, c_token{"/create_tournament"}},                  create_tournament_handler},
		{				  {c_token{"PUT"}, c_token{"/create_group_chat"}},                  create_group_chat_handler},
		{  {c_token{"PUT"}, c_token{"/acknowledge_group_message_recived"}},  acknowledge_group_message_recived_handler},
		{								{c_token{"PUT"}, c_token{"/ban"}},                                ban_handler},
		{						{c_token{"PUT"}, c_token{"/add_contact"}},                        add_contact_handler},
		{					 {c_token{"PUT"}, c_token{"/create_account"}},                     create_account_handler},
		{			   {c_token{"PUT"}, c_token{"/invite_to_group_chat"}},               invite_to_group_chat_handler},
		{			   {c_token{"PUT"}, c_token{"/invite_to_tournament"}},               invite_to_tournament_handler},
		{					{c_token{"PUT"}, c_token{"/invite_to_match"}},                    invite_to_match_handler},
		{				  {c_token{"DELETE"}, c_token{"/delete_account"}},                     delete_account_handler},
		{				  {c_token{"DELETE"}, c_token{"/remove_contact"}},                     remove_contact_handler},
		{						   {c_token{"DELETE"}, c_token{"/unban"}},                              unban_handler},
		{				{c_token{"DELETE"}, c_token{"/leave_group_chat"}},                   leave_group_chat_handler},
	};
	c_token const method = get_method_token(buffer);
	c_token const endpoint = get_endpoint_token(method.get_end() + 1);

	endpoint_to_handler.at(std::pair<c_token, c_token>(method, endpoint))(buffer, endpoint.get_end() + 1, dbconnection);
}

int main(void)
{
	static char   buffer[4096];
	int           status;
	ssize_t       read_ret;
	PGresult     *res;
	PGconn *const dbconnection =
		PQconnectdbParams((char *[]){"dbname", nullptr}, (char *[]){"pongdb", nullptr}, NO_EXPAND_DBNAME);

	if (dbconnection == nullptr)
	{
		std::cerr << "Api could not connect to the database: not enough memory left on device\n";
	}
	if (PQstatus(dbconnection) != CONNECTION_OK)
	{
		std::cerr << "Api could not connect to the database: " << PQerrorMessage(dbconnection);
	}
	res = c_prepare_pg_statement::get_result_of_statement_preparaitions(dbconnection);
	status = PQresultStatus(res);
	if (status != PGRES_COMMAND_OK)
	{
		if (status == PGRES_BAD_RESPONSE)
		{
			std::cerr << "api: error: internal database error\n";
		}
		else
		{
			std::cerr << "api: error: prepare statement failed: " << PQresultErrorMessage(res);
		}
		return (EXIT_FAILURE);
	}
	PQclear(res);
	read_ret = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	buffer[read_ret] = '\0';
	if (read_ret == -1)
	{
		perror("api: fatal error when reading from stdin: ");
		return (EXIT_FAILURE);
	}
	try
	{
		handle_request(buffer, dbconnection);
	}
	catch (std::out_of_range &)
	{
		std::cerr << "api: request to invalid endpoint\n";
	}
	catch (...)
	{
		std::cerr << "api: internal error\n";
	}
	PQfinish(dbconnection);
	return (EXIT_SUCCESS);
}

#pragma GCC diagnostic pop
