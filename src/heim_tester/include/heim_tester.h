#pragma once

#include <stddef.h>
#include <stdbool.h>

// Returns negative if a < b, 0 if a == b, positive if a > b
typedef int (*heim_test_cmp_fn)(void* a, void* b);

typedef enum TestType{
	TEST_TYPE_PASSING,
	TEST_TYPE_FAILING,
} TestType;

typedef enum TestCaseType{
	TEST_CASE_TYPE_EQ,
	TEST_CASE_TYPE_NEQ,
	TEST_CASE_TYPE_LT,
	TEST_CASE_TYPE_LTE,
	TEST_CASE_TYPE_GT,
	TEST_CASE_TYPE_GTE,
} TestCaseType;

typedef struct heim_test_case {
	void* lhs;
	void* rhs;
	TestCaseType case_type;
	TestType type;
} heim_test_case;

typedef struct heim_tester {
	const char* name;
	heim_test_cmp_fn cmp_fn;
	heim_test_case* test_cases;
	size_t test_cases_count;
} heim_tester;


heim_tester* heim_tester_init(const char* name, heim_test_cmp_fn cmp_fn);
void heim_tester_free(heim_tester* tester);

void heim_tester_add_test(heim_tester* tester, void* lhs, void* rhs, TestCaseType case_type, TestType test_type);

void heim_tester_run(heim_tester* tester);
