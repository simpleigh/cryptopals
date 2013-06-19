#include "../include/string.h"

#include <assert.h>
#include <stdlib.h>

void
string_xor(String *pString, const String *pOperand)
{
	size_t ibString = 0, ibOperand = 0;

	assert(pString  != NULL);
	assert(pOperand != NULL);
	assert(pOperand->cbCharacters > 0);

	while (ibString < pString->cbCharacters) {
		pString->rgbCharacters[ibString] =
			pString->rgbCharacters[ibString] ^ pOperand->rgbCharacters[ibOperand];

		ibString++;
		ibOperand++;

		if (ibOperand == pOperand->cbCharacters) {
			ibOperand = 0;
		}
	}
}
