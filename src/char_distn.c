#include "char_distn.h"

#include <assert.h>
#include <stddef.h>

struct char_distn
char_distn_from_string(char *string, size_t length)
{
	size_t i;
	struct char_distn result;

	assert(string != NULL);
	assert(length > 0);

	result.cTotal = 0;
	for (i = 0; i < 256; i++) {
		result.cChars[i] = 0;
	}

	for (i = 0; i < length; i++) {
		result.cTotal++;
		result.cChars[(size_t) string[i]]++;
		assert(result.cTotal != 0); /* Overflow */
	}

	return result;
}

float
char_distn_probability(struct char_distn dist1, struct char_distn dist2)
{
	size_t i;
	float result = 0;

	for (i = 0; i < 256; i++) {
		result += (dist1.cChars[i] * dist2.cChars[i]);
	}

	return result;
}
