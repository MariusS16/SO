// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>

int open(const char* filename, int flags, ...) {
	/* TODO: Implement open system call. */
	// codul este acelasi ca in read_write dar cu syscall-ul __NR_open
	int ret = syscall(__NR_open, filename, flags);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
	return -1;
}
