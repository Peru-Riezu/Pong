/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: client_connection_handler.hpp                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/24 16:25:15                                            */
/*   Updated:  2024/07/25 00:46:39                                            */
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
;

class c_dbconnection_pool_overseer;
class c_io_uring_overseer;
class c_client_connection_handlers_overseer;

extern c_dbconnection_pool_overseer          *g_dbconnection_pool_overseer;
extern c_io_uring_overseer                   *g_io_uring_overseer;
extern c_client_connection_handlers_overseer *g_client_connection_handlers_overseer;

class c_client_connection_handler
{
	private:
		typedef int                  t_e_handler_state;

		t_e_handler_state            current_state;
		c_client_connection_handler *next_aviable;
		int                          index;
		uint8_t                     *memory_shared_whit_the_ring;

	public:
		c_client_connection_handler *get_next_aviable(void) const;
		int                          get_index(void) const;

		void                         set_next_aviable(c_client_connection_handler *next_aviable_exemplum);
		void                         set_index(int index);
		void                         set_memory_shared_whit_the_ring(int index);
		void                         notify_connection_assigned(void);
		void                         notify_io_commpletion(struct io_uring_cqe *completion);
		void                         notify_query_commpletion(void *completion);

	private: // all posible client_connection_handler states in a enum
		struct e_handler_state
		{
				struct post_endpoint
				{
						struct set_session_token
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing,
									waiting_for_db_response,
									sending_response
								};
						};

						struct set_nick_name
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = set_session_token::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct set_profile_picture
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = set_nick_name::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct set_bio
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = set_profile_picture::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct set_password
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = set_bio::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct invalidate_invite_to_group_chat
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = set_password::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct invalidate_invite_to_match
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = invalidate_invite_to_group_chat::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct invalidate_invite_to_tournament
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = invalidate_invite_to_match::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct accept_invite_to_group_chat
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = invalidate_invite_to_tournament::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct accept_invite_to_tournament
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = accept_invite_to_group_chat::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct accept_invite_to_match
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = accept_invite_to_tournament::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct leave_tournament
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = accept_invite_to_match::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct send_direct_message
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = leave_tournament::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct send_group_message
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = send_direct_message::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct send_match_events
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = send_group_message::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct acknowledge_direct_message_recived
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = send_match_events::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct acknowledge_direct_message_read
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = acknowledge_direct_message_recived::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct acknowledge_group_message_read
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = acknowledge_direct_message_read::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct promote_group_user
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = acknowledge_group_message_read::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct demote_group_user
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = promote_group_user::parsing + 1,
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
									parsing = post_endpoint::demote_group_user::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_group_subscriptions
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_profile::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_tournament_subscriptions
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_group_subscriptions::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_contacts
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_tournament_subscriptions::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_match_history
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_contacts::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_messages
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_match_history::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_group_messages
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_messages::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_match_events
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_group_messages::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_pending_messages
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_match_events::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct get_pending_match_events
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = get_pending_messages::parsing + 1,
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
									parsing = get_endpoint::get_pending_match_events::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct create_group_chat
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = create_tournament::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct acknowledge_group_message_recived
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = create_group_chat::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct ban
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = acknowledge_group_message_recived::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct add_contact
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = ban::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct create_account
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = add_contact::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct invite_to_group_chat
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = create_account::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct invite_to_tournament
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = invite_to_group_chat::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct invite_to_match
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = invite_to_tournament::parsing + 1,
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
									parsing = put_endpoint::invite_to_match::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct remove_contact
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = delete_account::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct unban
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = remove_contact::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};

						struct leave_group_chat
						{
								enum e_sub_state : t_e_handler_state
								{
									parsing = unban::parsing + 1,
									waiting_for_db_response,
									sending_response
								};
						};
				};
		};
};

#pragma GCC diagnostic pop
