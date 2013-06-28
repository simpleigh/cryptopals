#include "../include/chardistn.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

CharDistn *
chardistn_from_string(const String *pString)
{
	CharDistn *pDistn;
	size_t ibCharacter;
	unsigned int *pCharacter;

	assert(pString != NULL);

	pDistn = malloc(sizeof(CharDistn));
	if (pDistn == NULL) {
		return pDistn;
	}

	for (ibCharacter = 0; ibCharacter < pString->cbCharacters; ibCharacter++) {
		pCharacter = pDistn->cChars +
			(size_t) pString->rgbCharacters[ibCharacter];

		(*pCharacter)++;
		assert(*pCharacter != 0); /* Overflow */
	}

	return pDistn;
}

void
chardistn_free(CharDistn *pDistn)
{
	if (pDistn == NULL) {
		return;
	}

	free(pDistn);
}

void
chardistn_print(const CharDistn *pDistn)
{
	size_t iDistn;
	unsigned char character;

	assert(pDistn != NULL);

	for (iDistn = 0; iDistn < 256; iDistn++) {
		character = (unsigned char) iDistn;
		printf(
			"| %3u '%c' : %-6u ",
			character,
			isprint(character) ? character : '?',
			pDistn->cChars[iDistn])
		;
		if (iDistn % 4 == 3) {
			printf("\n");
		}
	}
}

float
chardistn_probability(const CharDistn *pReference, const CharDistn *pTest)
{
	size_t iDistn;
	float result = 0;

	assert(pReference != NULL);
	assert(pTest != NULL);

	for (iDistn = 0; iDistn < 256; iDistn++) {
		result += pReference->cChars[iDistn] * pTest->cChars[iDistn];
	}

	return result;
}
