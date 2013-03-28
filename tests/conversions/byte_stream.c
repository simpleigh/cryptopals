#include "conversions.h"
#include "../../src/lib/conversions.h"
#include <check.h>
#include <stdlib.h>

START_TEST(test_allocates_size)
{
	struct byte_stream stream;
	conversion_result_t result;

	result = allocate_byte_stream(&stream, 5);

	fail_unless(result == CONVERSION_SUCCESS, "Failed to allocate");
	fail_unless(stream.bytec == 5, "Stream length was %u, not 5", stream.bytec);

	free_byte_stream(&stream);
}
END_TEST

START_TEST(test_freeing_stream)
{
	struct byte_stream stream;

	allocate_byte_stream(&stream, 5);
	fail_unless(stream.bytec == 5, "Stream length was %u, not 5", stream.bytec);

	free_byte_stream(&stream);
	fail_unless(stream.bytec == 0, "Stream length not reset");
	fail_unless(stream.bytev == NULL, "Stream pointer not NULL");
}
END_TEST

START_TEST(test_zero_stream)
{
	struct byte_stream stream;
	size_t i;

	allocate_byte_stream(&stream, 5);
	zero_byte_stream(&stream);

	fail_unless(stream.bytec == 5, "Stream length was %u, not 5", stream.bytec);

	for (i = 0; i < 5; i++) {
		fail_unless(stream.bytev[i] == 0, "Byte %u not zeroed", i);
	}

	free_byte_stream(&stream);
}
END_TEST

START_TEST(test_size_stream)
{
	struct byte_stream stream;
	size_t stream_size;

	allocate_byte_stream(&stream, 5);
	stream_size = size_byte_stream(stream);

	fail_unless(stream_size == 5, "Stream size was %u, not 5", stream_size);

	free_byte_stream(&stream);
}
END_TEST

Suite *
conversions_byte_stream_suite(void)
{
	Suite *s = suite_create("Conversions: byte stream manipulation");
	TCase *tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_allocates_size);
	tcase_add_test(tc_core, test_freeing_stream);
	tcase_add_test(tc_core, test_zero_stream);
	tcase_add_test(tc_core, test_size_stream);
	suite_add_tcase(s, tc_core);
	return s;
}
