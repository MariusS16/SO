// SPDX-License-Identifier: BSD-3-Clause

#include <internal/essentials.h>
#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void* malloc(size_t size) {
	/* TODO: Implement malloc(). */
	void* ret = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ret != NULL)
		mem_list_add(ret, size);
	return ret;
}

void* calloc(size_t nmemb, size_t size) {
	/* TODO: Implement calloc(). */
	void* ptr = mmap(NULL, nmemb * size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr != NULL) {
		mem_list_add(ptr, nmemb * size);
		memset(ptr, 0, nmemb * size);
	}
	return ptr;
}

void free(void* ptr) {
	struct mem_list* mem_list_ptr = mem_list_find(ptr);
	if (mem_list_ptr != NULL) {
		munmap(mem_list_ptr->start, mem_list_ptr->len);
		mem_list_del(ptr);
	}
	/* TODO: Implement free(). */
}

void* realloc(void* ptr, size_t size) {
	/* TODO: Implement realloc(). */
	struct mem_list* mem_list_ptr = mem_list_find(ptr);
	if (mem_list_ptr != NULL) {
		void* ret = mremap(mem_list_ptr->start, mem_list_ptr->len, size, 0);
		mem_list_del(ptr);
		mem_list_add(ret, size);
		return ret;
	}
	return NULL;
}

void* reallocarray(void* ptr, size_t nmemb, size_t size) {
	/* TODO: Implement reallocarray(). */
	struct mem_list* mem_list_ptr = mem_list_find(ptr);
	if (mem_list_ptr != NULL) {
		void* ret = mremap(mem_list_ptr->start, mem_list_ptr->len, nmemb * size, 0);
		mem_list_del(ptr);
		mem_list_add(ret, nmemb * size);
		return ret;
	}
	return NULL;
}
