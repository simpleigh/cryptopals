/*
   ________        _____     ____________
   ___  __ )____  ___  /_______  ___/_  /__________________ _______ ___
   __  __  |_  / / /  __/  _ \____ \_  __/_  ___/  _ \  __ `/_  __ `__ \
   _  /_/ /_  /_/ // /_ /  __/___/ // /_ _  /   /  __/ /_/ /_  / / / / /
   /_____/ _\__, / \__/ \___//____/ \__/ /_/    \___/\__,_/ /_/ /_/ /_/
           /____/
*/

#include "bs/bs.h"

#include <assert.h>
#include <stdlib.h>

struct BS {
	size_t cbBytes;
	BSbyte *pbBytes;
	size_t cbBuffer;
};

BS *
bs_create(void)
{
	BS *bs;

	bs = malloc(sizeof(struct BS));
	if (bs == NULL) {
		return NULL;
	}

	bs->cbBytes = 0;
	bs->pbBytes = NULL;
	bs->cbBuffer = 0;

	return bs;
}

/**
 * Handles memory allocations for byte streams.
 */
static BSresult
bs_malloc(BS *bs, size_t length)
{
	BSbyte *pbNewBytes;

	assert((bs->pbBytes != NULL) || (bs->cbBuffer == 0));
	assert(bs->cbBytes <= bs->cbBuffer);

	if (length <= bs->cbBuffer) { /* Buffer already long enough */
		bs->cbBytes = length;
		return BS_OK;
	}

	pbNewBytes = realloc(bs->pbBytes, length * sizeof(*(bs->pbBytes)));
	if (pbNewBytes == NULL) {
		return BS_MEMORY;
	}

	bs->cbBytes = length;
	bs->pbBytes = pbNewBytes;
	bs->cbBuffer = length;
	return BS_OK;
}

BS *
bs_create_size(size_t length)
{
	BS *bs;
	BSresult result;

	bs = bs_create();
	if (bs == NULL) {
		return bs;
	}

	if (length > 0) {
		result = bs_malloc(bs, length);
		if (result != BS_OK) {
			bs_free(bs);
			return NULL;
		}
	}

	return bs;
}

void
bs_zero(BS *bs)
{
	size_t ibIndex;

	if (bs_size(bs) == 0) {
		return;
	}

	assert(bs->pbBytes != NULL);

	for (ibIndex = 0; ibIndex < bs_size(bs); ibIndex++) {
		bs->pbBytes[ibIndex] = 0;
	}
}

void
bs_free(BS *bs)
{
	if ((bs->cbBuffer > 0) && (bs->pbBytes != NULL)) {
		free(bs->pbBytes);
	}
	free(bs);
}

size_t
bs_size(const BS *bs)
{
	return bs->cbBytes;
}

BSbyte
bs_byte_get(const BS *bs, size_t index)
{
	assert(index < bs_size(bs));
	assert(bs->pbBytes != NULL);

	return bs->pbBytes[index];
}

BSbyte
bs_byte_set(BS *bs, size_t index, BSbyte byte)
{
	assert(index < bs_size(bs));
	assert(bs->pbBytes != NULL);

	return bs->pbBytes[index] = byte;
}

BSresult
bs_load_binary(BS *bs, const unsigned char *data, size_t length)
{
	size_t ibIndex;
	BSresult result;

	result = bs_malloc(bs, length);
	if (result != BS_OK) {
		return result;
	}

	for (ibIndex = 0; ibIndex < length; ibIndex++) {
		bs->pbBytes[ibIndex] = data[ibIndex];
	}

	return BS_OK;
}

BSresult
bs_load_string(BS *bs, const char *string, size_t length)
{
	size_t ibIndex;
	BSresult result;

	result = bs_malloc(bs, length);
	if (result != BS_OK) {
		return result;
	}

	for (ibIndex = 0; ibIndex < length; ibIndex++) {
		if (string[ibIndex] < 0) { /* Negative values not allowed */
			bs_malloc(bs, 0);
			return BS_INVALID;
		}
		bs->pbBytes[ibIndex] = (BSbyte)string[ibIndex];
	}

	return BS_OK;
}
