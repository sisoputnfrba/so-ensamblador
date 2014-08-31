#ifndef RULESET_H_
#define RULESET_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/types.h>

#define LITERAL_SIZE 4
#define MAX_OP_SIZE 5

typedef enum{
	Direccion, Registro, Numero
} e_type;

typedef struct{
	char literal[LITERAL_SIZE];
	short opCount;
	e_type opType[MAX_OP_SIZE];
} t_rule;

bool isValidReg(char);
t_rule searchRule(char* line);

#endif
