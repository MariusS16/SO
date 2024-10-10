// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <sys/mman.h>

void* mmap(void* addr, size_t length, int prot, int flags, int fd, off_t offset) {
	/* TODO: Implement mmap(). */
	// if (flags | MAP_PRIVATE) {
	// 	if (flags | MAP_SHARED) {
	// 		errno = EINVAL;
	// 		return MAP_FAILED;
	// 	}
	// }

	void* ret = (void*)syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

	if (ret < 0) {
		errno = -(int)ret;
		return MAP_FAILED;
	}

	return ret;
}

void* mremap(void* old_address, size_t old_size, size_t new_size, int flags) {
	/* TODO: Implement mremap(). */
	void* ret = (void*)syscall(__NR_mremap, old_address, old_size, new_size, flags);

	if (ret < 0) {
		errno = -(int)ret;
		return MAP_FAILED;
	}

	return ret;
}

int munmap(void* addr, size_t length) {
	/* TODO: Implement munmap(). */
	int ret = syscall(__NR_munmap, addr, length);
	if (ret < 0) {
		errno = -ret;
		return -1;
	}
	return ret;
}
