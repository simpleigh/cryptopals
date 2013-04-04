/*
   ________        _____     ____________
   ___  __ )____  ___  /_______  ___/_  /__________________ _______ ___
   __  __  |_  / / /  __/  _ \____ \_  __/_  ___/  _ \  __ `/_  __ `__ \
   _  /_/ /_  /_/ // /_ /  __/___/ // /_ _  /   /  __/ /_/ /_  / / / / /
   /_____/ _\__, / \__/ \___//____/ \__/ /_/    \___/\__,_/ /_/ /_/ /_/
           /____/
*/

#ifndef __BS_BS_H
#define __BS_BS_H

#include <stdlib.h>

/* An individual byte */
typedef unsigned char BSbyte;

/* The byte stream itself */
typedef struct BS BS;

/* Result ENUM
   Each method call returns this type in order to indicate success (or
   otherwise). New error conditions may be added at any point.
*/
typedef enum {
	BS_OK = 0,
	BS_INVALID, /* 1 */ /* Invalid input data */
	BS_MEMORY   /* 2 */ /* Memory allocation problem */
} BSresult;

/* Creates a byte stream
   An empty byte stream is created and a pointer returned.
*/
BS *bs_create(void);

/* Creates a byte stream of a particular size
   A byte stream of the specified length is created and a pointer returned.
   The length must be greater than zero. Byte stream data is left uninitialised.
*/
BS *bs_create_size(size_t length);

/* Zeroes a byte stream
   All bytes in the stream are set to zero.
*/
void bs_zero(BS *bs);

/* Frees a byte stream
   Frees the memory used by a byte stream. The pointer provided must not be
   reused after being freed.
*/
void bs_free(BS *bs);

/* Returns byte stream size */
size_t bs_size(const BS *bs);

/* Gets a byte from the stream */
BSbyte bs_byte_get(const BS *bs, size_t index);

/* Sets a byte in the stream */
BSbyte bs_byte_set(BS *bs, size_t index, BSbyte byte);

/* Loads a string into the stream */
BSresult bs_load_string(BS *bs, const char *string);

#endif /* __BS_BS_H */
