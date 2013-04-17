#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char input1[] = "1c0111001f010100061a024b53535009181c";
static const char input2[] = "686974207468652062756c6c277320657965";
static const char expected_output[] = "746865206b696420646f6e277420706c6179";

int
main(/*int argc, char **argv*/)
{
	BS *bs1 = bs_create(), *bs2 = bs_create();
	char *string;
	size_t length;

	bs_load_hex(bs1, input1, strlen(input1));
	bs_load_hex(bs2, input2, strlen(input2));
	bs_combine_xor(bs1, bs2);
	bs_save_hex(bs1, &string, &length);
	bs_free(bs1);
	bs_free(bs2);

	printf("%s\n", string);
	if (strcmp(expected_output, string) != 0) {
		printf("Doesn't match expected\n");
	}
	free(string);

	return 0;
}
