/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: api.hpp                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/07 07:11:35                                            */
/*   Updated:  2024/07/13 09:54:37                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "/usr/include/postgresql/libpq-fe.h"
#include "c_token/c_token.hpp"
#include <cstring>
#include <fcntl.h>

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
#pragma GCC diagnostic ignored "-Wc11-extensions"
;

// clang-format off
#define API_WORKER_COUNT        1
#define STRINGIFY(x)            (char[]){#x}
#define TOSTRING(x)             STRINGIFY(x)
#define API_WORKER_COUNT_STR    TOSTRING(API_WORKER_COUNT)
#define API_SOCKET_PATH         ((char[]){"/home/user/pong/api_sockets/"})
// clang-format on

#define NO_EXPAND_DBNAME        0
#define RESULTS_IN_TEXT         0
#define RESULTS_IN_BINARY       1

#define SQ_SIZE                 1024
#define CQ_SIZE                 65536
#define MAX_CONN_PER_WORKER     100000
#define MEM_PER_CONN            5000 // bytes

#define DB_SOCK_READ_BUFF_SIZE  67108864
#define DB_SOCK_WRITE_BUFF_SIZE 67108864

c_mutable_token get_base58_token(char *buffer);
c_mutable_token get_token(char *buffer);
c_mutable_token decode_token(c_mutable_token token);

typedef void (*t_handler_function)(char *, char const *, PGconn *const);

void set_session_token_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void set_nick_name_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void set_profile_picture_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void set_bio_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void set_password_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void invalidate_invite_to_group_chat_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void invalidate_invite_to_match_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void invalidate_invite_to_tournament_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void accept_invite_to_group_chat_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void accept_invite_to_tournament_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void accept_invite_to_match_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void leave_tournament_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void send_direct_message_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void send_group_message_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void send_match_events_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void acknowledge_direct_message_recived_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void acknowledge_direct_message_read_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void acknowledge_group_message_read_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void promote_group_user_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void demote_group_user_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);

void get_profile_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_group_subscriptions_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_tournament_subscriptions_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_contacts_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_match_history_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_messages_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_group_messages_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_match_events_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_pending_messages_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void get_pending_match_events_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);

void create_tournament_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void create_group_chat_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void acknowledge_group_message_recived_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void ban_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void add_contact_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void create_account_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void invite_to_group_chat_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void invite_to_tournament_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void invite_to_match_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);

void delete_account_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void remove_contact_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void unban_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);
void leave_group_chat_handler(char *buffer, char const *query_beginning, PGconn *dbconnection);

#pragma GCC diagnostic pop
