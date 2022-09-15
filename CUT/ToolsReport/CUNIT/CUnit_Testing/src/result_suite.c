#include "CUnit/Basic.h"
#include "../include/result.h"

int init_suite_result(void)
{
return 0;
}

int clean_suite_result(void)
{
return 0;
}

void testSunnyCases2(void)
{
CU_ASSERT_EQUAL(result_Valid("Computer Aided Chemical Engineering"),3);
CU_ASSERT_EQUAL(result_Valid("Pipeline Scheduling"),2);
CU_ASSERT_EQUAL(result_Valid("Transportation"),3);
}
void testRainyCases2(void)
{
 CU_ASSERT_EQUAL(result_Valid("Transporthhhhh"),0);
CU_ASSERT_EQUAL(result_Valid("Capgemini"),0);
CU_ASSERT_EQUAL(result_Valid("testCase"),0);
}
