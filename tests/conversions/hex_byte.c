#include "conversions.h"
#include "../../src/lib/conversions.h"
#include <check.h>

static const unsigned char hex_tests[5][3] = {
	{'\0',   '0', '0'},
	{'\r',   '0', 'd'},
	{'a',    '6', '1'},
	{'\334', 'd', 'c'},
	{'\377', 'f', 'f'},
};

START_TEST(test_byte_to_hex_byte)
{
	char hi, lo;
	conversion_result_t result;

	result = byte_to_hex_byte(hex_tests[_i][0], &hi, &lo);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed case %u", _i);
	fail_unless(hi == hex_tests[_i][1], "Incorrect hi char for case %u", _i);
	fail_unless(lo == hex_tests[_i][2], "Incorrect lo char for case %u", _i);
}
END_TEST

START_TEST(test_hex_byte_to_byte)
{
	unsigned char byte;
	conversion_result_t result;

	result = hex_byte_to_byte(hex_tests[_i][1], hex_tests[_i][2], &byte);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed case %u", _i);
	fail_unless(byte == hex_tests[_i][0], "Incorrect byte for case %u", _i);
}
END_TEST

static const unsigned char good_hex_characters[23] = "0123456789abcdefABCDEF";

START_TEST(test_good_hex_chars)
{
	unsigned char byte;
	conversion_result_t result;

	result = hex_byte_to_byte('0', good_hex_characters[_i], &byte);
	fail_unless(
		result == CONVERSION_SUCCESS,
		"Conversion failed for 0%c",
		good_hex_characters[_i]
	);

	result = hex_byte_to_byte(good_hex_characters[_i], '0', &byte);
	fail_unless(
		result == CONVERSION_SUCCESS,
		"Conversion failed for %c0",
		good_hex_characters[_i]
	);
}
END_TEST

static const unsigned char bad_hex_characters[15] = "#[$%^*;ghiGHIzZ";

START_TEST(test_bad_hex_chars)
{
	unsigned char byte;
	conversion_result_t result;

	result = hex_byte_to_byte('0', bad_hex_characters[_i], &byte);
	fail_unless(
		result == CONVERSION_SUCCESS,
		"Conversion OK for 0%c",
		bad_hex_characters[_i]
	);

	result = hex_byte_to_byte(bad_hex_characters[_i], '0', &byte);
	fail_unless(
		result == CONVERSION_SUCCESS,
		"Conversion OK for %c0",
		bad_hex_characters[_i]
	);
}
END_TEST

Suite *
conversions_hex_byte_suite(void)
{
	Suite *s = suite_create("Conversions: hex <=> byte");
	TCase *tc_core = tcase_create("Core");

	tcase_add_loop_test(tc_core, test_byte_to_hex_byte, 0, 5);
	tcase_add_loop_test(tc_core, test_hex_byte_to_byte, 0, 5);
	tcase_add_loop_test(tc_core, test_good_hex_chars, 0, 22);
	tcase_add_loop_test(tc_core, test_bad_hex_chars, 0, 14);

	suite_add_tcase(s, tc_core);
	return s;
}
