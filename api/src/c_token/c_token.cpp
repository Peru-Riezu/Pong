/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_token.cpp                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/08 18:01:18                                            */
/*   Updated:  2024/07/08 18:12:53                                            */
/*                                                                            */
/* ************************************************************************** */
#include "c_token.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>


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

c_token::c_token(char const *beginning_exemplum, char const *end_exemplum) : beginning(beginning_exemplum), end(end_exemplum),
	size(static_cast<size_t>((end - beginning_exemplum) + 1))
{

}

c_token::c_token(c_token const &exemplum) : beginning(exemplum.beginning), end(exemplum.end), size(exemplum.size)
{

}

c_token::c_token(char const *exemplum) : beginning(exemplum), end(exemplum + strlen(exemplum) - 1), size(strlen(exemplum))
{

}

c_token const &c_token::operator=(c_token const &exemplum)
{
	if (this != &exemplum)
	{
		beginning = exemplum.beginning;
		end = exemplum.end;
		size = exemplum.size;
	}
	return (*this);
}

bool c_token::operator<(c_token const &exemplum) const
{
	int const cmp_res = strncmp(beginning, exemplum.get_beginning(), std::min(size, exemplum.size));

	if (cmp_res < 0)
	{
		return (true);
	}
	return (false);
}

char const *c_token::get_beginning(void) const
{
	return (beginning);
}

char const *c_token::get_end(void) const
{
	return (end);
}

size_t      c_token::get_size(void) const
{
	return (size);
}

#pragma GCC diagnostic pop
