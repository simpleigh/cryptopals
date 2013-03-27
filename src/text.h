#ifndef _TEXT_H
#define _TEXT_H

struct character_distribution {
	unsigned int total_count;
	unsigned int character_counts[256];
};

struct character_distribution build_character_distribution(char *input);

#endif /* _TEXT_H */
