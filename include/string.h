#ifndef __INCLUDE_STRING_H
#define __INCLUDE_STRING_H

#include <stdlib.h>

typedef struct {
	size_t cbCharacters;
	unsigned char *rgbCharacters;
} String;

String *string(const void *rgData, size_t cbBytes);
void string_free(String *pString);

int string_compare(const String *pString1, const String *pString2);

void string_print(const String *pString);
void string_debug(const String *pString);

typedef enum StringConversionResult {
	SCONV_OK = 0,
	SCONV_FAIL
} StringConversionResult;

StringConversionResult string_from_hex(String *pString);
StringConversionResult string_to_hex(String *pString);

StringConversionResult string_from_base64(String *pString);
StringConversionResult string_to_base64(String *pString);

void string_xor(String *pString1, const String *pString2);

#endif /* __INCLUDE_STRING_H */
