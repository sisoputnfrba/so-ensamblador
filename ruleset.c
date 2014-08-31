#include "ruleset.h"

bool isValidReg(char);

#define VA_NARGS_IMPL(_1, _2, _3, _4, _5, N, ...) N
#define VA_NARGS(...) VA_NARGS_IMPL(X,##__VA_ARGS__, 4, 3, 2, 1, 0)
#define createRule(Name, ...) \
		{\
			.literal = #Name,\
			.opCount = VA_NARGS(__VA_ARGS__),\
			.opType = {\
				__VA_ARGS__\
			}\
		},

t_rule searchRule(char* line){
	static t_rule rules[] ={
			#include "sintax/bytecodes.txt"
	};

	int i;
	for(i=0; i<sizeof(rules)/sizeof(t_rule); i++)
		if( !strncmp(rules[i].literal, line, LITERAL_SIZE) )
			return rules[i];

	fprintf(stderr, "No existe la isntruccion `%.*s`", LITERAL_SIZE, line);
	abort();
	return (t_rule){{0}};
}

bool isValidReg(char x){
	return x=='A' || x=='B' || x=='C' || x=='D' || x=='E' || x=='S' || x=='X' || x=='M' || x=='P' || x=='F';
}
