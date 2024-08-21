/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: waiting_for_write_completion.cpp                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/08/16 20:40:42                                            */
/*   Updated:  2024/08/21 21:34:41                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../../../api.hpp"
#include "../../../c_io_uring_overseer/c_io_uring_overseer.hpp"
#include "../../../c_worker_id_to_text.hpp"
#include "../../../internal_strerror.hpp"
#include "../c_client_connection_handler.hpp"
#include "assert.h"
#include <cstring>
#include <iostream>
#include <liburing/io_uring.h>
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
;

void c_client_connection_handlers_overseer::c_client_connection_handler::waiting_for_write_completion(
	struct io_uring_cqe *cqe)
{
	struct io_uring_sqe *sqe;

	if (cqe->res < 1)
	{
		if (log_level >= LOG_INFO && cqe->res < 0)
		{
			std::cerr << std::string("PRIORITY=6\n") + "SYSLOG_FACILITY=3\n" +
							 "SYSLOG_IDENTIFIER=" + c_worker_id_to_text::get_name_from_id(worker_id) +
							 "\nMESSAGE=" + "failed to write: " + internal_strerror(errno);
		}
		close_connection(this);
		return;
	}
	pending_write_size -= static_cast<unsigned int>(cqe->res);
	already_writen += static_cast<unsigned int>(cqe->res);
	if (pending_write_size != 0)
	{
		sqe = g_io_uring_overseer->get_sqe();
		assert(sqe != nullptr);
		io_uring_prep_send(sqe, static_cast<int>(index), memory_shared_with_the_ring + already_writen,
						   pending_write_size, 0);
		sqe->flags |= IOSQE_FIXED_FILE;
		sqe->flags |= IORING_RECVSEND_FIXED_BUF;
		sqe->buf_index = 0;
		sqe->user_data = index;
		return;
	}
	already_writen = 0;
	notify_internal_step_completion();
}

#pragma GCC diagnostic pop
