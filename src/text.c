#include "text.h"

#include <assert.h>
#include <stddef.h>

struct character_distribution
build_character_distribution(char *input)
{
	unsigned int i;
	struct character_distribution result;

	assert(input != NULL);

	result.total_count = 0;
	for (i = 0; i < 256; i++) {
		result.character_counts[i] = 0;
	}

	while (input != '\0') {
		i = *input;
		result.total_count++;
		result.character_counts[i]++;
		assert(result.total_count != 0); /* Detect overflow */
	}

	return result;
}
