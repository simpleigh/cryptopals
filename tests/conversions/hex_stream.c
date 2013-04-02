#include "conversions.h"
#include "../../src/lib/conversions.h"
#include <check.h>
#include <string.h>

START_TEST(test_byte_stream_to_hex_stream)
{
	struct byte_stream stream;
	unsigned char bytev[] = { 'H', 'e', 'l', 'l', 'o' };
	char *hex_stream;
	conversion_result_t result;

	stream.bytec = 5;
	stream.bytev = bytev;

	result = byte_stream_to_hex_stream(stream, &hex_stream);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed");
	fail_unless(strlen(hex_stream) == 10, "Converted stream wrong length");
	fail_unless(strcmp(hex_stream, "48656c6c6f") == 0, "Conversion incorrect");
}
END_TEST

START_TEST(test_hex_stream_to_byte_stream_bad_length)
{
	struct byte_stream stream;
	conversion_result_t result;

	result = hex_stream_to_byte_stream("123", &stream);

	fail_unless(result == CONVERSION_FAILURE, "Returned OK but bad length");
}
END_TEST

START_TEST(test_hex_stream_to_byte_stream_bad_character)
{
	struct byte_stream stream;
	conversion_result_t result;

	result = hex_stream_to_byte_stream("123#", &stream);

	fail_unless(result == CONVERSION_FAILURE, "Returned OK but bad character");
	fail_unless(size_byte_stream(stream) == 0, "Stream left with length");
	fail_unless(stream.bytev == NULL, "Stream left with pointer");
}
END_TEST

START_TEST(test_hex_stream_to_byte_stream_good)
{
	struct byte_stream stream;
	conversion_result_t result;
	unsigned char expected[] = { 'H', 'e', 'l', 'l', 'o' };
	size_t i;

	result = hex_stream_to_byte_stream("48656c6c6f", &stream);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed");
	fail_unless(size_byte_stream(stream) == 5, "Wrong length");
	fail_unless(strncmp(stream.bytev, expected, 5) == 0, "Wrong result");
}
END_TEST

Suite *
conversions_hex_stream_suite(void)
{
	Suite *s = suite_create("Conversions: hex stream <=> byte stream");
	TCase *tc_core = tcase_create("Core");

	tcase_add_test(tc_core, test_byte_stream_to_hex_stream);
	tcase_add_test(tc_core, test_hex_stream_to_byte_stream_bad_length);
	tcase_add_test(tc_core, test_hex_stream_to_byte_stream_bad_character);
	tcase_add_test(tc_core, test_hex_stream_to_byte_stream_good);

	suite_add_tcase(s, tc_core);
	return s;
}
