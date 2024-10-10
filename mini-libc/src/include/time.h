struct timespec {
	long tv_sec;	// seconds
	long tv_nsec; // nanoseconds
};
unsigned int sleep(unsigned int seconds);
int nanosleep(const struct timespec* request, struct timespec* remaining);
// source: https://www.codevscolor.com/c-nanosleep-example
// https://linuxhint.com/sleep-function-c/
