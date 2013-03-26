#include "conversions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char test_input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static const char expected_output[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

int
main(/*int argc, char **argv*/)
{
	struct byte_stream stream;
	char *string;
	char *base64_stream;
	char *hex_stream;

	printf("%s\n", test_input);

	hex_stream_to_byte_stream(test_input, &stream);

	byte_stream_to_string(stream, &string);
	printf("(%s)\n", string);

	byte_stream_to_base64(stream, &base64_stream);
	printf("%s\n", base64_stream);

	if (strcmp(expected_output, base64_stream) != 0) {
		printf("Doesn't match expected\n");
	}

	free_byte_stream(&stream);

	base64_to_byte_stream(base64_stream, &stream);

	byte_stream_to_hex_stream(stream, &hex_stream);
	printf("%s\n", hex_stream);

	if (strcmp(test_input, hex_stream) != 0) {
		printf("Doesn't match expected\n");
	}

	free_byte_stream(&stream);
	free(hex_stream);
	free(base64_stream);

	return 0;
}
