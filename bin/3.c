#include "../include/string.h"
#include "../include/chardistn.h"

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 2000

static const char input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

char *
load_training_data(char *filename)
{
	int handle = open(filename, O_RDONLY);
	char *buffer = malloc(BUFFER_SIZE + 1);
	ssize_t bytes = read(handle, buffer, BUFFER_SIZE);
	buffer[bytes] = '\0';
	close(handle);
	return buffer;
}

int
main(int argc, char **argv)
{
	char *szTraining;
	String *stString;
	CharDistn *pDistn;
	StringConversionResult result;

	if (argc != 2) {
		printf("Expected one argument\n");
		exit(1);
	}

	szTraining = load_training_data(argv[1]);
	stString = string(szTraining, strlen(szTraining));
	pDistn = chardistn_from_string(stString);
	assert(pDistn != NULL);
	string_free(stString);

	stString = string(input, sizeof(input) - 1);
	assert(stString != NULL);

	result = string_from_hex(stString);
	assert(result == SCONV_OK);

	printf("Hex-decodes to:\n");
	string_debug(stString);

	chardistn_free(pDistn);
	string_free(stString);

	return 0;
}
