#include "conversions.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static const char hex_encoding_table[] = "0123456789abcdef";

static const char base64_encoding_table[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned int base64_decoding_table[] = {
		                                            62, 99, 99, 99, 99,
		52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 99, 99, 99, 99, 99, 99,
		99,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
		15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 99, 99, 99, 99, 99,
		99, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51
};

/**
 * Allocates memory for a byte stream.
 */
conversion_result_t
allocate_byte_stream(struct byte_stream *stream, size_t bytes)
{
	assert(bytes > 0);

	stream->bytev = malloc(bytes * sizeof(stream->bytev));

	if (stream->bytev == NULL) {
		stream->bytec = 0;
		return CONVERSION_FAILURE;
	} else {
		stream->bytec = bytes;
		return CONVERSION_SUCCESS;
	}
}


/**
 * Zeroes all entries in a byte stream.
 */
void
zero_byte_stream(struct byte_stream *stream)
{
	size_t i;

	assert(stream->bytev != NULL);

	for (i = 0; i < stream->bytec; i++) {
		stream->bytev[i] = 0;
	}
}


/**
 * Frees memory for a byte stream.
 */
void
free_byte_stream(struct byte_stream *stream)
{
	assert(stream->bytev != NULL);

	stream->bytec = 0;
	free(stream->bytev);
	stream->bytev = NULL;
}


/**
 * Returns the length of a byte stream.
 */
size_t
size_byte_stream(const struct byte_stream stream)
{
	return stream.bytec;
}


/**
 * Converts an integer to a hexadecimal byte.
 */
conversion_result_t
byte_to_hex_byte(const unsigned char byte, char *hi_digit, char *lo_digit)
{
	unsigned char hi, lo;

	hi = byte >> 4;
	lo = byte & 0xF;

	assert(hi <= 15);
	assert(lo <= 15);

	*hi_digit = hex_encoding_table[hi];
	*lo_digit = hex_encoding_table[lo];

	return CONVERSION_SUCCESS;
}


/**
 * Converts a single hexadecimal character to an integer.
 */
static conversion_result_t
hex_digit_to_byte(const char hex_digit, unsigned char *byte)
{
	if ((hex_digit >= '0' && hex_digit <= '9')) {
		*byte = hex_digit - '0';
		return CONVERSION_SUCCESS;
	}

	if ((hex_digit >= 'a' && hex_digit <= 'f')) {
		*byte = hex_digit - 'a' + 0xA;
		return CONVERSION_SUCCESS;
	}

	if ((hex_digit >= 'A' && hex_digit <= 'F')) {
		*byte = hex_digit - 'A' + 0xA;
		return CONVERSION_SUCCESS;
	}

	return CONVERSION_FAILURE;
}


/**
 * Converts a hexadecimal byte to an integer.
 */
conversion_result_t
hex_byte_to_byte(const char hi_digit, const char lo_digit, unsigned char *byte)
{
	unsigned char hi, lo;

	if (
		(hex_digit_to_byte(hi_digit, &hi) == CONVERSION_SUCCESS) &&
		(hex_digit_to_byte(lo_digit, &lo) == CONVERSION_SUCCESS)
	) {
		*byte = (hi << 4) | lo;
		return CONVERSION_SUCCESS;
	}

	return CONVERSION_FAILURE;
}


/**
 * Converts an integer stream to a hexadecimal string.
 */
conversion_result_t
byte_stream_to_hex_stream(const struct byte_stream stream, char **hex_stream)
{
	size_t hex_stream_length, i;
	conversion_result_t result;

	assert(stream.bytev != NULL);

	hex_stream_length = (size_byte_stream(stream) << 1);

	*hex_stream = malloc((hex_stream_length + 1) * sizeof(**hex_stream));
	if (*hex_stream == NULL)
		return CONVERSION_FAILURE;

	(*hex_stream)[hex_stream_length] = '\0';

	for (i = 0; i < hex_stream_length; i += 2) {
		result = byte_to_hex_byte(
			stream.bytev[i >> 1],
			*hex_stream + i,
			*hex_stream + i + 1
		);

		if (result == CONVERSION_FAILURE) {
			free(*hex_stream);
			*hex_stream = NULL;
			return CONVERSION_FAILURE;
		}
	}

	return CONVERSION_SUCCESS;
}


/**
 * Converts a hexadecimal string to an integer stream.
 */
conversion_result_t
hex_stream_to_byte_stream(const char *hex_stream, struct byte_stream *stream)
{
	size_t hex_stream_length, i;
	conversion_result_t result;

	hex_stream_length = strlen(hex_stream);
	if (hex_stream_length & 1)
		return CONVERSION_FAILURE; /* odd number of characters */

	result = allocate_byte_stream(stream, hex_stream_length >> 1);
	if (result == CONVERSION_FAILURE)
		return CONVERSION_FAILURE;

	for (i = 0; i < hex_stream_length; i += 2) {
		result = hex_byte_to_byte(
			hex_stream[i],
			hex_stream[i + 1],
			stream->bytev + (i >> 1)
		);
		if (result == CONVERSION_FAILURE) {
			free_byte_stream(stream);
			return CONVERSION_FAILURE;
		}
	}

	return CONVERSION_SUCCESS;
}


/**
 * Writes a byte stream to a text string.
 */
conversion_result_t
byte_stream_to_string(const struct byte_stream stream, char **string)
{
	size_t byte_stream_length, i;
	char c;

	byte_stream_length = size_byte_stream(stream);

	*string = malloc((byte_stream_length + 1) * sizeof(**string));
	if (string == NULL)
		return CONVERSION_FAILURE;

	(*string)[byte_stream_length] = '\0';

	for (i = 0; i < byte_stream_length; i++) {
		c = stream.bytev[i];
		if ((c < 32) || (c > 126)) {
			free(*string);
			*string = NULL;
			return CONVERSION_FAILURE;
		}

		(*string)[i] = c;
	}

	return CONVERSION_SUCCESS;
}


/**
 * Loads a text string into a byte stream.
 */
conversion_result_t
string_to_byte_stream(const char *string, struct byte_stream *stream)
{
	size_t string_length, i;
	conversion_result_t result;

	string_length = strlen(string);

	result = allocate_byte_stream(stream, string_length);
	if (result == CONVERSION_FAILURE)
		return CONVERSION_FAILURE;

	for (i = 0; i < string_length; i++) {
		stream->bytev[i] = string[i];
	}

	return CONVERSION_SUCCESS;
}


/**
 * Converts a block of three bytes into a base64-encoded string.
 */
static conversion_result_t
bytes_to_base64(const unsigned char *in, const size_t length, char *out)
{
	assert(length > 0);

	switch (length) {
	case 0:
		return CONVERSION_FAILURE;

	case 1:
		out[0] = base64_encoding_table[in[0] >> 2];
		out[1] = base64_encoding_table[(in[0] & 0x3) << 4];
		out[2] = '=';
		out[3] = '=';
		break;

	case 2:
		out[0] = base64_encoding_table[in[0] >> 2];
		out[1] = base64_encoding_table[(in[0] & 0x3) << 4 | in[1] >> 4];
		out[2] = base64_encoding_table[(in[1] & 0xF) << 2];
		out[3] = '=';
		break;

	default:
		out[0] = base64_encoding_table[in[0] >> 2];
		out[1] = base64_encoding_table[(in[0] & 0x3) << 4 | in[1] >> 4];
		out[2] = base64_encoding_table[(in[1] & 0xF) << 2 | in[2] >> 6];
		out[3] = base64_encoding_table[in[2] & 0x3F];
		break;
	}

	return CONVERSION_SUCCESS;
}


/**
 * Converts a byte stream to a base64-encoded string.
 */
conversion_result_t
byte_stream_to_base64(const struct byte_stream stream, char **base64_stream)
{
	size_t byte_stream_length, base64_stream_length;
	size_t byte_stream_i = 0, base64_stream_i = 0;
	conversion_result_t result;

	assert(stream.bytev != NULL);

	byte_stream_length = size_byte_stream(stream);
	base64_stream_length = (byte_stream_length + 2) / 3 * 4;

	*base64_stream = malloc((base64_stream_length + 1) * sizeof(**base64_stream));
	if (*base64_stream == NULL)
		return CONVERSION_FAILURE;

	(*base64_stream)[base64_stream_length] = '\0';

	while (byte_stream_i < byte_stream_length) {
		result = bytes_to_base64(
			stream.bytev + byte_stream_i,
			byte_stream_length - byte_stream_i,
			*base64_stream + base64_stream_i
		);

		if (result == CONVERSION_FAILURE) {
			free(*base64_stream);
			*base64_stream = NULL;
			return CONVERSION_FAILURE;
		}

		byte_stream_i += 3;
		base64_stream_i += 4;
	}

	return CONVERSION_SUCCESS;
}


/**
 * Converts a single base64 code unit.
 * Returns 99 in the event of failure.
 */
static unsigned int
base64_decode(const char in)
{
	if ((in < 43) || (in > 122))
		return 99;

	return base64_decoding_table[in - 43];
}


/**
 * Converts a block of three bytes into a base64-encoded string.
 */
static conversion_result_t
base64_to_bytes(const char *in, unsigned char *out)
{
	unsigned int in0, in1, in2, in3;

	in0 = base64_decode(in[0]);
	in1 = base64_decode(in[1]);
	in2 = base64_decode(in[2]);
	in3 = base64_decode(in[3]);

	if ((in0 == 99) || (in1 == 99) || (in2 == 99) || (in3 == 99))
		return CONVERSION_FAILURE;

	out[0] = in0 << 2 | in1 >> 4;
	if (in[2] != '=') {
		out[1] = (in1 & 0xF) << 4 | in2 >> 2;
		if (in[3] != '=')
			out[2] = (in2 & 0x3) << 6 | in3;
	}

	return CONVERSION_SUCCESS;
}


/**
 * Converts a base64-encoded string to a byte stream.
 */
conversion_result_t
base64_to_byte_stream(const char *base64_stream, struct byte_stream *stream)
{
	size_t byte_stream_length, base64_stream_length;
	size_t byte_stream_i = 0, base64_stream_i = 0;
	conversion_result_t result;

	base64_stream_length = strlen(base64_stream);
	if (base64_stream_length & 3)
		return CONVERSION_FAILURE; /* not multiple of 4 */

	byte_stream_length = base64_stream_length / 4 * 3;

	result = allocate_byte_stream(stream, byte_stream_length);
	if (result == CONVERSION_FAILURE)
		return CONVERSION_FAILURE;

	while (base64_stream_i < base64_stream_length) {
		result = base64_to_bytes(
			base64_stream + base64_stream_i,
			stream->bytev + byte_stream_i
		);

		if (result == CONVERSION_FAILURE) {
			free_byte_stream(stream);
			return CONVERSION_FAILURE;
		}

		byte_stream_i += 3;
		base64_stream_i += 4;
	}

	return CONVERSION_SUCCESS;
}


/**
 * XORs two byte streams together.
 * Applies STREAM to TARGET, repeating the former if necessary.
 */
conversion_result_t
xor_byte_streams(const struct byte_stream stream, struct byte_stream *target)
{
	size_t stream_length, target_length;
	size_t stream_i = 0, target_i = 0;

	assert(stream.bytev != NULL);
	assert(target->bytev != NULL);

	stream_length = size_byte_stream(stream);
	target_length = size_byte_stream(*target);

	assert(stream_length > 0);

	while (target_i < target_length) {
		target->bytev[target_i] =
			target->bytev[target_i] ^ stream.bytev[stream_i];

		stream_i++;
		target_i++;
		if (stream_i == stream_length)
			stream_i = 0;
	}

	return CONVERSION_SUCCESS;
}
