#include "conversions.h"
#include "../../src/lib/conversions.h"
#include <check.h>
#include <stdlib.h>

struct base64_testcase {
	unsigned char bytev[3];
	char base64[5];
};

struct base64_testcase test_cases[6] = {
	{ {   0,   0,   0 }, "AAAA" },
	{ {   0,   0,  46 }, "AAAu" },
	{ { 'M', 'a', 'n' }, "TWFu" },
	{ { 'a', 'n', 'y' }, "YW55" },
	{ { 151,  79, 191 }, "l0+/" },
	{ {  0,   16, 131 }, "ABCD" },
};

START_TEST(test_byte_stream_to_base64)
{
	struct byte_stream stream;
	char *base64_stream;
	conversion_result_t result;

	stream.bytec = 3;
	stream.bytev = &(test_cases[_i].bytev);

	result = byte_stream_to_base64(stream, &base64_stream);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed case %i", _i);
	fail_unless(
		strcmp(base64_stream, test_cases[_i].base64) == 0,
		"Wrong result for case %i",
		_i
	);

	free(base64_stream);
}
END_TEST

START_TEST(test_base64_to_byte_stream)
{
	struct byte_stream stream;
	char *base64_stream;
	conversion_result_t result;
	unsigned int j;

	base64_stream = &(test_cases[_i].base64);

	result = base64_to_byte_stream(base64_stream, &stream);

	fail_unless(result == CONVERSION_SUCCESS, "Conversion failed case %i", _i);
	fail_unless(size_byte_stream(stream) == 3, "Case %i wrong length", _i);

	for (j = 0; j < 3; j++) {
		fail_unless(
			stream.bytev[j] == test_cases[_i].bytev[j],
			"Byte %u wrong case %i",
			j,
			_i
		);
	}

	free_byte_stream(&stream);
}
END_TEST

START_TEST(test_base64_one_byte_high)
{
	struct byte_stream stream;
	char *base64_stream;
	conversion_result_t result;

	base64_stream = "/w==";
	result = base64_to_byte_stream(base64_stream, &stream);

	fail_unless(result == CONVERSION_SUCCESS, "One byte hi conversion failed");
	fail_unless(size_byte_stream(stream) == 1, "One byte hi wrong length");
	fail_unless(stream.bytev[0] == 255, "One byte hi wrong value");

	base64_stream = "****";
	result = byte_stream_to_base64(stream, &base64_stream);

	fail_unless(result == CONVERSION_SUCCESS, "One byte hi restore failed");
	fail_unless(strcmp(base64_stream, "/w==") == 0, "One byte hi restore bad");

	free_byte_stream(&stream);
	free(base64_stream);
}
END_TEST

START_TEST(test_base64_one_byte_low)
{
	struct byte_stream stream;
	char *base64_stream;
	conversion_result_t result;

	base64_stream = "AA==";
	result = base64_to_byte_stream(base64_stream, &stream);

	fail_unless(result == CONVERSION_SUCCESS, "One byte lo conversion failed");
	fail_unless(size_byte_stream(stream) == 1, "One byte lo wrong length");
	fail_unless(stream.bytev[0] == 0, "One byte lo wrong value");

	base64_stream = "****";
	result = byte_stream_to_base64(stream, &base64_stream);

	fail_unless(result == CONVERSION_SUCCESS, "One byte lo restore failed");
	fail_unless(strcmp(base64_stream, "AA==") == 0, "One byte lo restore bad");

	free_byte_stream(&stream);
	free(base64_stream);
}
END_TEST

START_TEST(test_base64_two_bytes_high)
{
	struct byte_stream stream;
	char *base64_stream;
	conversion_result_t result;

	base64_stream = "//8=";
	result = base64_to_byte_stream(base64_stream, &stream);

	fail_unless(result == CONVERSION_SUCCESS, "Two byte hi conversion failed");
	fail_unless(size_byte_stream(stream) == 2, "Two byte hi wrong length");
	fail_unless(stream.bytev[0] == 255, "Two byte hi wrong value 1");
	fail_unless(stream.bytev[1] == 255, "Two byte hi wrong value 2");

	base64_stream = "****";
	result = byte_stream_to_base64(stream, &base64_stream);

	fail_unless(result == CONVERSION_SUCCESS, "Two byte hi restore failed");
	fail_unless(strcmp(base64_stream, "//8=") == 0, "Two hi byte restore bad");

	free_byte_stream(&stream);
	free(base64_stream);
}
END_TEST

START_TEST(test_base64_two_bytes_low)
{
	struct byte_stream stream;
	char *base64_stream;
	conversion_result_t result;

	base64_stream = "AAA=";
	result = base64_to_byte_stream(base64_stream, &stream);

	fail_unless(result == CONVERSION_SUCCESS, "Two byte lo conversion failed");
	fail_unless(size_byte_stream(stream) == 2, "Two byte lo wrong length");
	fail_unless(stream.bytev[0] == 0, "Two byte lo wrong value 1");
	fail_unless(stream.bytev[1] == 0, "Two byte lo wrong value 2");

	base64_stream = "****";
	result = byte_stream_to_base64(stream, &base64_stream);

	fail_unless(result == CONVERSION_SUCCESS, "Two byte lo restore failed");
	fail_unless(strcmp(base64_stream, "AAA=") == 0, "Two byte lo restore bad");

	free_byte_stream(&stream);
	free(base64_stream);
}
END_TEST

START_TEST(test_base64_many_bytes)
{
	struct byte_stream stream;
	char *input = "easure.";
	char *output;
	char *expected = "ZWFzdXJlLg==";
	conversion_result_t result;

	result = string_to_byte_stream(input, &stream);
	fail_unless(result == CONVERSION_SUCCESS, "Couldn't load string");

	result = byte_stream_to_base64(stream, &output);
	fail_unless(result == CONVERSION_SUCCESS, "Couldn't base64");
	fail_unless(strcmp(output, expected) == 0, "Wrong base64 output");
	free_byte_stream(&stream);
	free(output);

	result = base64_to_byte_stream(expected, &stream);
	fail_unless(result == CONVERSION_SUCCESS, "Couldn't de-base64");

	result = byte_stream_to_string(stream, &output);
	fail_unless(result == CONVERSION_SUCCESS, "Couldn't print to string");
	fail_unless(strcmp(output, input) == 0, "Wrong decoded output");
	free_byte_stream(&stream);
	free(output);
}
END_TEST

static unsigned char test_bad_chars[6] = {'!', '"', '#', '\0', '\177', '\377'};

START_TEST(test_base64_bad_chars)
{
	struct byte_stream stream;
	char base64_stream[] = "A*==";
	conversion_result_t result;

	base64_stream[1] = test_bad_chars[_i];
	result = base64_to_byte_stream(base64_stream, &stream);

	fail_unless(result == CONVERSION_FAILURE, "Case %i succeeded", _i);
	fail_unless(stream.bytec == 0, "Stream left with nonzero length");
	fail_unless(stream.bytev == NULL, "Stream left with non-null vector");
}
END_TEST

Suite *
conversions_base64_stream_suite(void)
{
	Suite *s = suite_create("Conversions: base64 stream <=> byte stream");
	TCase *tc_core = tcase_create("Core");

	tcase_add_loop_test(tc_core, test_byte_stream_to_base64, 0, 6);
	tcase_add_loop_test(tc_core, test_base64_to_byte_stream, 0, 6);
	tcase_add_test(tc_core, test_base64_one_byte_high);
	tcase_add_test(tc_core, test_base64_one_byte_low);
	tcase_add_test(tc_core, test_base64_two_bytes_high);
	tcase_add_test(tc_core, test_base64_two_bytes_low);
	tcase_add_test(tc_core, test_base64_many_bytes);
	tcase_add_loop_test(tc_core, test_base64_bad_chars, 0, 6);

	suite_add_tcase(s, tc_core);
	return s;
}

