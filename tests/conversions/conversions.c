#include "conversions.h"
#include <check.h>
#include <stdlib.h>

Suite *
conversions_root_suite(void)
{
	Suite *s = suite_create("Conversions");
	return s;
}

int
main(/* int argc, char **argv */)
{
	SRunner *sr;
	int number_failed;

	sr = srunner_create(conversions_root_suite());
	srunner_add_suite(sr, conversions_byte_stream_suite());
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
