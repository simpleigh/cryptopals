#include "../include/string.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const unsigned char inputHex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
static const unsigned char inputB64[] = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

int main(/* int argc, void **argv */)
{
	String *stInput, *stBase64, *stString;
	StringConversionResult result;

	stInput = string(inputHex, strlen(inputHex));
	assert(stInput != NULL);
	assert(stInput->rgbCharacters != NULL);

	printf("\nHex input:\n");
	string_debug(stInput);

	stBase64 = string(inputB64, strlen(inputB64));
	assert(stBase64 != NULL);
	assert(stBase64->rgbCharacters != NULL);

	printf("\nBase64 input:\n");
	string_debug(stBase64);

	stString = string(stInput->rgbCharacters, stInput->cbCharacters);
	assert(stString != NULL);
	assert(stString->rgbCharacters != NULL);
	assert(string_compare(stInput, stString) == 0);

	result = string_from_hex(stString);
	assert(result == SCONV_OK);

	printf("\nHex-decodes to:\n");
	string_debug(stString);

	result = string_to_base64(stString);
	assert(result == SCONV_OK);
	assert(string_compare(stBase64, stString) == 0);

	printf("\nBase64-encodes to:\n");
	string_debug(stString);

	result = string_from_base64(stString);
	assert(result == SCONV_OK);

	result = string_to_hex(stString);
	assert(result == SCONV_OK);
	assert(string_compare(stInput, stString) == 0);

	string_free(stInput);
	string_free(stBase64);
	string_free(stString);

	return 0;
}
