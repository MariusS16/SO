// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <unistd.h>

int close(int fd) {
	/* TODO: Implement close(). */
	// codul este acelasi ca in read_write dar cu syscall-ul __NR_close
	int ret = syscall(__NR_close, fd);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
	return -1;
}
