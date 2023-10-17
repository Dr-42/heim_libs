#include <stdio.h>

#include <heim_vector.h>

void dump_vector(int* vector) {
    printf("[");
    for (int i = 0; i < heim_vector_size(vector); i++) {
        printf("%d,", vector[i]);
    }
    printf("]\n");
}

int main() {
    int* vector = (int*)_heim_vector_new(sizeof(int));
    _heim_vector_push(vector, &(int){1});
    _heim_vector_push(vector, &(int){2});
    _heim_vector_push(vector, &(int){3});
    _heim_vector_push(vector, &(int){4});

    dump_vector(vector);

    int popped;
    _heim_vector_pop(&popped, vector);
    printf("Popped last: %d\n", (int)popped);

    _heim_vector_pop_at(&popped, vector, 1);
    printf("Popped at 1: %d\n", (int)popped);
    dump_vector(vector);

    _heim_vector_insert(vector, &(int){5}, 0);
    dump_vector(vector);

    return 0;
}
