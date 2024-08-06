/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: c_io_uring_overseer.cpp                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/07/27 02:14:07                                            */
/*   Updated:  2024/08/06 01:49:33                                            */
/*                                                                            */
/* ************************************************************************** */

#include "c_io_uring_overseer.hpp"
#include "../c_worker_id_to_text.hpp"
#include "../internal_strerror.hpp"
#include <cerrno>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <liburing.h>
#include <liburing/io_uring.h>

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
;

c_io_uring_overseer::c_io_uring_overseer(void)
{
	struct io_uring_params params = {
		.sq_entries = SQ_SIZE,
		.cq_entries = CQ_SIZE,
		.flags = IORING_SETUP_CQSIZE | IORING_SETUP_SUBMIT_ALL | IORING_SETUP_COOP_TASKRUN | IORING_SETUP_SINGLE_ISSUER,
	}; // NOLINT
	struct iovec shared_buffers = {.iov_base = calloc(MAX_CONN_PER_WORKER, MEM_PER_CONN),
								   .iov_len = static_cast<size_t>(MAX_CONN_PER_WORKER) * MEM_PER_CONN};
	int          res;

	if (shared_buffers.iov_base == nullptr)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to allocate the shared buffer: " + internal_strerror(errno);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	shared_buffer = reinterpret_cast<uint8_t *>(shared_buffers.iov_base);
	res = io_uring_queue_init_params(SQ_SIZE, &ring, &params);
	if (res < 0)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to create io uring: " + internal_strerror(-res);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_ring_fd(&ring);
	if (res < 0)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to register io uring fd in io uring: " + internal_strerror(-res);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_files_sparse(&ring, MAX_CONN_PER_WORKER);
	if (res < 0)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "\nMESSAGE=" + "failed to register fd table io uring: " + internal_strerror(-res);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	res = io_uring_register_buffers(&ring, &shared_buffers, 1);
	if (res < 0)
	{
		std::cerr << std::string("PRIORITY=3\n")
				  + "SYSLOG_FACILITY=3\n"
				  + "SYSLOG_IDENTIFIER="
				  + c_worker_id_to_text::get_name_from_id(worker_id) + "\nMESSAGE="
				  + "failed to register the shared buffers in io uring: " + internal_strerror(-res);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
	g_io_uring_overseer = this;
}

c_io_uring_overseer::~c_io_uring_overseer(void)
{
}

void c_io_uring_overseer::register_file(int fd, unsigned int pos)
{
	int const res = io_uring_register_files_update(&ring, pos, (int[]){fd}, 1);
	if (res < 0)
	{
		std::cerr << std::string("PRIORITY=3\n") + "SYSLOG_FACILITY=3\n" + "SYSLOG_IDENTIFIER=\n" +
						 c_worker_id_to_text::get_name_from_id(worker_id) +
						 "MESSAGE=" + "failed to register fd in io uring: " + internal_strerror(-res);
		exit(EXIT_FAILURE); // NOLINT(concurrency-mt-unsafe)
	}
}

uint8_t *c_io_uring_overseer::get_shared_buffer(void)
{
	return (shared_buffer);
}

#pragma GCC diagnostic pop
