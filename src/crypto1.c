#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char test_input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static const char expected_output[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

int
main(/*int argc, char **argv*/)
{
	BS *bs = bs_create();
	char *string;
	size_t length;

	printf("%s\n", test_input);
	bs_load_hex(bs, test_input, strlen(test_input));

	bs_save_string(bs, &string, &length);
	printf("(%s)\n", string);
	free(string);

	bs_save_base64(bs, &string, &length);
	printf("%s\n", string);
	if (strcmp(expected_output, string) != 0) {
		printf("Doesn't match expected\n");
	}
	bs_free(bs);

	bs = bs_create();
	bs_load_base64(bs, string, length);
	bs_save_hex(bs, &string, &length);
	printf("%s\n", string);
	if (strcmp(test_input, string) != 0) {
		printf("Doesn't match expected\n");
	}
	free(string);
	bs_free(bs);

	return 0;
}
