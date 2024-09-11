/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_token.hpp                                                    */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/08 17:46:45                                            */
/*   Updated:  2024/09/09 11:40:38                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <compare>
#include <cstddef>
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

class c_token
{
	private:
		char const *beginning;
		char const *end;
		size_t      size;

	public:
		c_token(char const *beginning_exemplum, char const *end_exemplum);
		c_token(c_token const &exemplum);
		explicit c_token(char const *exemplum);
		c_token(void);

		c_token const       &operator=(c_token const &exemplum);
		std::strong_ordering operator<=>(c_token const &exemplum) const;
		char const          &operator[](size_t i) const;

		bool                 is_valid(void) const;

		char const          *get_beginning(void) const;
		char const          *get_end(void) const;
		size_t               get_size(void) const;
};

class c_mutable_token
{
	private:
		char  *beginning;
		char  *end;
		size_t size;

	public:
		c_mutable_token(char *beginning_exemplum, char *end_exemplum);
		c_mutable_token(c_mutable_token &exemplum);
		explicit c_mutable_token(char *exemplum);
		c_mutable_token(void);

		c_mutable_token const &operator=(c_mutable_token const &exemplum);
		std::strong_ordering   operator<=>(c_mutable_token const &exemplum) const;
		char                  &operator[](size_t i) const;

		bool                   is_valid(void) const;

		char                  *get_beginning(void) const;
		char                  *get_end(void) const;
		size_t                 get_size(void) const;

		void                   shrink_by(size_t value);
};

#pragma GCC diagnostic pop
