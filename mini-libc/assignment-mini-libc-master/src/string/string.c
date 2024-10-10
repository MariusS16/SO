// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char* strcpy(char* destination, const char* source) {
	/* TODO: Implement strcpy(). */
	for (size_t index = 0; index < strlen(source) + 1; index++)
		destination[index] = source[index];
	return destination;
}

char* strncpy(char* destination, const char* source, size_t len) {
	/* TODO: Implement strncpy(). */
	for (size_t index = 0; index < len; index++)
		destination[index] = source[index];
	return destination;
}

char* strcat(char* destination, const char* source) {
	/* TODO: Implement strcat(). */
	size_t destination_index = strlen(destination);
	size_t source_index = 0;
	for (; source_index < strlen(source) + 1; destination_index++, source_index++)
		destination[destination_index] = source[source_index];
	return destination;
}

char* strncat(char* destination, const char* source, size_t len) {
	/* TODO: Implement strncat(). */
	size_t destination_index = strlen(destination);
	size_t source_index = 0;
	for (; source_index < len; destination_index++, source_index++)
		destination[destination_index] = source[source_index];
	destination[destination_index] = '\0';
	return destination;
}

int strcmp(const char* str1, const char* str2) {
	/* TODO: Implement strcmp(). */
	for (size_t index = 0; index < strlen(str1) + 1; index++)
		if (str1[index] != str2[index])
			return str1[index] - str2[index];
	return 0;
}

int strncmp(const char* str1, const char* str2, size_t len) {
	/* TODO: Implement strncmp(). */
	for (size_t index = 0; index < len; index++)
		if (str1[index] != str2[index])
			return str1[index] - str2[index];
	return str1[len - 1] - str2[len - 1];
}

size_t strlen(const char* str) {
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char* strchr(const char* str, int c) {
	/* TODO: Implement strchr(). */
	for (size_t index = 0; index < strlen(str) + 1; index++)
		if (str[index] == c)
			return &str[index];
	return NULL;
}

char* strrchr(const char* str, int c) {
	/* TODO: Implement strrchr(). */
	for (size_t index = strlen(str); index > 0; index--)
		if (str[index] == c)
			return &str[index];
	return NULL;
}

char* strstr(const char* haystack, const char* needle) {
	/* TODO: Implement strstr(). */
	for (size_t haystack_index = 0; haystack_index < strlen(haystack) + 1; haystack_index++)
		if (haystack[haystack_index] == needle[0]) {
			for (size_t needle_index = 0; needle_index < strlen(needle) + 1; needle_index++)
				if (haystack[haystack_index + needle_index] != needle[needle_index])
					break;
				else if (needle_index == strlen(needle) - 1)
					return &haystack[haystack_index];
		}
	return NULL;
}

char* strrstr(const char* haystack, const char* needle) {
	/* TODO: Implement strrstr(). */
	for (size_t haystack_index = strlen(haystack); haystack_index > 0; haystack_index--)
		if (haystack[haystack_index] == needle[0]) {
			for (size_t needle_index = 0; needle_index < strlen(needle) + 1; needle_index++)
				if (haystack[haystack_index + needle_index] != needle[needle_index])
					break;
				else if (needle_index == strlen(needle) - 1)
					return &haystack[haystack_index];
		}
	return NULL;
}

void* memcpy(void* destination, const void* source, size_t num) {
	/* TODO: Implement memcpy(). */
	for (size_t index = 0; index < num; index++)
		((unsigned char*)destination)[index] = ((unsigned char*)source)[index];
	return destination;
}

void* memmove(void* destination, const void* source, size_t num) {
	/* TODO: Implement memmove(). */
	for (size_t index = 0; index < num; index++)
		((unsigned char*)destination)[index] = ((unsigned char*)source)[index];
	return destination;
}

int memcmp(const void* ptr1, const void* ptr2, size_t num) {
	/* TODO: Implement memcmp(). */
	for (size_t index = 0; index < num; index++)
		if (((unsigned char*)ptr1)[index] != ((unsigned char*)ptr2)[index])
			return ((unsigned char*)ptr1)[index] - ((unsigned char*)ptr2)[index];
	return ((unsigned char*)ptr1)[num - 1] - ((unsigned char*)ptr2)[num - 1];
}

void* memset(void* source, int value, size_t num) {
	/* TODO: Implement memset(). */
	for (size_t index = 0; index < num; index++)
		((unsigned char*)source)[index] = value;
	return source;
}
