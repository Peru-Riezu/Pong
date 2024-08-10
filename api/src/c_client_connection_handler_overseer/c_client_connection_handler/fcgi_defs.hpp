/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: fcgi_defs.hpp                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/09 01:16:42                                            */
/*   Updated:  2024/08/10 05:53:29                                            */
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
#pragma GCC diagnostic ignored "-Wc99-designator"
;

#include <cstddef>

#define FCGI_BEGIN_REQUEST    1
#define FCGI_ABORT_REQUEST    2
#define FCGI_END_REQUEST      3
#define FCGI_PARAMS           4
#define FCGI_STDIN            5
#define FCGI_STDOUT           6
#define FCGI_STDERR           7
#define FCGI_DATA             8

#define FCGI_VERSION          1

#define FCGI_RESPONDER        1
#define FCGI_AUTHORIZER       2
#define FCGI_FILTER           3

#define FCGI_REQUEST_COMPLETE 0

#define FCGI_HEADER_LEN       8

struct s_fcgi_header
{
		unsigned char version;
		unsigned char type;
		unsigned char request_id_b1;
		unsigned char request_id_b0;
		unsigned char content_length_b1;
		unsigned char content_length_b0;
		unsigned char padding_length;
		unsigned char reserved;

		void          to_string(void);
		size_t        get_size(void);
};

struct s_fcgi_name_value_pair_small_value
{
		unsigned char name_length_b0;  /* nameLengthB0  >> 7 == 0 */
		unsigned char value_length_b0; /* valueLengthB0 >> 7 == 0 */

		void          to_string(void);
		size_t        get_size(void);
};

struct s_fcgi_begin_request_body
{
		unsigned char role_b1;
		unsigned char role_b0;
		unsigned char flags;
		unsigned char reserved[5];

		void          to_string(void);
};

struct s_fcgi_end_request_body
{
		unsigned char app_status_b3;
		unsigned char app_status_b2;
		unsigned char app_status_b1;
		unsigned char app_status_b0;
		unsigned char protocol_status;
		unsigned char reserved[3];

		void          to_string(void);
};

struct s_fcgi_end_request_record
{
		s_fcgi_header           header;
		s_fcgi_end_request_body body;

		void                    to_string(void);
		size_t                  get_size(void);
};

struct s_fcgi_begin_request_record
{
		s_fcgi_header             header;
		s_fcgi_begin_request_body body;

		void                      to_string(void);
		size_t                    get_size(void);
};

struct s_fcgi_params_record
{
		s_fcgi_header header;

		void          to_string(void);
		size_t        get_size(void);
};

inline char const *fcgi_type_to_str(unsigned char type)
{
	static char *table[] = {[FCGI_BEGIN_REQUEST] = "begin_request",
							[FCGI_ABORT_REQUEST] = "abort_request",
							[FCGI_END_REQUEST] = "end_request",
							[FCGI_PARAMS] = "params",
							[FCGI_STDIN] = "stdin",
							[FCGI_STDOUT] = "stdout",
							[FCGI_STDERR] = "stderr",
							[FCGI_DATA] = "data"};

	return (table[type]);
}

inline char const *fcgi_role_to_str(unsigned char b1, unsigned char b0)
{
	static char *table[] = {[FCGI_RESPONDER] = "responder", [FCGI_AUTHORIZER] = "authorizer", [FCGI_FILTER] = "filter"};

	return (table[(b1 << 8U) + b0]);
}

#pragma GCC diagnostic pop
