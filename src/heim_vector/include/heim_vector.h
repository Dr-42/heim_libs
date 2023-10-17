#pragma once

#include <stddef.h>

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
