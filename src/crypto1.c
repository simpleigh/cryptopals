#include "bs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
static const char test_input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static const char expected_output[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
*/
#define BUFFER_SIZE 8

BSresult convert(const BS *bs)
{
	char *output;
	size_t length;
	BSresult result;
	BS *bsConvert = bs_create_size(4);

	result = bs_save(bs, (BSbyte **) &output, &length);
	if (result != BS_OK) goto error;

	result = bs_load_hex(bsConvert, output, length);
	free(output);
	if (result != BS_OK) goto error;

	result = bs_save_base64(bsConvert, &output, &length);
	if (result != BS_OK) goto error;

	printf("%s", output);
	free(output);
	bs_free(bsConvert);

	return BS_OK;

error:
	bs_free(bsConvert);
	return BS_INVALID;
}

int
main(/*int argc, char **argv*/)
{
	BS *bs = bs_create_size(8);
	BSbyte *buffer = malloc(BUFFER_SIZE * sizeof(BSbyte));
	size_t cbRead;
	BSresult result = BS_OK;

	while (result == BS_OK) {
		cbRead = fread(buffer, sizeof(BSbyte), BUFFER_SIZE, stdin);
		result = bs_stream(bs, buffer, cbRead, convert);
	}

	return 0;
}
