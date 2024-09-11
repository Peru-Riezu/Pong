/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: decode_query_params.hpp                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/09/06 23:30:19                                            */
/*   Updated:  2024/09/09 12:50:28                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../c_token/c_token.hpp"
#include "c_uint256.hpp"
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>

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

inline c_token get_token_value(char const *token_beginning, char const *token_end)
{
	char const *const equal_sign = reinterpret_cast<char const *>(
		memchr(token_beginning, '=', static_cast<size_t>(token_end - token_beginning) + 1));
	char const *const hard_end =
		reinterpret_cast<char const *>(memchr(equal_sign, '&', static_cast<size_t>(token_end - equal_sign) + 1));
	char const *beginning;
	char const *end;

	if (equal_sign == nullptr)
	{
		return (c_token());
	}
	beginning = equal_sign + 1;
	if (hard_end == nullptr)
	{
		end = token_end;
	}
	else
	{
		end = hard_end - 1;
	}
	return (c_token(beginning, end));
}

inline uint64_t decode_base58_char(char c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (static_cast<unsigned>(c - 'A' + 10));
	}
	if (c >= 'a' && c <= 'z')
	{
		return (static_cast<unsigned>(c - 'a' + 10 + ('Z' - 'A') + 1));
	}
	return (static_cast<unsigned>(c - '0'));
}

inline std::optional<uint64_t> decode_7_numeral(c_token const &token)
{
	uint64_t res;

	if (token.is_valid() == false || token.get_size() != 7)
	{
		return (std::nullopt);
	}
	res = 0;
	for (size_t i = 0; i < token.get_size(); i++)
	{
		if (isalnum(token[i]) == 0)
		{
			return (std::nullopt);
		}
		res *= 58;
		res += decode_base58_char(token[i]);
	}
	return (res);
}

inline std::optional<c_uint256> decode_44_numeral(c_token const &token)
{
	c_uint256 res(0);

	if (token.is_valid() == false || token.get_size() != 44)
	{
		return (std::nullopt);
	}
	for (size_t i = 0; i < token.get_size(); i++)
	{
		if (isalnum(token[i]) == 0)
		{
			return (std::nullopt);
		}
		res = res * 58;
		res = res + decode_base58_char(token[i]);
	}
	return (res);
}

#pragma GCC diagnostic pop
