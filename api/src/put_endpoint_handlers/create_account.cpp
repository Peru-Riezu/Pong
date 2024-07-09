/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: create_account.cpp                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/09 08:17:58                                            */
/*   Updated:  2024/07/09 14:35:43                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../api.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <postgresql/libpq-fe.h>
#include <string.h>

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
#pragma GCC diagnostic ignored "-Wc++98-compat-bind-to-temporary-copy"
;

c_mutable_token get_base58_token(char *buffer)
{
	char  *beginning;
	size_t i;

	i = 0;
	beginning = &buffer[i];
	while (isalnum(buffer[i]) != 0)
	{
		i++;
	}
	if (i == 0)
	{
		return (c_mutable_token());
	}
	return (c_mutable_token(beginning, &buffer[i - 1]));
}

c_mutable_token get_token(char *buffer)
{
	char  *beginning;
	size_t i;

	i = 0;
	beginning = &buffer[i];
	while (isalnum(buffer[i]) != 0 || buffer[i] == ',' || buffer[i] == '.' || buffer[i] == '_' || buffer[i] == '~' ||
		   buffer[i] == '%')
	{
		i++;
	}
	if (i == 0)
	{
		return (c_mutable_token());
	}
	return (c_mutable_token(beginning, &buffer[i - 1]));
}

static int decode_hex_digit(char c)
{
	if (isdigit(c) != 0)
	{
		return (c - '0');
	}
	return ((tolower(c) - 'a') + 10);
}

c_mutable_token decode_token(c_mutable_token token) // NOLINT(performance-unnecessary-value-param)
{
	size_t i;

	i = 0;
	while (i < token.get_size())
	{
		if (token.get_beginning()[i] == '%')
		{
			if ((token.get_size() - i) < 3 || isalnum(token[i + 1]) == 0 || isalnum(token[i + 2]) == 0)
			{
				return (c_mutable_token());
			}
			token[i] = static_cast<char>(decode_hex_digit(token[i + 1]) * 16 + decode_hex_digit(token[i + 2]));
			token.shrink_by(2);
		}
		i++;
	}
	return (token);
}

static bool get_params_if_able(c_mutable_token &name, c_mutable_token &password, c_mutable_token &nick_name,
							   char *buffer)
{
	if (strncmp(buffer, "?name=", strlen("?name=")) != 0)
	{
		return (false);
	}
	buffer += strlen("?name=");
	name = get_base58_token(buffer);
	if (name.get_size() != 7)
	{
		return (false);
	}
	buffer += name.get_size();
	if (strncmp(buffer, "&password=", strlen("&password=")) != 0)
	{
		return (false);
	}
	buffer += strlen("&password=");
	password = get_base58_token(buffer);
	if (password.get_size() != 44)
	{
		return (false);
	}
	buffer += password.get_size();
	if (strncmp(buffer, "&nick_name=", strlen("&nick_name=")) != 0)
	{
		return (false);
	}
	buffer += strlen("&nick_name=");
	nick_name = decode_token(get_token(buffer));
	if (nick_name.get_size() > 30 || nick_name.get_size() == 0 || nick_name.is_valid() == false)
	{
		return (false);
	}
	name[name.get_size()] = '\0';
	password[password.get_size()] = '\0';
	nick_name[nick_name.get_size()] = '\0';
	return (true);
}

void create_account_handler(char *buffer, char const *query_beginning, PGconn *const dbconnection)
{
	PGresult       *res;
	c_mutable_token name;
	c_mutable_token password;
	c_mutable_token nick_name;

	// prepare statement
	buffer += query_beginning - buffer;
	if (get_params_if_able(name, password, nick_name, buffer) == false)
	{
		std::cerr << "api: error: invalid format for query parameters\n";
		return;
	}
	res = PQexecParams(dbconnection,
					   "insert into user_t (name, password, nick_name)"
					   "values ($1::char(7), $2::char(43), $3::varchar(30));",
					   3, nullptr,
					   (char const *[]){name.get_beginning(), password.get_beginning(), nick_name.get_beginning()},
					   nullptr, nullptr, RESULTS_IN_TEXT);
	int status = PQresultStatus(res);
	if (status != PGRES_COMMAND_OK)
	{
		if (status == PGRES_BAD_RESPONSE)
		{
			std::cerr << "api: error: internal database error\n";
		}
		else
		{
			std::cerr << "api: error: user could not be created because a user whit that name already exists\n";
		}
		PQclear(res);
		return;
	}
	std::cout << "api: successfully created account with:\n"
				 "\tname: "
			  << name.get_beginning()
			  << "\n"
				 "\tpassword: "
			  << password.get_beginning()
			  << "\n"
				 "\tnick_name: "
			  << nick_name.get_beginning() << "\n";
	PQclear(res);
}

#pragma GCC diagnostic pop
