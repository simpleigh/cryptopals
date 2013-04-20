#include "bs.h"
#include "char_distn.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFFER_SIZE 2000

static const char input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

char *
load_training_data(char *filename)
{
	int handle = open(filename, O_RDONLY);
	char *buffer = malloc(BUFFER_SIZE * sizeof(char));
	ssize_t bytes = read(handle, buffer, BUFFER_SIZE);
	buffer[bytes] = '\0';
	close(handle);
	return buffer;
}

void
compute_string(BSbyte bXor, BSbyte **string, size_t *length)
{
	BS *bs      = bs_create(),
	   *operand = bs_create_size(1);

	bs_load_hex(bs, input, strlen(input));
	bs_set_byte(operand, 0, bXor);
	bs_combine_xor(bs, operand);
	bs_save(bs, string, length);

	bs_free(bs);
	bs_free(operand);
}

int main(int argc, char **argv)
{
	char *training_string;
	struct char_distn trained_distn;

	unsigned int testByte;
	char *proposed_string;
	size_t length;
	struct char_distn proposed_distn;

	unsigned int resultByte = 65535;
	float probability = 0, resultProbability = 0;

	if (argc != 2) {
		printf("Expected one argument\n");
		exit(1);
	}

	training_string = load_training_data(argv[1]);
	trained_distn = char_distn_from_string(
		training_string,
		strlen(training_string)
	);
	free(training_string);

	for (testByte = 0; testByte < 256; testByte++) {
		compute_string(
			(BSbyte) testByte,
			(BSbyte **) &proposed_string,
			&length
		);

		proposed_distn = char_distn_from_string(proposed_string, length);
		free(proposed_string);

		probability = char_distn_probability(trained_distn, proposed_distn);
		if (probability > resultProbability) {
			resultProbability = probability;
			resultByte = testByte;
		}
	}

	compute_string(
		(BSbyte) resultByte,
		(BSbyte **) &proposed_string,
		&length
	);

	printf("%s\n", proposed_string);
	free(proposed_string);

	return 0;
}
