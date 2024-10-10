// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>

int ftruncate(int fd, off_t length) {
	/* TODO: Implement ftruncate(). */
	// codul de mai jos este este acelasi ca in close.c dar cu syscall-ul __NR_ftruncate
	int ret = syscall(__NR_ftruncate, fd, length);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
	return -1;
}
