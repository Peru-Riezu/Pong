/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_mutable_token.cpp                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/09 12:56:34                                            */
/*   Updated:  2024/07/09 13:03:35                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_token.hpp"
#include <algorithm>
#include <stdexcept>
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
;

c_mutable_token::c_mutable_token(char *beginning_exemplum, char *end_exemplum)
	: beginning(beginning_exemplum), end(end_exemplum), size(static_cast<size_t>((end - beginning_exemplum) + 1))
{
}

c_mutable_token::c_mutable_token(c_mutable_token &exemplum)
	: beginning(exemplum.beginning), end(exemplum.end), size(exemplum.size)
{
}

c_mutable_token::c_mutable_token(char *exemplum)
	: beginning(exemplum), end(exemplum + strlen(exemplum) - 1), size(strlen(exemplum))
{
}

c_mutable_token::c_mutable_token(void) : beginning(nullptr), end(nullptr), size(0)
{
}

c_mutable_token const &c_mutable_token::operator=(c_mutable_token const &exemplum)
{
	if (this != &exemplum)
	{
		beginning = exemplum.beginning;
		end = exemplum.end;
		size = exemplum.size;
	}
	return (*this);
}

std::strong_ordering c_mutable_token::operator<=>(c_mutable_token const &exemplum) const
{
	int const cmp_res = strncmp(beginning, exemplum.get_beginning(), std::min(size, exemplum.size));

	if (cmp_res == 0)
	{
		if (size == exemplum.size)
		{
			return (std::strong_ordering::equal);
		}
		if (size > exemplum.size)
		{
			return (std::strong_ordering::greater);
		}
		return (std::strong_ordering::less);
	}
	return (cmp_res <=> 0);
}

char &c_mutable_token::operator[](size_t i) const
{
	return (beginning[i]);
}

bool c_mutable_token::is_valid(void) const
{
	return (size != 0);
}

char *c_mutable_token::get_beginning(void) const
{
	return (beginning);
}

char *c_mutable_token::get_end(void) const
{
	return (end);
}

size_t c_mutable_token::get_size(void) const
{
	return (size);
}

void c_mutable_token::shrink_by(size_t value)
{
	if (value >= size)
	{
		throw(std::invalid_argument("attempt to shrink token by a value greater or equal than its size"));
	}
	size -= value;
	end -= value;
}

#pragma GCC diagnostic pop
