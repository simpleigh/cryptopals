#include "conversions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char input1[] = "1c0111001f010100061a024b53535009181c";
static const char input2[] = "686974207468652062756c6c277320657965";
static const char expected_output[] = "746865206b696420646f6e277420706c6179";

int
main(/*int argc, char **argv*/)
{
	struct byte_stream stream1, stream2;
	char *output;

	hex_stream_to_byte_stream(input1, &stream1);
	hex_stream_to_byte_stream(input2, &stream2);
	xor_byte_streams(stream1, &stream2);
	byte_stream_to_hex_stream(stream2, &output);

	free_byte_stream(&stream1);
	free_byte_stream(&stream2);

	printf("%s\n", output);

	if (strcmp(expected_output, output) != 0) {
		printf("Doesn't match expected\n");
	}

	free(output);

	return 0;
}
