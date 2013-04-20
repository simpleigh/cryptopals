#ifndef _CHAR_DISTN_H
#define _CHAR_DISTN_H

#include <sys/types.h>

struct char_distn {
	unsigned int cTotal;
	unsigned int cChars[256];
};

struct char_distn char_distn_from_string(char *string, size_t length);

float char_distn_probability(struct char_distn dist1, struct char_distn dist2);

#endif /* _CHAR_DISTN_H */
