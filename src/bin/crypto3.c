#include "../lib/conversions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

int main(/* int argc, char **argv*/)
{
	struct byte_stream input_stream, char_stream;
	char *output;
	unsigned int test_char;
	conversion_result_t result;

	allocate_byte_stream(&char_stream, 1);

	for (test_char = 0; test_char < 256; test_char++) {
		hex_stream_to_byte_stream(input, &input_stream);
		char_stream.bytev[0] = (unsigned char)test_char;
		xor_byte_streams(char_stream, &input_stream);
		result = byte_stream_to_string(input_stream, &output);
		if (result == CONVERSION_SUCCESS)
			printf("%u: %s\n", test_char, output);
	}

	free_byte_stream(&input_stream);
	free_byte_stream(&char_stream);
	free(output);

	return 0;
}
