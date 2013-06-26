#ifndef __INCLUDE_CHARDISTN_H
#define __INCLUDE_CHARDISTN_H

#include "string.h"

typedef struct {
	unsigned int cChars[256];
} CharDistn;

CharDistn *chardistn_from_string(const String *pString);
void chardistn_free(CharDistn *pDistn);

void chardistn_print(const CharDistn *pDistn);

float chardistn_probability(const CharDistn *pReference, const CharDistn *pTest);

#endif /* __INCLUDE_CHARDISTN_H */
