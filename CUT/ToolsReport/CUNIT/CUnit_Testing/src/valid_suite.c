#include "CUnit/Basic.h"
#include "../include/valid.h"

int init_suite_valid(void)
{
return 0;
}

int clean_suite_valid(void)
{
return 0;
}

void testSunnyCases1(void)
{
CU_ASSERT_EQUAL(validation("data/unit_testcases/testCase1.txt"),1);
CU_ASSERT_EQUAL(validation("data/unit_testcases/testCase2.txt"),1);
CU_ASSERT_EQUAL(validation("data/unit_testcases/testCase3.txt"),1);
}
void testRainyCases1(void)
{
 CU_ASSERT_EQUAL(validation("data/unit_testcases/testCase4.txt"),0);
CU_ASSERT_EQUAL(validation("data/unit_testcases/testCase5.txt"),0);
CU_ASSERT_EQUAL(validation("data/unit_testcases/testCase6.txt"),0);
}
