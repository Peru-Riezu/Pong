/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_endpoint_overseer.hpp                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/14 12:28:12                                            */
/*   Updated:  2024/07/19 19:38:00                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../api.hpp"
#include "c_token/c_token.hpp"
#include <cstdint>
#include <postgresql/libpq-fe.h>

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

typedef int t_e_endpoint_state;

class c_endpoint_overseer
{
	private:
		static inline c_listenning_socket_overseer &listenning_socket_overseer;
		static inline c_dbconnection_pool_overseer &dbconnection_pool_overseer;
		static inline c_endpoint_overseer          *aviable_head;
		static inline c_endpoint_overseer          *aviable_tail;
		static inline struct io_uring              *ring;
		static inline int                           completion_ring_aviable_entries = CQ_SIZE;
		static inline int                           submisioin_ring_aviable_entries = SQ_SIZE;

		c_endpoint_overseer                        *next_aviable;
		t_e_endpoint_state                          current_state;
		int                                         relative_index;
		uint8_t                                    *memory_shared_whit_ring;

		void                                        parse_headers_and_get_new_state(char *buffer);
		c_mutable_token                             get_base58_token(char *buffer);
		c_mutable_token                             get_token(char *buffer);
		c_mutable_token                             decode_token(c_mutable_token token);

	public:
		void        set_new_state(t_e_endpoint_state new_state);
		void        set_memory_shared_whit_ring(uint8_t *memory);
		void        set_relative_index(int index);
		void        set_next_avialbe(c_endpoint_overseer *overseer);
		void        make_aviable(void);
		void        notify_db_result(void *res);
		void        notify_ring_result(struct io_uring_cqe *cqe, c_endpoint_overseer *overseers);
		static void notify_pipeline_not_empty(void);
		static void set_listenning_socket_overseer(c_endpoint_overseer *overseer);
		static void set_dbconnection_overseer(c_endpoint_overseer *overseer);
		static void set_dbconnection(PGconn *dbconnection_exemplum);
		static void set_ring(struct io_uring *ring_exemplum);
		static void set_aviable_head(c_endpoint_overseer *overseer);
		static void set_aviable_tail(c_endpoint_overseer *overseer);
};

namespace e_endpoint_state
{
	namespace post_endpoint
	{
		namespace set_session_token
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing,
				waiting_for_db_response,
				sending_response
			};
		} // namespace set_session_token

		namespace set_nick_name
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = set_session_token::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace set_nick_name

		namespace set_profile_picture
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = set_nick_name::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace set_profile_picture

		namespace set_bio
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = set_profile_picture::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace set_bio

		namespace set_password
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = set_bio::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace set_password

		namespace invalidate_invite_to_group_chat
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = set_password::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace invalidate_invite_to_group_chat

		namespace invalidate_invite_to_match
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = invalidate_invite_to_group_chat::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace invalidate_invite_to_match

		namespace invalidate_invite_to_tournament
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = invalidate_invite_to_match::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace invalidate_invite_to_tournament

		namespace accept_invite_to_group_chat
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = invalidate_invite_to_tournament::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace accept_invite_to_group_chat

		namespace accept_invite_to_tournament
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = accept_invite_to_group_chat::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace accept_invite_to_tournament

		namespace accept_invite_to_match
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = accept_invite_to_tournament::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace accept_invite_to_match

		namespace leave_tournament
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = accept_invite_to_match::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace leave_tournament

		namespace send_direct_message
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = leave_tournament::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace send_direct_message

		namespace send_group_message
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = send_direct_message::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace send_group_message

		namespace send_match_events
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = send_group_message::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace send_match_events

		namespace acknowledge_direct_message_recived
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = send_match_events::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace acknowledge_direct_message_recived

		namespace acknowledge_direct_message_read
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = acknowledge_direct_message_recived::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace acknowledge_direct_message_read

		namespace acknowledge_group_message_read
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = acknowledge_direct_message_read::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace acknowledge_group_message_read

		namespace promote_group_user
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = acknowledge_group_message_read::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace promote_group_user

		namespace demote_group_user
		{
			enum e_sub_state : t_e_endpoint_state
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
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = post_endpoint::demote_group_user::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_profile

		namespace get_group_subscriptions
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_profile::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_group_subscriptions

		namespace get_tournament_subscriptions
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_group_subscriptions::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_tournament_subscriptions

		namespace get_contacts
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_tournament_subscriptions::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_contacts

		namespace get_match_history
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_contacts::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_match_history

		namespace get_messages
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_match_history::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_messages

		namespace get_group_messages
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_messages::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_group_messages

		namespace get_match_events
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_group_messages::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_match_events

		namespace get_pending_messages
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_match_events::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace get_pending_messages

		namespace get_pending_match_events
		{
			enum e_sub_state : t_e_endpoint_state
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
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = get_endpoint::get_pending_match_events::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace create_tournament

		namespace create_group_chat
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = create_tournament::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace create_group_chat

		namespace acknowledge_group_message_recived
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = create_group_chat::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace acknowledge_group_message_recived

		namespace ban
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = acknowledge_group_message_recived::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace ban

		namespace add_contact
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = ban::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace add_contact

		namespace create_account
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = add_contact::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace create_account

		namespace invite_to_group_chat
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = create_account::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace invite_to_group_chat

		namespace invite_to_tournament
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = invite_to_group_chat::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace invite_to_tournament

		namespace invite_to_match
		{
			enum e_sub_state : t_e_endpoint_state
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
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = put_endpoint::invite_to_match::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace delete_account

		namespace remove_contact
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = delete_account::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace remove_contact

		namespace unban
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = remove_contact::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace unban

		namespace leave_group_chat
		{
			enum e_sub_state : t_e_endpoint_state
			{
				parsing = unban::parsing + 1,
				waiting_for_db_response,
				sending_response
			};
		} // namespace leave_group_chat
	}     // namespace delete_endpoint
} // namespace e_endpoint_state

#pragma GCC diagnostic pop
