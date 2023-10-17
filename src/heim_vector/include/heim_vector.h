#pragma once

#include <stddef.h>

// API
#define heim_vector_new(type) (type*)_heim_vector_new(sizeof(type))
#define heim_vector_free(ptr) _heim_vector_free(ptr)

#define heim_vector_push(ptr, item) _heim_vector_push(	\
						(void*)ptr,						\
						(void*)item						\
)

#define heim_vector_pop(dst, ptr) _heim_vector_pop(	\
						(void*)dst,					\
						(void*)ptr					\
)

#define heim_vector_insert(ptr, item, index) _heim_vector_insert(	\
						(void*)ptr,									\
						(void*)item,								\
						(size_t)index								\
)

#define heim_vector_pop_at(dst, ptr, index) _heim_vector_pop_at(\
						(void*)dst,								\
						(void*)ptr,								\
						(size_t)index							\
)

// Internal vector implementation
void* _heim_vector_new(size_t size);
void _heim_vector_free(void* ptr);

size_t heim_vector_size(void* ptr);
size_t heim_vector_capacity(void* ptr);

void heim_vector_clear(void* ptr);
void heim_vector_reserve(void* ptr, size_t size);
void heim_vector_shrink(void* ptr);

void _heim_vector_push(void* ptr, void* item);
void _heim_vector_pop(void* dst, void* ptr);
void _heim_vector_insert(void* ptr, void* item, size_t index);
void _heim_vector_pop_at(void* dst, void* ptr, size_t index);

void _heim_vector_resize(void* ptr, size_t size);
