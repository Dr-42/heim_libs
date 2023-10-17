#include "heim_tester.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

heim_tester* heim_tester_init(const char* name, heim_test_cmp_fn cmp_fn){
    heim_tester* tester = malloc(sizeof(heim_tester));
    tester->name = name;
    tester->cmp_fn = cmp_fn;

    tester->test_cases = NULL;
    tester->test_cases_count = 0;

    return tester;
}
void heim_tester_free(heim_tester* tester){
    free(tester->test_cases);
    free(tester);
}

void heim_tester_add_test(heim_tester* tester, void* lhs, void* rhs, TestCaseType case_type, TestType test_type){
    heim_test_case test_case = {
        .lhs = lhs,
        .rhs = rhs,
        .type = test_type,
        .case_type = case_type,
    };
    tester->test_cases_count++;
    tester->test_cases = realloc(tester->test_cases, sizeof(heim_test_case) * tester->test_cases_count);
    memcpy(&tester->test_cases[tester->test_cases_count - 1], &test_case, sizeof(heim_test_case));
}

void heim_tester_run(heim_tester* tester){
    printf("Running tests for %s\n", tester->name);
    size_t passed_count = 0;
    size_t failed_count = 0;
    for(size_t i = 0; i < tester->test_cases_count; i++){
        heim_test_case* test_case = &tester->test_cases[i];
        printf("Running test %zu\n", i);
        int result = tester->cmp_fn(test_case->lhs, test_case->rhs);
        bool passed = false;
        switch(test_case->case_type){
            case TEST_CASE_TYPE_EQ:
                passed = result == 0;
                break;
            case TEST_CASE_TYPE_NEQ:
                passed = result != 0;
                break;
            case TEST_CASE_TYPE_LT:
                passed = result < 0;
                break;
            case TEST_CASE_TYPE_LTE:
                passed = result <= 0;
                break;
            case TEST_CASE_TYPE_GT:
                passed = result > 0;
                break;
            case TEST_CASE_TYPE_GTE:
                passed = result >= 0;
                break;
        }
        switch (test_case->type) {
            case TEST_TYPE_PASSING:
                if(passed){
                    printf("Test supposed to pass...Passed, OK\n");
                    passed_count++;
                }else{
                    printf("Test supposed to pass...Failed, ERR\n");
                    failed_count++;
                }
                break;
            case TEST_TYPE_FAILING:
                if(passed){
                    printf("Test supposed to fail...Passed, ERR\n");
                    passed_count++;
                }else{
                    printf("Test supposed to fail...Failed, OK\n");
                    failed_count++;
                }
                break;
        }
    }
    printf("For test %s, %zu passed, %zu failed\n", tester->name, passed_count, failed_count);
}
