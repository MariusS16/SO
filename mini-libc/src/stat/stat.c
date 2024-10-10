// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <fcntl.h>
#include <internal/syscall.h>
#include <sys/stat.h>

int stat(const char* restrict path, struct stat* restrict buf) {
	/* TODO: Implement stat(). */
	////codul este acelasi ca in /io dar cu syscall-ul __NR_stat
	int ret = syscall(__NR_stat, path, buf);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
	return -1;
}
