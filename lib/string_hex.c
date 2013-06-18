#include "../include/string.h"

#include <assert.h>
#include <stdlib.h>

static unsigned char
read_hex_digit(unsigned char digit)
{
	if ((digit >= '0' && digit <= '9')) {
		return digit - '0';
	}

	if ((digit >= 'a' && digit <= 'f')) {
		return digit - 'a' + 0xA;
	}

	if ((digit >= 'A' && digit <= 'F')) {
		return digit - 'A' + 0xA;
	}

	return 16;
}

StringConversionResult
string_from_hex(String *pString)
{
	unsigned char *rgbCharactersNew;
	size_t ibCharacters;
	unsigned char hi, lo;

	assert(pString != NULL);

	if (pString->cbCharacters == 0) {
		return SCONV_OK;
	}

	if (pString->cbCharacters % 2) {
		return SCONV_FAIL;
	}

	rgbCharactersNew = malloc(pString->cbCharacters >> 1);
	if (rgbCharactersNew == NULL) {
		return SCONV_FAIL;
	}

	for (ibCharacters = 0; ibCharacters < pString->cbCharacters; ibCharacters += 2) {
		hi = read_hex_digit(pString->rgbCharacters[ibCharacters]);
		lo = read_hex_digit(pString->rgbCharacters[ibCharacters + 1]);

		if (hi > 15 || lo > 15) {
			free(rgbCharactersNew);
			return SCONV_FAIL;
		}

		rgbCharactersNew[ibCharacters >> 1] = (hi << 4) | lo;
	}

	free(pString->rgbCharacters);
	pString->rgbCharacters = rgbCharactersNew;
	pString->cbCharacters = pString->cbCharacters >> 1;
	return SCONV_OK;
}

StringConversionResult
string_to_hex(String *pString)
{
	return SCONV_FAIL;
}
