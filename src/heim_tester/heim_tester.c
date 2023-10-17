/// define NO_COLOR to disable ANSI color codes before including this file
#include "heim_tester.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef NO_COLOR
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_RESET "\x1b[0m"
#else
#define ANSI_RED ""
#define ANSI_GREEN ""
#define ANSI_BLUE ""
#define ANSI_RESET ""
#endif

heim_tester* heim_tester_init(const char* name, heim_test_cmp_fn cmp_fn){
    heim_tester* tester = malloc(sizeof(heim_tester));
    tester->name = name;
    tester->cmp_fn = cmp_fn;

    tester->test_cases = NULL;
    tester->test_cases_count = 0;

    return tester;
}
void heim_tester_free(heim_tester* tester){
    for(size_t i = 0; i < tester->test_cases_count; i++){
        free(tester->test_cases[i].lhs);
        free(tester->test_cases[i].rhs);
    }
    free(tester->test_cases);
    free(tester);
}

void _heim_tester_add_test(heim_tester* tester, void* lhs, void* rhs, TestCaseType case_type, TestType test_type, size_t lhs_size, size_t rhs_size){
    void* lhs_copy = malloc(lhs_size);
    void* rhs_copy = malloc(rhs_size);
    memcpy(lhs_copy, lhs, lhs_size);
    memcpy(rhs_copy, rhs, rhs_size);
    heim_test_case test_case = {
        .lhs = lhs_copy,
        .rhs = rhs_copy,
        .type = test_type,
        .case_type = case_type,
    };
    tester->test_cases_count++;
    tester->test_cases = realloc(tester->test_cases, sizeof(heim_test_case) * tester->test_cases_count);
    memcpy(&tester->test_cases[tester->test_cases_count - 1], &test_case, sizeof(heim_test_case));
}

void heim_tester_run(heim_tester* tester){
    printf("%sRunning tests for %s\n%s", ANSI_BLUE, tester->name, ANSI_RESET);
    size_t passed_count = 0;
    size_t failed_count = 0;
    for(size_t i = 0; i < tester->test_cases_count; i++){
        heim_test_case* test_case = &tester->test_cases[i];
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
                    printf("\t%s%zu. Test supposed to pass...Passed, OK\n%s", ANSI_GREEN, i, ANSI_RESET);
                    passed_count++;
                }else{
                    printf("\t%s%zu. Test supposed to pass...Failed, ERR\n%s", ANSI_RED, i, ANSI_RESET);
                    failed_count++;
                }
                break;
            case TEST_TYPE_FAILING:
                if(passed){
                    printf("\t%s%zu. Test supposed to fail...Passed, ERR\n%s", ANSI_RED, i, ANSI_RESET);
                    passed_count++;
                }else{
                    printf("\t%s%zu. Test supposed to fail...Failed, OK\n%s", ANSI_GREEN, i, ANSI_RESET);
                    failed_count++;
                }
                break;
        }
    }
    printf("%sFor test %s,%s %s%zu passed%s, %s%zu failed%s\n\n",ANSI_BLUE, tester->name, ANSI_RED, ANSI_GREEN, passed_count, ANSI_RESET, ANSI_RED, failed_count, ANSI_RESET);
}
