#include <errno.h>
#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <stdio.h>
#include <unistd.h>

int puts(const char* s) {
	int x = 0;
	for (; s[x] != '\0'; x++) {
	}
	int w1 = write(1, s, x);
	int w2 = write(1, "\n", 1);
	return w1 + w2;
}
