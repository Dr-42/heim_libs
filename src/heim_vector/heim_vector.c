#include "heim_vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_INITIAL_CAPACITY 2
#define VECTOR_RESIZE_FACTOR 2

#define todo() do{ \
	fprintf(stderr, "TODO : %s:%d %s\n", __FILE__, __LINE__, __func__); \
	exit(1); \
} while(0);

// Vector structure
// (size_t element_size) (size_t capacity) (size_t size) (char data[])

void* _heim_vector_new(size_t size){
	void* ptr = malloc(sizeof(size_t) * 3 + size);
	memset(ptr, 0, sizeof(size_t) * 3 + size);
	*(size_t*)ptr = size;
	*(size_t*)(ptr + sizeof(size_t)) = VECTOR_INITIAL_CAPACITY;
	*(size_t*)(ptr + sizeof(size_t) * 2) = 0;
	return ptr + sizeof(size_t) * 3;
}

void _heim_vector_free(void* ptr){
	free(ptr - sizeof(size_t) * 3);
}

size_t heim_vector_size(void* ptr){
	return *(size_t*)(ptr - sizeof(size_t));
}

size_t heim_vector_capacity(void* ptr){
	return *(size_t*)(ptr - sizeof(size_t) * 2);
}

void heim_vector_clear(void* ptr) {
	*(size_t*)(ptr - sizeof(size_t)) = 0;
}

void heim_vector_reserve(void* ptr, size_t size){
	size_t* vector = ptr - sizeof(size_t) * 3;
	size_t capacity = *(vector + 1);
	if (capacity < size){
		_heim_vector_resize(ptr, size);
	}
}

void heim_vector_shrink(void* ptr){
	size_t* vector = ptr - sizeof(size_t) * 3;
	size_t capacity = *(vector + 1);
	size_t size = *(vector + 2);
	if (capacity > size){
		_heim_vector_resize(ptr, size);
	}
}

void _heim_vector_resize(void* ptr, size_t size){
	size_t* vector = ptr - sizeof(size_t) * 3;
	size_t capacity = *(vector + 1);
	size_t new_capacity = capacity;
	while(new_capacity < size){
		new_capacity *= VECTOR_RESIZE_FACTOR;
	}
	vector = realloc(vector, sizeof(size_t) * 3 + new_capacity);
	*(vector + 1) = new_capacity;
}

void _heim_vector_push(void* ptr, void* item){
	if (ptr == NULL){
		fprintf(stderr, "Invalid vector pointer\n");
	}

	size_t element_size = *(size_t*)(ptr - sizeof(size_t) * 3);
	size_t capacity = *(size_t*)(ptr - sizeof(size_t) * 2);
	size_t size = *(size_t*)(ptr - sizeof(size_t));

	if (size == capacity){
		_heim_vector_resize(ptr, size + 1);
	}

	memcpy(ptr + size * element_size, item, element_size);
	*(size_t*)(ptr - sizeof(size_t)) = size + 1;
}

void _heim_vector_pop(void* dst, void* ptr){
	if (ptr == NULL){
		fprintf(stderr, "Invalid vector pointer\n");
	}

	size_t element_size = *(size_t*)(ptr - sizeof(size_t) * 3);
	size_t size = *(size_t*)(ptr - sizeof(size_t));

	if (size == 0){
		fprintf(stderr, "Trying to pop from empty vector\n");
		exit(1);
	}

	*(size_t*)(ptr - sizeof(size_t)) = size - 1;
	memcpy(dst, ptr + (size - 1) * element_size, element_size);
}

void _heim_vector_insert(void* ptr, void* item, size_t index){
	if (ptr == NULL){
		fprintf(stderr, "Invalid vector pointer\n");
	}

	size_t element_size = *(size_t*)(ptr - sizeof(size_t) * 3);
	size_t capacity = *(size_t*)(ptr - sizeof(size_t) * 2);
	size_t size = *(size_t*)(ptr - sizeof(size_t));

	if (index >= size){
		fprintf(stderr, "Index out of bounds\n");
		exit(1);
	}
	
	if (size == capacity){
		_heim_vector_resize(ptr, size + 1);
	}

	memmove(
		ptr + (index + 1) * element_size,
		ptr + index * element_size,
		(size - index) * element_size
	);

	memcpy(ptr + index * element_size, item, element_size);
	*(size_t*)(ptr - sizeof(size_t)) = size + 1;
}

void _heim_vector_pop_at(void* dst, void* ptr, size_t index) {
	if (ptr == NULL){
		fprintf(stderr, "Invalid vector pointer\n");
	}

	size_t element_size = *(size_t*)(ptr - sizeof(size_t) * 3);
	size_t size = *(size_t*)(ptr - sizeof(size_t));

	if (index >= size){
		fprintf(stderr, "Index out of bounds\n");
		exit(1);
	}
	
	void* item = ptr + index * element_size;
	memcpy(dst, item, element_size);

	memmove(
		ptr + index * element_size,
		ptr + (index + 1) * element_size,
		(size - index - 1) * element_size
	);
	*(size_t*)(ptr - sizeof(size_t)) = size - 1;
}
