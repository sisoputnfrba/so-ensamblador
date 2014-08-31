#ifndef ASSEMBLE_H_
#define ASSEMBLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ruleset.h"
#include "labels.h"

void assembleLine(char*, int, void(*)(short, unsigned int*, char*), t_labels*);
void decompile(char*, char*);

#endif
