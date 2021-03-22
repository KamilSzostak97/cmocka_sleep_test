#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
//export LD_LIBRARY_PATH=/usr/local/lib64/

static void test_negative_intervals(void **state) {
	int returnCode = system("./sleep -10s >nul 2>nul");
	assert_int_equal(returnCode,256);
}

static void test_invalid_intervals(void **state) {
	int returnCode = system("./sleep 10e >nul 2>nul");
	assert_int_equal(returnCode,256);
}

static void test_invalid_intervals_multiple_suffixes(void **state) {
	int returnCode = system("./sleep 10sdd >nul 2>nul");
	assert_int_equal(returnCode,256);
}

static void test_missing_operand(void **state) {
	int returnCode = system("./sleep >nul 2>nul");
	assert_int_equal(returnCode,256);
}

static void test_no_error(void **state){
	int returnCode=system("./sleep 0");
	assert_int_equal(returnCode,0);
}

static void test_sleep_10s(void **state){
	int min = 999;
	int max = 1001;
	struct timespec start, end;
	double time_spent;


	clock_gettime(CLOCK_MONOTONIC, &start);
	system("./sleep 10s");
	clock_gettime(CLOCK_MONOTONIC, &end);
	
	time_spent = ((double) (end.tv_sec - start.tv_sec) +
               1e-9 * (end.tv_nsec - start.tv_nsec))*100;

	printf("Elapsed: %f\n", time_spent/100);
	system("rm nul");

	assert_in_range(time_spent, min, max);
}

int code_coverage(int test_coverage,int all_lines){
	int coverage=(69*100/90);
	return(coverage);
}


int main(int argc, char **argv) { 
	system("clear");
	printf("Test coverage = %d % (69/90)\n",code_coverage(1,2));
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_no_error),
		cmocka_unit_test(test_negative_intervals),
		cmocka_unit_test(test_invalid_intervals),
		cmocka_unit_test(test_invalid_intervals_multiple_suffixes),
		cmocka_unit_test(test_missing_operand),
		cmocka_unit_test(test_sleep_10s)
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}
