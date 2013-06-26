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
	String *pString;
	CharDistn *pDistn;

	if (argc != 2) {
		printf("Expected one argument\n");
		exit(1);
	}

	szTraining = load_training_data(argv[1]);
	pString = string(szTraining, strlen(szTraining));
	pDistn = chardistn_from_string(pString);
	assert(pDistn != NULL);
	chardistn_print(pDistn);

	chardistn_free(pDistn);
	string_free(pString);

	return 0;
}
