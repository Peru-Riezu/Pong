/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: e_handler_state.hpp                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/10 18:51:01                                            */
/*   Updated:  2024/08/21 17:55:29                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "c_client_connection_handler.hpp"

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
#pragma GCC diagnostic ignored "-Wshadow"
;

struct c_client_connection_handlers_overseer::c_client_connection_handler::e_handler_state
{
		enum e_sub_state : t_e_handler_state
		{
			invalid_state,
			waiting_for_connection,
			waiting_for_headers,
			waiting_for_write_completion,
			closing,
			waiting_for_close_completion
		};

		struct post_endpoint
		{
				struct set_session_token
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = waiting_for_close_completion + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct set_nick_name
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = set_session_token::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct set_profile_picture
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = set_nick_name::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct set_bio
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = set_profile_picture::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct set_password
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = set_bio::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct invalidate_invite_to_group_chat
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = set_password::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct invalidate_invite_to_match
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = invalidate_invite_to_group_chat::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct invalidate_invite_to_tournament
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = invalidate_invite_to_match::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct accept_invite_to_group_chat
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = invalidate_invite_to_tournament::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct accept_invite_to_tournament
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = accept_invite_to_group_chat::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct accept_invite_to_match
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = accept_invite_to_tournament::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct leave_tournament
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = accept_invite_to_match::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct send_direct_message
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = leave_tournament::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct send_group_message
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = send_direct_message::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct send_match_events
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = send_group_message::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct acknowledge_direct_message_received
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = send_match_events::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct acknowledge_direct_message_read
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = acknowledge_direct_message_received::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct acknowledge_group_message_read
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = acknowledge_direct_message_read::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct promote_group_user
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = acknowledge_group_message_read::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct demote_group_user
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = promote_group_user::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};
		};

		struct get_endpoint
		{
				struct get_profile
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = post_endpoint::demote_group_user::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_group_subscriptions
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_profile::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_tournament_subscriptions
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_group_subscriptions::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_contacts
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_tournament_subscriptions::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_match_history
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_contacts::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_messages
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_match_history::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_group_messages
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_messages::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_match_events
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_group_messages::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_pending_messages
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_match_events::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct get_pending_match_events
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_pending_messages::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};
		};

		struct put_endpoint
		{
				struct create_tournament
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = get_endpoint::get_pending_match_events::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct create_group_chat
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = create_tournament::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct acknowledge_group_message_received
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = create_group_chat::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct ban
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = acknowledge_group_message_received::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct add_contact
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = ban::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct create_account
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = add_contact::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct invite_to_group_chat
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = create_account::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct invite_to_tournament
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = invite_to_group_chat::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct invite_to_match
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = invite_to_tournament::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};
		};

		struct delete_endpoint
		{
				struct delete_account
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = put_endpoint::invite_to_match::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct remove_contact
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = delete_account::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct unban
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = remove_contact::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};

				struct leave_group_chat
				{
						enum e_sub_state : t_e_handler_state
						{
							parsing = unban::sending_response + 1,
							waiting_for_db_response,
							sending_response
						};
				};
		};
};

#pragma GCC diagnostic pop
