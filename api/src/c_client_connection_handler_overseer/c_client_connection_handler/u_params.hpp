/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: u_params.hpp                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/10 19:06:41                                            */
/*   Updated:  2024/08/12 06:19:59                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>

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
#pragma GCC diagnostic ignored "-Wpadded"
;

union u_params
{
		struct s_set_session_token
		{
				uint64_t name;
				uint64_t password[4];
				bool     force;
		} set_session_token_params;

		struct s_set_nick_name
		{
				uint64_t name;
				uint64_t session_token[4];
		} set_nick_name_params;

		struct s_set_profile_picture
		{
				uint64_t name;
				uint64_t session_token[4];
		} set_profile_picture_params;

		struct s_set_bio
		{
				uint64_t name;
				uint64_t session_token[4];
		} set_bio_params;

		struct s_set_password
		{
				uint64_t name;
				uint64_t old_password[4];
				uint64_t new_password[4];
		} set_password_params;

		struct s_get_profile
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t subject_name;
		} get_profile_params;

		struct s_get_group_subscriptions
		{
				uint64_t name;
				uint64_t session_token[4];
		} get_group_subscriptions_params;

		struct s_get_tournament_subscriptions
		{
				uint64_t name;
				uint64_t session_token[4];
		} get_tournament_subscriptions_params;

		struct s_get_contacts
		{
				uint64_t name;
				uint64_t session_token[4];
		} get_contacts_params;

		struct s_get_match_history
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t subject_name;
				int      from;
				int      to;
		} get_match_history_params;

		struct s_get_messages
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t sender_name;
				int      from;
				int      to;
		} get_messages_params;

		struct s_get_group_messages
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_id;
				int      from;
				int      to;
		} get_group_messages_params;

		struct s_get_match_events
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t match_id;
		} get_match_events_params;

		struct s_get_pending_messages
		{
				uint64_t name;
				uint64_t session_token[4];
		} get_pending_messages_params;

		struct s_get_pending_match_events
		{
				uint64_t name;
				uint64_t session_token[4];
		} get_pending_match_events_params;

		struct s_create_tournament
		{
				uint64_t name;
				uint64_t session_token[4];
				int      tournament_name;
		} create_tournament_params;

		struct s_create_group_chat
		{
				unsigned char group_chat_name[30];
				uint64_t      name;
				uint64_t      session_token[4];
		} create_group_chat_params;

		struct s_invite_to_group_chat
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
				uint64_t recipient_name;
		} invite_to_group_chat_params;

		struct s_invite_to_tournament
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
				int      tournament_id;
		} invite_to_tournament_params;

		struct s_invite_to_match
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
		} invite_to_match_params;

		struct s_invalidate_invite_to_group_chat
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
				uint64_t recipient_name;
		} invalidate_invite_to_group_chat_params;

		struct s_invalidate_invite_to_match
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
				int      tournament_id;
		} invalidate_invite_to_match_params;

		struct s_invalidate_invite_to_tournament
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
		} invalidate_invite_to_tournament_params;

		struct s_accept_invite_to_group_chat
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
		} accept_invite_to_group_chat_params;

		struct s_accept_invite_to_tournament
		{
				uint64_t name;
				uint64_t session_token[4];
				int      tournament_id;
		} accept_invite_to_tournament_params;

		struct s_accept_invite_to_match
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t match_id;
		} accept_invite_to_match_params;

		struct s_leave_tournament
		{
				uint64_t name;
				uint64_t session_token[4];
				int      tournament_id;
		} leave_tournament_params;

		struct s_leave_group_chat
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
		} leave_group_chat_params;

		struct s_send_direct_message
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
		} send_direct_message_params;

		struct s_send_group_message
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
		} send_group_message_params;

		struct s_send_match_events
		{
				uint64_t name;
				uint64_t session_token[4];
		} send_match_events_params;

		struct s_acknowledge_direct_message_recived
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t message_id;
		} acknowledge_direct_message_recived_params;

		struct s_acknowledge_direct_message_read
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t message_id;
		} acknowledge_direct_message_read_params;

		struct s_acknowledge_group_message_recived
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t message_id;
		} acknowledge_group_message_recived_params;

		struct s_acknowledge_group_message_read
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t message_id;
		} acknowledge_group_message_read_params;

		struct s_promote_group_user
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
				uint64_t recipient_name;
		} promote_group_user_params;

		struct s_demote_group_user
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t group_chat_id;
				uint64_t recipient_name;
		} demote_group_user_params;

		struct s_ban
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
		} ban_params;

		struct s_unban
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t recipient_name;
		} unban_params;

		struct s_add_contact
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t subject_name;
		} add_contact_params;

		struct s_remove_contact
		{
				uint64_t name;
				uint64_t session_token[4];
				uint64_t subject_name;
		} remove_contact_params;

		struct s_create_account
		{
				unsigned char nick_name[30];
				uint64_t      name;
				uint64_t      password[4];
		} create_account_params;

		struct s_delete_account
		{
				uint64_t name;
				uint64_t password[4];
		} delete_account_params;
};

#pragma GCC diagnostic pop
