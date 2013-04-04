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
#include <string.h>

struct BS {
	size_t bytec;
	BSbyte *bytev;
};

BS *
bs_create(void)
{
	BS *bs;

	bs = malloc(sizeof(struct BS));
	if (bs == NULL) return NULL;

	bs->bytec = 0;
	bs->bytev = NULL;

	return bs;
}

static BSresult
bs_malloc(BS *bs, size_t length)
{
	assert(length > 0);

	bs->bytec = length;
	bs->bytev = malloc(length * sizeof(*(bs->bytev)));
	if (bs->bytev == NULL) {
		bs->bytec = 0;
		return BS_MEMORY;
	}

	return BS_OK;
}

static BSresult
bs_realloc(BS *bs, size_t length)
{
	if ((bs_size(bs) > 0) && (bs->bytev != NULL)) {
		free(bs->bytev);
	}

	if (length > 0) {
		return bs_malloc(bs, length);
	} else {
		bs->bytec = 0;
		bs->bytev = NULL;
		return BS_OK;
	}
}

BS *
bs_create_size(size_t length)
{
	BS *bs;
	BSresult result;

	bs = malloc(sizeof(struct BS));
	if (bs == NULL) return NULL;

	result = bs_malloc(bs, length);
	if (result != BS_OK) {
		bs_free(bs);
		return NULL;
	}

	return bs;
}

void
bs_zero(BS *bs)
{
	size_t i;

	if (bs_size(bs) > 0)
		assert(bs->bytev != NULL);

	for (i = 0; i < bs->bytec; i++) {
		bs->bytev[i] = 0;
	}
}

void
bs_free(BS *bs)
{
	if ((bs_size(bs) > 0) && (bs->bytev != NULL)) {
		free(bs->bytev);
	}
	free(bs);
}

size_t
bs_size(const BS *bs)
{
	return bs->bytec;
}

BSbyte
bs_byte_get(const BS *bs, size_t index)
{
	assert(index < bs->bytec);
	assert(bs->bytev != NULL);

	return bs->bytev[index];
}

BSbyte
bs_byte_set(BS *bs, size_t index, BSbyte byte)
{
	assert(index < bs->bytec);
	assert(bs->bytev != NULL);

	return bs->bytev[index] = byte;
}

BSresult
bs_load_string(BS *bs, const char *string)
{
	size_t string_length;
	BSresult result;

	string_length = strlen(string);
	result = bs_realloc(bs, string_length);
	if (result != BS_OK) return result;

	strncpy(bs->bytev, string, string_length);
	return BS_OK;
}
