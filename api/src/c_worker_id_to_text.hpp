/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_worker_id_to_text.hpp                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/12 20:08:38                                            */
/*   Updated:  2024/07/13 09:45:55                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "api.hpp"
#include <string>

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
#pragma GCC diagnostic ignored "-Wglobal-constructors"
#pragma GCC diagnostic ignored "-Wgnu-designator"
#pragma GCC diagnostic ignored "-Wc99-extensions"
;

static inline class c_worker_id_to_text
{
	private:
		static inline char id_to_name[API_WORKER_COUNT][12 + sizeof(API_WORKER_COUNT_STR) - 1];
		static inline char id_to_socket_name[API_WORKER_COUNT]
											[sizeof(API_SOCKET_PATH) + 17 + sizeof(API_WORKER_COUNT_STR) - 1];

	public:
		c_worker_id_to_text(void)
		{
			for (size_t i = 0; i < API_WORKER_COUNT; i++)
			{
				strcpy(&id_to_name[i][0], ("api worker " + std::to_string(i + 1)).c_str());
				strcpy(&id_to_socket_name[i][0],
					   (std::string(API_SOCKET_PATH) + "api_worker_" + std::to_string(i + 1) + ".sock").c_str());
			}
		}

		static char const *get_name_from_id(int id)
		{
			return (&id_to_name[id - 1][0]);
		}

		static char const *get_socket_name_from_id(int id)
		{
			return (&id_to_socket_name[id - 1][0]);
		}
} worker_id_to_text;

#pragma GCC diagnostic pop
