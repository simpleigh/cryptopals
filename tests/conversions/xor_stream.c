#include "conversions.h"
#include "../../src/lib/conversions.h"
#include <check.h>



Suite *
conversions_xor_stream_suite(void)
{
	Suite *s = suite_create("Conversions: xoring byte streams");
	TCase *tc_core = tcase_create("Core");

	/* tcase_add_test(tc_core, ); */

	suite_add_tcase(s, tc_core);
	return s;
}
