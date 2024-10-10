// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <sys/stat.h>

int fstat(int fd, struct stat* st) {
	/* TODO: Implement fstat(). */
	// codul este acelasi ca in /io dar cu syscall-ul __NR_fstat
	int ret = syscall(__NR_fstat, fd, st);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
	return -1;
}
