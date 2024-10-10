#include <errno.h>
#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int nanosleep(const struct timespec* request, struct timespec* remaining) {
	int ret = syscall(__NR_nanosleep, request, remaining);

	if (ret < 0) {
		errno = -ret;
		return -1;
	}

	return ret;
	return -1;
}
