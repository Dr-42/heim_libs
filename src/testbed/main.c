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
    printf("Heim Vector Test\n--------------\n\n");
    int* vector = heim_vector_new(int);
    
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int f = 5;

    heim_vector_push(vector, &a);
    heim_vector_push(vector, &b);
    heim_vector_push(vector, &c);
    heim_vector_push(vector, &d);
    dump_vector(vector);

    int popped;
    heim_vector_pop(&popped, vector);
    printf("Popped last: %d\n", (int)popped);

    heim_vector_pop_at(&popped, vector, 1);
    printf("Popped at 1: %d\n", (int)popped);
    dump_vector(vector);

    heim_vector_insert(vector, &f, 0);
    dump_vector(vector);

    heim_vector_free(vector);

    return 0;
}
