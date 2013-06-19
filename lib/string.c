#include "../include/string.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

String *
string(const void *rgData, size_t cbData)
{
	String *pString;

	assert(rgData != NULL);

	pString = malloc(sizeof(String));
	if (pString == NULL) {
		return pString;
	}

	pString->cbCharacters = cbData;

	if (cbData == 0) {
		pString->rgbCharacters = NULL;
	} else {
		pString->rgbCharacters = malloc(cbData);
		if (pString->rgbCharacters == NULL) {
			free(pString);
			pString = NULL;
		} else {
			memcpy(pString->rgbCharacters, rgData, cbData);
			pString->cbCharacters = cbData;
		}
	}

	return pString;
}

void
string_free(String *pString)
{
	if (pString == NULL) {
		return;
	}

	if (pString->rgbCharacters != NULL) {
		free(pString->rgbCharacters);
	}

	free(pString);
}

int
string_compare(const String *pString1, const String *pString2)
{
	int compareResult;
	size_t minSize;

	assert(pString1 != NULL);
	assert(pString2 != NULL);

	minSize = min(pString1->cbCharacters, pString2->cbCharacters);
	compareResult = memcmp(pString1->rgbCharacters, pString2->rgbCharacters, minSize);

	if (compareResult == 0) {
		if (pString1->cbCharacters > minSize) return 1;
		if (pString2->cbCharacters > minSize) return -1;
	}

	return 0;
}

void
string_print(const String *pString)
{
	size_t ibCharacters;
	unsigned char character;

	assert(pString != NULL);

	for (ibCharacters = 0; ibCharacters < pString->cbCharacters; ibCharacters++) {
		character = pString->rgbCharacters[ibCharacters];
		if (isprint(character)) {
			putchar(character);
		} else {
			putchar('?');
		}
	}
}

void
string_debug(const String *pString)
{
	assert(pString != NULL);

	printf("String(%u): '", pString->cbCharacters);
	string_print(pString);
	printf("'\n");
}
