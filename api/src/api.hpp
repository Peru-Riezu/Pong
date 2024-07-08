/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: api.hpp                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/07 07:11:35                                            */
/*   Updated:  2024/07/08 17:44:31                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

typedef void (*t_handler_function)(char *);

void                   set_session_token_handler(char *buffer);
void                   set_nick_name_handler(char *buffer);
void                   set_profile_picture_handler(char *buffer);
void                   set_bio_handler(char *buffer);
void                   set_password_handler(char *buffer);
void                   invalidate_invite_to_group_chat_handler(char *buffer);
void                   invalidate_invite_to_match_handler(char *buffer);
void                   invalidate_invite_to_tournament_handler(char *buffer);
void                   accept_invite_to_group_chat_handler(char *buffer);
void                   accept_invite_to_tournament_handler(char *buffer);
void                   accept_invite_to_match_handler(char *buffer);
void                   leave_tournament_handler(char *buffer);
void                   send_direct_message_handler(char *buffer);
void                   send_group_message_handler(char *buffer);
void                   send_match_events_handler(char *buffer);
void                   acknowledge_direct_message_recived_handler(char *buffer);
void                   acknowledge_direct_message_read_handler(char *buffer);
void                   acknowledge_group_message_read_handler(char *buffer);
void                   promote_group_user_handler(char *buffer);
void                   demote_group_user_handler(char *buffer);

void                   get_profile_handler(char *buffer);
void                   get_group_subscriptions_handler(char *buffer);
void                   get_tournament_subscriptions_handler(char *buffer);
void                   get_contacts_handler(char *buffer);
void                   get_match_history_handler(char *buffer);
void                   get_messages_handler(char *buffer);
void                   get_group_messages_handler(char *buffer);
void                   get_match_events_handler(char *buffer);
void                   get_pending_messages_handler(char *buffer);
void                   get_pending_match_events_handler(char *buffer);

void                   create_tournament_handler(char *buffer);
void                   create_group_chat_handler(char *buffer);
void                   acknowledge_group_message_recived_handler(char *buffer);
void                   ban_handler(char *buffer);
void                   add_contact_handler(char *buffer);
void                   create_account_handler(char *buffer);
void                   invite_to_group_chat_handler(char *buffer);
void                   invite_to_tournament_handler(char *buffer);
void                   invite_to_match_handler(char *buffer);

void                   delete_account_handler(char *buffer);
void                   remove_contact_handler(char *buffer);
void                   unban_handler(char *buffer);
void                   leave_group_chat_handler(char *buffer);

#pragma GCC diagnostic pop
