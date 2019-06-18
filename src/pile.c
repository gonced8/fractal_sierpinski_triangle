#include "pile.h"


Entry *newEntry(float pos[2]){
	Entry *entry = malloc(sizeof(Entry));

	if(entry == NULL){
		printf("Error in newEntry()\n");
		perror("malloc");
	}

	memcpy(entry, pos, 2*sizeof(float));

	return entry;
}


Entry *push(Entry *top, Entry *entry){
	entry->next = top;

	return entry;
}


Entry *pop(Entry *top){
	Entry *next = top->next;

	free((Entry *)top);

	return next;
}


Entry *clear(Entry *top){
	while(top!=NULL)
		top = pop(top);
	
	return NULL;
}
