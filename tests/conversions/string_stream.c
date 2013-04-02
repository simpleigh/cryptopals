#include "conversions.h"
#include "../../src/lib/conversions.h"
#include <check.h>

static unsigned char bad_characters[] = { 0, 31, 127, 255 };

START_TEST(test_byte_stream_to_string_bad_char)
{
	struct byte_stream stream;
	char *string;
	conversion_result_t result;

	stream.bytec = 1;
	stream.bytev = bad_characters + _i;

	result = byte_stream_to_string(stream, &string);

	fail_unless(result == CONVERSION_FAILURE, "Returned OK but bad character");
	fail_unless(string == NULL, "Set string pointer but bad character");
}
END_TEST

START_TEST(test_byte_stream_to_string_good)
{
	struct byte_stream stream;
	unsigned char bytev[] = { 'H', 'e', 'l', 'l', 'o' };
	char *string;
	conversion_result_t result;

	stream.bytec = 5;
	stream.bytev = bytev;

	result = byte_stream_to_string(stream, &string);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed");
	fail_unless(strlen(string) == 5, "Converted string wrong length");
	fail_unless(strcmp(string, "Hello") == 0, "Conversion incorrect");
}
END_TEST

START_TEST(test_string_to_byte_stream)
{
	struct byte_stream stream;
	conversion_result_t result;
	unsigned char expected[] = { 'H', 'e', 'l', 'l', 'o' };
	size_t i;

	result = string_to_byte_stream("Hello", &stream);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed");
	fail_unless(size_byte_stream(stream) == 5, "Wrong length");
	fail_unless(strncmp(stream.bytev, expected, 5) == 0, "Wrong result");
}
END_TEST

Suite *
conversions_string_stream_suite(void)
{
	Suite *s = suite_create("Conversions: string <=> byte stream");
	TCase *tc_core = tcase_create("Core");

	tcase_add_loop_test(tc_core, test_byte_stream_to_string_bad_char, 0, 4);
	tcase_add_test(tc_core, test_byte_stream_to_string_good);
	tcase_add_test(tc_core, test_string_to_byte_stream);

	suite_add_tcase(s, tc_core);
	return s;
}
