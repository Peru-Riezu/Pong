/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: api.hpp                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/07 07:11:35                                            */
/*   Updated:  2024/07/27 01:46:15                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <fcntl.h>

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
#pragma GCC diagnostic ignored "-Wc11-extensions"
;

// clang-format off
#define API_WORKER_COUNT           1
#define STRINGIFY(x)               (char[]){#x}
#define TOSTRING(x)                STRINGIFY(x)
#define API_WORKER_COUNT_STR       TOSTRING(API_WORKER_COUNT)
#define API_SOCKET_PATH            ((char[]){"./api_sockets/"})
// clang-format on

#define NO_EXPAND_DBNAME    0
#define RESULTS_IN_TEXT     0
#define RESULTS_IN_BINARY   1

#define SQ_SIZE             1024
#define CQ_SIZE             65536
#define MAX_CONN_PER_WORKER 100000
#define MEM_PER_CONN        4480          // bytes
_Static_assert(MEM_PER_CONN >= 4480, ""); // the minimum size of the uninx domain socket send buffer is 4608
										  // and a message contains 128 bytes of headers

#define DBCONN_POOL_SIZE 3334

#pragma GCC diagnostic pop
