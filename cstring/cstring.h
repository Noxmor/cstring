#ifndef CSTRING_H
#define CSTRING_H

#include <stdlib.h>
#include <string.h>

typedef struct
{
	size_t size;
	char* data;
} cstring;

cstring* cstring_create_empty(size_t len)
{
	cstring* str = malloc(sizeof(str));
	str->size = len + 1;
	str->data = calloc(str->size, sizeof(char));
	str->data[len] = '\0';
	return str;
}

cstring* cstring_create(const char* str)
{
	if (str == NULL)
		return cstring_create_empty(0);
	
	size_t len = strlen(str);
	cstring* string = cstring_create_empty(len);
	memcpy(string->data, str, sizeof(char) * len);
	return string;
}

void cstring_delete(cstring* str)
{
	if (str == NULL)
		return;
	
	free(str->data);
	free(str);
}

//void cstring_realloc(cstring* str, size_t size)
//{
//	if (str == NULL || size == 0 || str->size == size)
//		return;
//
//	const char* old_data = str->data;
//
//	str->data = calloc(size, sizeof(char));
//	memcpy(str->data, old_data, sizeof(char) * (size > str->size ? str->size : size - 1));
//	str->size = size;
//	free(old_data);
//}

size_t cstring_len(cstring* str)
{
	if (str == NULL || str->data == NULL)
		return 0;
	
	for (size_t i = 0; i < str->size; i++)
	{
		if (str->data[i] == '\0')
			return i;
	}

	return 0;
}

//uint8_t cstring_compare(cstring* c_str, const char* str)
//{
//	if (!c_str || !str)
//		return 0;
//
//	size_t c_str_len = cstring_len(c_str);
//	size_t len = strlen(str);
//
//	
//}

void cstring_copy(cstring* dest, const cstring* src)
{
	if (dest == NULL || src == NULL || src->data == NULL)
		return;

	size_t len = cstring_len(src);
	if (len == 0)
		return;

	if(dest->size < len)
		//TODO: REALLOC

	for (size_t i = 0; i < len; i++)
		dest->data[i] = src[i];

	dest->data[len] = '\0';
}

void cstring_append(cstring* dest, const cstring* src)
{
	if (dest == NULL || src == NULL || src ->data)
		return;
	
	size_t len = cstring_len(src);
	cstring_realloc(c_str, c_str->size + len);

	size_t c_str_len = cstring_len(c_str);
	for (size_t i = 0; i < len; i++)
		c_str->data[c_str_len + i] = str[i];
}

void cstring_insert(cstring* c_str, size_t pos, const char* str)
{
	if (!c_str || !str)
		return;
	
	size_t len = strlen(str);
	cstring_realloc(c_str, c_str->size + len);
	
	for (size_t i = 0; i < len; i++)
	{
		if (c_str->data[pos + i] != '\0')
			c_str->data[pos + i + len] = c_str->data[pos + i];

		c_str->data[pos + i] = str[i];
	}
}

int cstring_find_char(cstring* c_str, char c)
{
	if (!c_str || c == '\0')
		return -1;

	size_t len = cstring_len(c_str);
	for (size_t i = 0; i < len; i++)
	{
		if (c_str->data[i] == c)
			return i;
	}

	return -1;
}

int cstring_find_reverse_char(cstring* c_str, char c)
{
	if (!c_str || c == '\0')
		return -1;

	size_t len = cstring_len(c_str);
	for (size_t i = 0; i < len; i++)
	{
		if (c_str->data[len - i] == c)
			return len - i;
	}

	return -1;
}

#endif