#pragma once

#include <stddef.h>
#include <stdbool.h>

// Returns negative if a < b, 0 if a == b, positive if a > b
typedef int (*heim_test_cmp_fn)(const void* a, const void* b) ;

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

void _heim_tester_add_test(heim_tester* tester, void* lhs, void* rhs, TestCaseType case_type, TestType test_type, size_t lhs_size, size_t rhs_size);

#define heim_tester_add_eq_p(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_EQ, TEST_TYPE_PASSING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_eq_f(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_EQ, TEST_TYPE_FAILING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_neq_p(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_NEQ, TEST_TYPE_PASSING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_neq_f(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_NEQ, TEST_TYPE_FAILING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_lt_p(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_LT, TEST_TYPE_PASSING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_lt_f(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_LT, TEST_TYPE_FAILING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_lte_p(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_LTE, TEST_TYPE_PASSING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_lte_f(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_LTE, TEST_TYPE_FAILING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_gt_p(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_GT, TEST_TYPE_PASSING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_gt_f(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_GT, TEST_TYPE_FAILING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_gte_p(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_GTE, TEST_TYPE_PASSING, sizeof(*lhs), sizeof(*rhs))

#define heim_tester_add_gte_f(tester, lhs, rhs) _heim_tester_add_test(tester, lhs, rhs, TEST_CASE_TYPE_GTE, TEST_TYPE_FAILING, sizeof(*lhs), sizeof(*rhs))


void heim_tester_run(heim_tester* tester);
