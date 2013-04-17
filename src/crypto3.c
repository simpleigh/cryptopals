#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

int main(/* int argc, char **argv*/)
{
	BS *bs = bs_create(), *operand = bs_create_size(1);
	char *string;
	size_t length;
	unsigned int testByte;
	BSresult result;

	for (testByte = 0; testByte < 256; testByte++) {
		bs_load_hex(bs, input, strlen(input));
		bs_set_byte(operand, 0, (BSbyte) testByte);
		bs_combine_xor(bs, operand);
		result = bs_save_string(bs, &string, &length);
		if (result == BS_OK) {
			printf("%u: %s\n", testByte, string);
		}
		free(string);
	}

	bs_free(bs);
	bs_free(operand);

	return 0;
}
