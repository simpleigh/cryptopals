#ifndef _CONVERSIONS_H
#define _CONVERSIONS_H

#include <stddef.h>

#define CONVERSION_SUCCESS 1
#define CONVERSION_FAILURE 0

typedef unsigned int conversion_result_t;

struct byte_stream {
	size_t bytec;
	unsigned char *bytev;
};

conversion_result_t allocate_byte_stream(struct byte_stream *stream, size_t bytes);
void                zero_byte_stream(struct byte_stream *stream);
void                free_byte_stream(struct byte_stream *stream);
size_t              size_byte_stream(const struct byte_stream stream);

conversion_result_t byte_to_hex_byte(const unsigned char byte, char *hi_digit, char *lo_digit);
conversion_result_t hex_byte_to_byte(const char hi_digit, const char lo_digit, unsigned char *byte);

conversion_result_t byte_stream_to_hex_stream(const struct byte_stream stream, char **hex_stream);
conversion_result_t hex_stream_to_byte_stream(const char *hex_stream, struct byte_stream *stream);

conversion_result_t byte_stream_to_string(const struct byte_stream stream, char **string);
conversion_result_t string_to_byte_stream(const char *string, struct byte_stream *stream);

conversion_result_t byte_stream_to_base64(const struct byte_stream stream, char **base64_stream);
conversion_result_t base64_to_byte_stream(const char *base64_stream, struct byte_stream *stream);

conversion_result_t xor_byte_streams(const struct byte_stream stream, struct byte_stream *target);

#endif /* _CONVERSIONS_H */
