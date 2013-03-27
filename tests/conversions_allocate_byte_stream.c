#include <check.h>
#include <stdlib.h>
#include "../src/conversions.h"

START_TEST (test_allocates_size)
{
	struct byte_stream stream;
	conversion_result_t result;

	result = allocate_byte_stream(&stream, 5);

	fail_unless(result == CONVERSION_SUCCESS, "Failed to allocate");
}
END_TEST

Suite *
conversions_allocate_byte_stream_suite(void)
{
	Suite *s = suite_create("Conversions: allocate_byte_stream");

	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_allocates_size);
	suite_add_tcase(s, tc_core);

	return s;
}

int
main(/* int argc, char **argv */)
{
	int number_failed;
	Suite *s = conversions_allocate_byte_stream_suite();
	SRunner *sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
