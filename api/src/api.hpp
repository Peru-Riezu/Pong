/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: api.hpp                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/07 07:11:35                                            */
/*   Updated:  2024/07/19 15:39:16                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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
#define API_WORKER_COUNT           1
#define STRINGIFY(x)               (char[]){#x}
#define TOSTRING(x)                STRINGIFY(x)
#define API_WORKER_COUNT_STR       TOSTRING(API_WORKER_COUNT)
#define API_SOCKET_PATH            ((char[]){"./api_sockets/"})
// clang-format on

#define NO_EXPAND_DBNAME           0
#define RESULTS_IN_TEXT            0
#define RESULTS_IN_BINARY          1

#define SQ_SIZE                    1024
#define CQ_SIZE                    65536
#define MAX_CONN_PER_WORKER        100000
#define MEM_PER_CONN               4480 // bytes
_Static_assert(MEM_PER_CONN >= 4480, ""); // the minimum size of the uninx domain socket send buffer is 4608
										  // and a message contains 128 bytes of headers

#define DB_SOCK_READ_BUFF_SIZE     67108864
#define DB_SOCK_WRITE_BUFF_SIZE    67108864

#define DB_CONN_RELATIVE_FD        0
#define LISTENING_SOCK_RELATIVE_FD 1

typedef int t_e_state;

namespace overseer_state
{
	enum e_base_state : t_e_state
	{
		invalid_state,
		waiting_for_connections,
		waiting_for_headers,
		closing_connection
	};

	namespace dbconnection
	{
		enum e_sub_state : t_e_state
		{
			waiting_to_read_from = closing_connection + 1,
			waiting_to_read_and_write
		};
	} // namespace dbconnection

	namespace listenning_socket
	{
		enum e_sub_state : t_e_state
		{
			listenning_for_connections = dbconnection::waiting_to_read_and_write + 1,
			waiting_for_closed_connections,
			preparing_to_listen_for_connections
		};
	} // namespace listenning_socket

	namespace endpoint
	{
		namespace post_endpoint
		{
			namespace set_session_token
			{
				enum e_sub_state : t_e_state
				{
					parsing = listenning_socket::preparing_to_listen_for_connections + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace set_session_token

			namespace set_nick_name
			{
				enum e_sub_state : t_e_state
				{
					parsing = set_session_token::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace set_nick_name

			namespace set_profile_picture
			{
				enum e_sub_state : t_e_state
				{
					parsing = set_nick_name::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace set_profile_picture

			namespace set_bio
			{
				enum e_sub_state : t_e_state
				{
					parsing = set_profile_picture::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace set_bio

			namespace set_password
			{
				enum e_sub_state : t_e_state
				{
					parsing = set_bio::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace set_password

			namespace invalidate_invite_to_group_chat
			{
				enum e_sub_state : t_e_state
				{
					parsing = set_password::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace invalidate_invite_to_group_chat

			namespace invalidate_invite_to_match
			{
				enum e_sub_state : t_e_state
				{
					parsing = invalidate_invite_to_group_chat::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace invalidate_invite_to_match

			namespace invalidate_invite_to_tournament
			{
				enum e_sub_state : t_e_state
				{
					parsing = invalidate_invite_to_match::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace invalidate_invite_to_tournament

			namespace accept_invite_to_group_chat
			{
				enum e_sub_state : t_e_state
				{
					parsing = invalidate_invite_to_tournament::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace accept_invite_to_group_chat

			namespace accept_invite_to_tournament
			{
				enum e_sub_state : t_e_state
				{
					parsing = accept_invite_to_group_chat::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace accept_invite_to_tournament

			namespace accept_invite_to_match
			{
				enum e_sub_state : t_e_state
				{
					parsing = accept_invite_to_tournament::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace accept_invite_to_match

			namespace leave_tournament
			{
				enum e_sub_state : t_e_state
				{
					parsing = accept_invite_to_match::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace leave_tournament

			namespace send_direct_message
			{
				enum e_sub_state : t_e_state
				{
					parsing = leave_tournament::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace send_direct_message

			namespace send_group_message
			{
				enum e_sub_state : t_e_state
				{
					parsing = send_direct_message::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace send_group_message

			namespace send_match_events
			{
				enum e_sub_state : t_e_state
				{
					parsing = send_group_message::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace send_match_events

			namespace acknowledge_direct_message_recived
			{
				enum e_sub_state : t_e_state
				{
					parsing = send_match_events::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace acknowledge_direct_message_recived

			namespace acknowledge_direct_message_read
			{
				enum e_sub_state : t_e_state
				{
					parsing = acknowledge_direct_message_recived::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace acknowledge_direct_message_read

			namespace acknowledge_group_message_read
			{
				enum e_sub_state : t_e_state
				{
					parsing = acknowledge_direct_message_read::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace acknowledge_group_message_read

			namespace promote_group_user
			{
				enum e_sub_state : t_e_state
				{
					parsing = acknowledge_group_message_read::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace promote_group_user

			namespace demote_group_user
			{
				enum e_sub_state : t_e_state
				{
					parsing = promote_group_user::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace demote_group_user
		}     // namespace post_endpoint

		namespace get_endpoint
		{
			namespace get_profile
			{
				enum e_sub_state : t_e_state
				{
					parsing = post_endpoint::demote_group_user::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_profile

			namespace get_group_subscriptions
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_profile::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_group_subscriptions

			namespace get_tournament_subscriptions
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_group_subscriptions::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_tournament_subscriptions

			namespace get_contacts
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_tournament_subscriptions::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_contacts

			namespace get_match_history
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_contacts::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_match_history

			namespace get_messages
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_match_history::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_messages

			namespace get_group_messages
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_messages::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_group_messages

			namespace get_match_events
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_group_messages::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_match_events

			namespace get_pending_messages
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_match_events::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_pending_messages

			namespace get_pending_match_events
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_pending_messages::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace get_pending_match_events
		}     // namespace get_endpoint

		namespace put_endpoint
		{
			namespace create_tournament
			{
				enum e_sub_state : t_e_state
				{
					parsing = get_endpoint::get_pending_match_events::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace create_tournament

			namespace create_group_chat
			{
				enum e_sub_state : t_e_state
				{
					parsing = create_tournament::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace create_group_chat

			namespace acknowledge_group_message_recived
			{
				enum e_sub_state : t_e_state
				{
					parsing = create_group_chat::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace acknowledge_group_message_recived

			namespace ban
			{
				enum e_sub_state : t_e_state
				{
					parsing = acknowledge_group_message_recived::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace ban

			namespace add_contact
			{
				enum e_sub_state : t_e_state
				{
					parsing = ban::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace add_contact

			namespace create_account
			{
				enum e_sub_state : t_e_state
				{
					parsing = add_contact::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace create_account

			namespace invite_to_group_chat
			{
				enum e_sub_state : t_e_state
				{
					parsing = create_account::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace invite_to_group_chat

			namespace invite_to_tournament
			{
				enum e_sub_state : t_e_state
				{
					parsing = invite_to_group_chat::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace invite_to_tournament

			namespace invite_to_match
			{
				enum e_sub_state : t_e_state
				{
					parsing = invite_to_tournament::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace invite_to_match
		}     // namespace put_endpoint

		namespace delete_endpoint
		{
			namespace delete_account
			{
				enum e_sub_state : t_e_state
				{
					parsing = put_endpoint::invite_to_match::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace delete_account

			namespace remove_contact
			{
				enum e_sub_state : t_e_state
				{
					parsing = delete_account::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace remove_contact

			namespace unban
			{
				enum e_sub_state : t_e_state
				{
					parsing = remove_contact::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace unban

			namespace leave_group_chat
			{
				enum e_sub_state : t_e_state
				{
					parsing = unban::parsing + 1,
					waiting_for_db_response,
					sending_response
				};
			} // namespace leave_group_chat
		}     // namespace delete_endpoint
	}         // namespace endpoint
} // namespace overseer_state

c_mutable_token        get_base58_token(char *buffer);
c_mutable_token        get_token(char *buffer);
c_mutable_token        decode_token(c_mutable_token token);

t_e_state              parse_headers_and_get_new_state(char *buffer);

#pragma GCC diagnostic pop
