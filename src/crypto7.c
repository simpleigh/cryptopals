#include "bs.h"

#include <fcntl.h>
#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 4000

static const unsigned char
key_string[] = "YELLOW SUBMARINE";

unsigned char *
load_input(char *filename, size_t *length)
{
	int handle = open(filename, O_RDONLY);
	unsigned char *buffer = malloc(BUFFER_SIZE * sizeof(char));
	*length = read(handle, buffer, BUFFER_SIZE);
	buffer[*length] = '\0';
	close(handle);
	return buffer;
}

int
main(int argc, char **argv)
{
	unsigned char *input;
	size_t length;
	BS *bs = bs_create();
	AES_KEY *key = NULL;
	size_t ibInput;
	unsigned char output[16];

	if (argc != 2) {
		printf("Expected one argument\n");
		return 1;
	}

	input = load_input(argv[1], &length);

	bs_load_base64(bs, (char *) input, length);
	bs_save(bs, &input, &length);
	bs_free(bs);

	key = malloc(sizeof(AES_KEY));
	AES_set_decrypt_key(key_string, 128, key);

	for (ibInput = 0; ibInput < length; ibInput+= 16) {
		AES_decrypt(input + ibInput, output, key);
		printf("%s", output);
	}
	printf("\n");

	free(key);
	free(input);

	return 0;
}
