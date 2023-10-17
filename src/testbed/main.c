#include <stdio.h>

#include <heim_vector.h>
#include <heim_tester.h>

int int_cmp(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

void test_vector(){
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int f = 5;
    int* vector = heim_vector_new(int);
    heim_tester* tester = heim_tester_init("Heim Vector", int_cmp);

    heim_vector_push(vector, &a);
    heim_vector_push(vector, &b);
    heim_vector_push(vector, &c);
    heim_vector_push(vector, &d);

    heim_tester_add_eq_p(tester, &vector[0], &a);
    heim_tester_add_eq_p(tester, &vector[1], &b);
    heim_tester_add_eq_p(tester, &vector[2], &c);
    heim_tester_add_eq_p(tester, &vector[3], &d);

    int popped;
    heim_vector_pop(&popped, vector);
    heim_tester_add_eq_p(tester, &popped, &d);

    heim_vector_pop_at(&popped, vector, 1);
    heim_tester_add_eq_p(tester, &popped, &b);

    heim_vector_insert(vector, &f, 0);
    heim_tester_add_eq_p(tester, &vector[0], &f);

    heim_vector_free(vector);
    heim_tester_run(tester);
    heim_tester_free(tester);
}

int main() {
    test_vector();
    return 0;
}
