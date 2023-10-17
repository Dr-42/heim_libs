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
    int* vector = heim_vector_new(int);
    heim_vector_push(vector, 1);

    // printf("vec[0] = %d\n", vector[0]);

    // printf("vec[1] = %d\n", vector[1]);

    heim_vector_push(vector, 2);
    heim_vector_push(vector, 3);

    int a = 1;
    _heim_vector_push(vector, &a);

    heim_vector_push(vector, 4);

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
