#ifndef _TESTS_CONVERSIONS_H
#define _TESTS_CONVERSIONS_H

#include <check.h>

Suite *conversions_byte_stream_suite(void);
Suite *conversions_hex_byte_suite(void);
Suite *conversions_hex_stream_suite(void);
Suite *conversions_string_stream_suite(void);
Suite *conversions_base64_stream_suite(void);
Suite *conversions_xor_stream_suite(void);

#endif /* _TESTS_CONVERSIONS_H */
