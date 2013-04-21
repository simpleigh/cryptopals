#include "bs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
encrypt(const char *string, const char *key, char **result, size_t *length)
{
	BS *bsString = bs_create(), *bsKey = bs_create();

	bs_load(bsString, (BSbyte *) string, strlen(string));
	bs_load(bsKey,    (BSbyte *) key,    strlen(key));

	bs_combine_xor(bsString, bsKey);

	bs_save_hex(bsString, result, length);

	bs_free(bsString);
	bs_free(bsKey);
}



int
main(int argc, char **argv)
{
	char *string, *key;
	char *result;
	size_t length;

	if (argc != 3) {
		printf("Expected two arguments: PLAINTEXT KEY\n");
		return 1;
	}

	string = argv[1];
	key    = argv[2];

	encrypt(string, key, &result, &length);
	printf("%s", result);
	free(result);

	return 0;
}
