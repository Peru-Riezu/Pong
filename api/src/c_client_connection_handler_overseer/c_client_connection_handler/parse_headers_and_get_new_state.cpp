/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parse_headers_and_get_new_state.cpp                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/13 19:45:54                                            */
/*   Updated:  2024/08/21 18:53:53                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../c_token/c_token.hpp"
#include "./c_client_connection_handler.hpp"
#include "e_handler_state.hpp"
#include <cctype>
#include <map>

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
#pragma GCC diagnostic ignored "-Wexit-time-destructors"
;

c_client_connection_handlers_overseer::c_client_connection_handler::t_e_handler_state
	c_client_connection_handlers_overseer::c_client_connection_handler::parse_headers_and_get_new_state(
		s_fcgi_params *request_params)
{
	// clang-format off
	static std::map<std::pair<c_token, c_token>, t_e_handler_state> const endpoint_to_state =
	{
		{{c_token{"POST"}, c_token{"/api/set_session_token"}},
			e_handler_state::post_endpoint::set_session_token::parsing},
		{{c_token{"POST"}, c_token{"/api/set_nick_name"}},
			e_handler_state::post_endpoint::set_nick_name::parsing},
		{{c_token{"POST"}, c_token{"/api/set_profile_picture"}},
			e_handler_state::post_endpoint::set_profile_picture::parsing},
		{{c_token{"POST"}, c_token{"/api/set_bio"}},
			e_handler_state::post_endpoint::set_bio::parsing},
		{{c_token{"POST"}, c_token{"/api/set_password"}},
			e_handler_state::post_endpoint::set_password::parsing},
		{{c_token{"POST"}, c_token{"/api/invalidate_invite_to_group_chat"}},
			e_handler_state::post_endpoint::invalidate_invite_to_group_chat::parsing},
		{{c_token{"POST"}, c_token{"/api/invalidate_invite_to_match"}},
			e_handler_state::post_endpoint::invalidate_invite_to_match::parsing},
		{{c_token{"POST"}, c_token{"/api/invalidate_invite_to_tournament"}},
			e_handler_state::post_endpoint::invalidate_invite_to_tournament::parsing},
		{{c_token{"POST"}, c_token{"/api/accept_invite_to_group_chat"}},
			e_handler_state::post_endpoint::accept_invite_to_group_chat::parsing},
		{{c_token{"POST"}, c_token{"/api/accept_invite_to_tournament"}},
			e_handler_state::post_endpoint::accept_invite_to_tournament::parsing},
		{{c_token{"POST"}, c_token{"/api/accept_invite_to_match"}},
			e_handler_state::post_endpoint::accept_invite_to_match::parsing},
		{{c_token{"POST"}, c_token{"/api/leave_tournament"}},
			e_handler_state::post_endpoint::leave_tournament::parsing},
		{{c_token{"POST"}, c_token{"/api/send_direct_message"}},
			e_handler_state::post_endpoint::send_direct_message::parsing},
		{{c_token{"POST"}, c_token{"/api/send_group_message"}},
			e_handler_state::post_endpoint::send_group_message::parsing},
		{{c_token{"POST"}, c_token{"/api/send_match_events"}},
			e_handler_state::post_endpoint::send_match_events::parsing},
		{{c_token{"POST"}, c_token{"/api/acknowledge_direct_message_received"}},
			e_handler_state::post_endpoint::acknowledge_direct_message_received::parsing},
		{{c_token{"POST"}, c_token{"/api/acknowledge_direct_message_read"}},
			e_handler_state::post_endpoint::acknowledge_direct_message_read::parsing},
		{{c_token{"POST"}, c_token{"/api/acknowledge_group_message_read"}},
			e_handler_state::post_endpoint::acknowledge_group_message_read::parsing},
		{{c_token{"POST"}, c_token{"/api/promote_group_user"}},
			e_handler_state::post_endpoint::promote_group_user::parsing},
		{{c_token{"POST"}, c_token{"/api/demote_group_user"}},
			e_handler_state::post_endpoint::demote_group_user::parsing},
		{{c_token{"GET"}, c_token{"/api/get_profile"}},
			e_handler_state::get_endpoint::get_profile::parsing},
		{{c_token{"GET"}, c_token{"/api/get_group_subscriptions"}},
			e_handler_state::get_endpoint::get_group_subscriptions::parsing},
		{{c_token{"GET"}, c_token{"/api/get_tournament_subscriptions"}},
			e_handler_state::get_endpoint::get_tournament_subscriptions::parsing},
		{{c_token{"GET"}, c_token{"/api/get_contacts"}},
			e_handler_state::get_endpoint::get_contacts::parsing},
		{{c_token{"GET"}, c_token{"/api/get_match_history"}},
			e_handler_state::get_endpoint::get_match_history::parsing},
		{{c_token{"GET"}, c_token{"/api/get_messages"}},
			e_handler_state::get_endpoint::get_messages::parsing},
		{{c_token{"GET"}, c_token{"/api/get_group_messages"}},
			e_handler_state::get_endpoint::get_group_messages::parsing},
		{{c_token{"GET"}, c_token{"/api/get_match_events"}},
			e_handler_state::get_endpoint::get_match_events::parsing},
		{{c_token{"GET"}, c_token{"/api/get_pending_messages"}},
			e_handler_state::get_endpoint::get_pending_messages::parsing},
		{{c_token{"GET"}, c_token{"/api/get_pending_match_events"}},
			e_handler_state::get_endpoint::get_pending_match_events::parsing},
		{{c_token{"PUT"}, c_token{"/api/create_tournament"}},
			e_handler_state::put_endpoint::create_tournament::parsing},
		{{c_token{"PUT"}, c_token{"/api/create_group_chat"}},
			e_handler_state::put_endpoint::create_group_chat::parsing},
		{{c_token{"PUT"}, c_token{"/api/acknowledge_group_message_received"}},
			e_handler_state::put_endpoint::acknowledge_group_message_received::parsing},
		{{c_token{"PUT"}, c_token{"/api/ban"}},
			e_handler_state::put_endpoint::ban::parsing},
		{{c_token{"PUT"}, c_token{"/api/add_contact"}},
			e_handler_state::put_endpoint::add_contact::parsing},
		{{c_token{"PUT"}, c_token{"/api/create_account"}},
			e_handler_state::put_endpoint::create_account::parsing},
		{{c_token{"PUT"}, c_token{"/api/invite_to_group_chat"}},
			e_handler_state::put_endpoint::invite_to_group_chat::parsing},
		{{c_token{"PUT"}, c_token{"/api/invite_to_tournament"}},
			e_handler_state::put_endpoint::invite_to_tournament::parsing},
		{{c_token{"PUT"}, c_token{"/api/invite_to_match"}},
			e_handler_state::put_endpoint::invite_to_match::parsing},
		{{c_token{"DELETE"}, c_token{"/api/delete_account"}},
			e_handler_state::delete_endpoint::delete_account::parsing},
		{{c_token{"DELETE"}, c_token{"/api/remove_contact"}},
			e_handler_state::delete_endpoint::remove_contact::parsing},
		{{c_token{"DELETE"}, c_token{"/api/unban"}},
			e_handler_state::delete_endpoint::unban::parsing},
		{{c_token{"DELETE"}, c_token{"/api/leave_group_chat"}},
			e_handler_state::delete_endpoint::leave_group_chat::parsing}
	 };
	// clang-format on
	std::map<std::pair<c_token, c_token>, t_e_handler_state>::const_iterator it = endpoint_to_state.find(
		std::pair<c_token, c_token>(request_params->request_method, request_params->fastcgi_script_name));

	if (it == endpoint_to_state.end())
	{
		return (e_handler_state::invalid_state);
	}
	return (it->second);
}

#pragma GCC diagnostic pop
