#include <errno.h>
#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

unsigned int sleep(unsigned int seconds) {
	struct timespec t = {.tv_sec = seconds, .tv_nsec = 0};
	struct timespec r = {.tv_sec = 0, .tv_nsec = 0};

	int ret = nanosleep(&t, &r);

	if (ret == -1) {
		if (r.tv_sec + r.tv_nsec > 0) {
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}
