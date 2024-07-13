/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.cpp                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/05 23:46:55                                            */
/*   Updated:  2024/07/13 09:58:24                                            */
/*                                                                            */
/* ************************************************************************** */

#include "api.hpp"
#include "c_prepare_pg_statement/c_prepare_pg_statement.hpp"
#include "c_worker_id_to_text.hpp"
#include <asm-generic/socket.h>
#include <bits/types/struct_iovec.h>
#include <cctype>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <liburing.h>
#include <liburing/io_uring.h>
#include <map>
#include <postgresql/libpq-fe.h>
#include <sys/socket.h>
#include <sys/un.h>
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
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
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

static PGconn *connect_to_database(int worker_id)
{
	int           status;
	PGresult     *res;
	PGconn *const dbconnection =
		PQconnectdbParams((char *[]){"dbname", nullptr}, (char *[]){"pongdb", nullptr}, NO_EXPAND_DBNAME);

	if (dbconnection == nullptr)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": error: could not connect to the database: not enough memory left on device\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	if (PQstatus(dbconnection) != CONNECTION_OK)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": error: could not connect to the database: " << PQerrorMessage(dbconnection);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = c_prepare_pg_statement::get_result_of_statement_preparaitions(
		dbconnection); // a little bit hacky but
					   // this allows us to prepare statements through global constructors
	status = PQresultStatus(res);
	if (status != PGRES_COMMAND_OK)
	{
		if (status == PGRES_BAD_RESPONSE)
		{
			std::cerr << c_worker_id_to_text::get_name_from_id(worker_id) << ": error: internal database error\n";
		}
		else
		{
			std::cerr << c_worker_id_to_text::get_name_from_id(worker_id)
					  << ": error: prepare statement failed: " << PQresultErrorMessage(res);
		}
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	PQclear(res);
	if (PQsetnonblocking(dbconnection, 1) == -1) // set connection to nonblocking mode
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": error: failed to set database connection to nonblocking mode\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (dbconnection);
}

static int enlarge_connection_buffers_and_get_fd(PGconn *dbconnection, int worker_id)
{
	int const connection_fd = PQsocket(dbconnection);

	if (setsockopt(connection_fd, SOL_SOCKET, SO_SNDBUF, (int[]){DB_SOCK_WRITE_BUFF_SIZE}, sizeof(int)) == -1 ||
		setsockopt(connection_fd, SOL_SOCKET, SO_RCVBUF, (int[]){DB_SOCK_READ_BUFF_SIZE}, sizeof(int)) == -1)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id)
				  << ": error: failed to increase database connection buffer sizes\n";
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (connection_fd);
}

static int get_listening_socket(int worker_id)
{
	int const          listening_sock = socket(AF_UNIX, SOCK_STREAM, AF_UNIX);
	struct sockaddr_un server_addr;
	int const          slen = sizeof(server_addr);

	if (listening_sock == -1)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to create listening socket");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	server_addr.sun_family = AF_UNIX;
	strcpy(server_addr.sun_path, c_worker_id_to_text::get_socket_name_from_id(worker_id));
	unlink(c_worker_id_to_text::get_socket_name_from_id(worker_id));
	if (bind(listening_sock, reinterpret_cast<struct sockaddr *>(&server_addr), slen) == -1)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to bind listening socket to the file system");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	if (listen(listening_sock, INT_MAX) == -1)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to beginning listening in api socket");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (listening_sock);
}

static struct io_uring get_ring(int dbconnection_fd, int listening_sock_fd, struct iovec shared_buffer, int worker_id)
{
	struct io_uring_params params = {
		.sq_entries = SQ_SIZE,
		.cq_entries = CQ_SIZE,
		.flags = IORING_SETUP_CQSIZE | IORING_SETUP_SUBMIT_ALL | IORING_SETUP_COOP_TASKRUN | IORING_SETUP_SINGLE_ISSUER,
	};
	struct io_uring ring;
	int             res;

	res = io_uring_queue_init_params(SQ_SIZE, &ring, &params);
	if (res < 0)
	{
		errno = -res;
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to create io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_ring_fd(&ring);
	if (res < 0)
	{
		errno = -res;
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to register io uring fd in io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_files_sparse(&ring, MAX_CONN_PER_WORKER);
	if (res < 0)
	{
		errno = -res;
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to register fd table io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_files_update(&ring, 0, (int[2]){dbconnection_fd, listening_sock_fd}, 2);
	if (res < 0)
	{
		errno = -res;
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to register the fd of the database connection in io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_buffers(&ring, &shared_buffer, 1);
	if (res < 0)
	{
		errno = -res;
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to register the shared buffers in io uring");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (ring);
}

static struct iovec get_shared_buffer(int worker_id)
{
	struct iovec shared_buffer = {.iov_base = calloc(MAX_CONN_PER_WORKER, MEM_PER_CONN),
								  .iov_len = static_cast<size_t>(MAX_CONN_PER_WORKER) * MEM_PER_CONN};

	if (shared_buffer.iov_base == nullptr)
	{
		std::cerr << c_worker_id_to_text::get_name_from_id(worker_id);
		perror(": error: failed to allocate the shared buffer");
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	return (shared_buffer);
}

int main(void)
{
	int                worker_id = 1;
	PGconn *const      dbconnection = connect_to_database(worker_id);                                    // may exit
	int const          dbconnection_fd = enlarge_connection_buffers_and_get_fd(dbconnection, worker_id); // may exit
	int const          listening_sock_fd = get_listening_socket(worker_id);                              // may exit
	const struct iovec shared_buffer = get_shared_buffer(worker_id);                                     // may exit
	struct io_uring    ring = get_ring(dbconnection_fd, listening_sock_fd, shared_buffer, worker_id);    // may exit

	PQfinish(dbconnection);
	free(shared_buffer.iov_base);
	return (EXIT_SUCCESS);
}

#pragma GCC diagnostic pop
