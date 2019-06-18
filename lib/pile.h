#ifndef PILE_H
#define PILE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry{
	float pos[2];
	struct entry *next;
}Entry;

Entry *newEntry(float pos[2]);
Entry *push(Entry *top, Entry *entry);
Entry *pop(Entry *top);
Entry *clear(Entry *top);


#endif /* PILE_H */
