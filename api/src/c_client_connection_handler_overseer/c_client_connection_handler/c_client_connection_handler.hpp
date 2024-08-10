/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_client_connection_handler.hpp                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/24 16:25:15                                            */
/*   Updated:  2024/08/10 05:59:42                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../c_client_connection_handler_overseer.hpp"
#include "../c_token/c_token.hpp"
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
;

class c_dbconnection_pool_overseer;
class c_io_uring_overseer;

class c_client_connection_handlers_overseer::c_client_connection_handler
{
	private:
		typedef int                  t_e_handler_state;

		c_client_connection_handler *next_available;
		t_e_handler_state            current_state;
		unsigned int                 index;
		unsigned int                 memory_held_by_the_codec; // starts at memory_shared_with_the_ring
		unsigned int memory_held_by_the_handler; // starts at memory_shared_with_the_ring - memory_held_by_the_handler
		uint8_t     *memory_shared_with_the_ring;

	public:
		c_client_connection_handler *get_next_available(void) const;
		unsigned int                 get_index(void) const;

		void                         set_next_available(c_client_connection_handler *next_available_exemplum);
		void                         set_index(unsigned int index_exemplum);
		void                         set_memory_shared_with_the_ring(uint8_t *memory_shared_with_the_ring_exemplum);
		void                         set_current_state(t_e_handler_state current_state_exemplum);
		void                         notify_io_completion(struct io_uring_cqe *cqe);
		void                         notify_query_completion(void *result);
		void                         parse_headers_and_get_new_state(void);

		// all posible client_connection_handler states in a enum
		struct e_handler_state
		{
				enum e_sub_state : t_e_handler_state
				{
					invalid_state,
					waiting_for_connection,
					waiting_for_headers,
					waiting_for_close
				};

				struct post_endpoint
				{
						struct set_session_token
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = waiting_for_close + 1,
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

						struct acknowledge_direct_message_recived
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
									parsing = acknowledge_direct_message_recived::sending_response + 1,
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

						struct acknowledge_group_message_recived
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
									parsing = acknowledge_group_message_recived::sending_response + 1,
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

	private:
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
						uint64_t      name;
						uint64_t      session_token[4];
						unsigned char group_chat_name[30];
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
						int      tournament_id;
						uint64_t recipient_name;
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
						int      tournament_id;
						uint64_t recipient_name;
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
						uint64_t      name;
						uint64_t      password[4];
						unsigned char nick_name[30];
				} create_account_params;

				struct s_delete_account
				{
						uint64_t name;
						uint64_t password[4];
				} delete_account_params;
		} params;

		struct s_fcgi_params
		{
				c_token request_method;
				c_token fastcgi_script_name;
				c_token query_string;
				c_token content_length;
		};
};

#pragma GCC diagnostic pop
