#ifndef LABELS_H_
#define LABELS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	char* label;
	unsigned int point;
	short obsSize;
	unsigned int* obs;
} t_label;

typedef struct{
	short size;
	t_label* x;
} t_labels;

void addLabel(char*, int, char*, t_labels*);
t_label* findLabel(char*, t_labels*);

t_labels* initLabels();
void destroyLabels(t_labels*);

unsigned int getOrSubscribePos(char*, unsigned int, t_labels*);
void postTranslate(char*, unsigned int, t_labels*, void (*fun)(short, unsigned int*, char*));

#endif
