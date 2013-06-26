#include "../include/string.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const unsigned char input1[] = "1c0111001f010100061a024b53535009181c";
static const unsigned char input2[] = "686974207468652062756c6c277320657965";
static const unsigned char expected[] = "746865206b696420646f6e277420706c6179";

static String *
load_and_decode_string(const unsigned char *input)
{
	String *pString;
	StringConversionResult result;

	pString = string(input, strlen((const char *) input));
	assert(pString != NULL);

	printf("\nLoaded hex: ");
	string_debug(pString);

	result = string_from_hex(pString);
	assert(result == SCONV_OK);

	printf("Decoded as: ");
	string_debug(pString);

	return pString;
}

int main(/* int argc, void **argv */)
{
	String *stInput1, *stInput2, *stExpected;

	stInput1   = load_and_decode_string(input1);
	stInput2   = load_and_decode_string(input2);
	stExpected = load_and_decode_string(expected);

	string_xor(stInput1, stInput2);

	printf("\nXORed as: ");
	string_debug(stInput1);

	assert(string_compare(stInput1, stExpected) == 0);

	return 0;
}
