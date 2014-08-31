#include "assemble.h"

void decompile(char* start, char* end){
	int i, isData=false;
	while (start != end) {
		if( isData && end-start>0){
			printf("%.*s\n", end-start, start); //imprimi lo que puedas!
			return;
		}

		t_rule r = searchRule(start);
		if( !strncmp(r.literal, "XXXX", LITERAL_SIZE) )
				isData=true;

		printf("%.4s ", start);
		start += LITERAL_SIZE;
		for (i = 0; i < r.opCount; i++) {
			switch (r.opType[i]) {
			case Registro:
				if (isValidReg(start[0])){
					printf("%c", start[0]);
					start++;
				}else {
					fprintf(stderr, "No existe el registro `%c`", start[0]);
					abort();
				}
				break;
			case Numero:
			case Direccion:
				printf("%d", *(int*)start);
				start+=4;
				break;
			}
			printf(",");
		}
		printf("\n");
	}
}

#define call_translate(N, m) \
	if( !strcmp(line, #N )) saver = m; else

void assembleLine(char* begin, int offset, void(*save)(short, unsigned int*, char*), t_labels* labels){
	char* line, *aux;
	int oldOffset = offset;
	while( (offset >= 0) && (*(begin+(offset--)) != '^') );
	if( offset == 0 || begin[0] == '^' )
			return;
	if( offset < 0 )
		offset = oldOffset;
	else
		offset++;

	aux = line = calloc(offset+2, sizeof(char));
	sprintf(line, "%.*s", offset, begin);
	static unsigned int position = 0;

	static bool isData=false;

	if(line[0] == ':'){
		postTranslate(line+1, position, labels, save);
		} else {
		if( !strcmp(line, "DATA") ){
			isData=true;
		} else {
			if(isData){
				if(line[0] == '"')
					save(strlen(line+1), &position, line+1);
				else{
					int aux = atoi(line);
					save(4, &position, (void*)&aux);
				}
			} else {
				t_rule r = searchRule(line);
				save(LITERAL_SIZE, &position, r.literal);
				line+=LITERAL_SIZE+1;
				unsigned int i, saver;
				line = strtok(line, ",");
				for(i=0; i<r.opCount; i++){
					if(line == NULL){
						fprintf(stderr, "Faltan parametros para `%4s`", r.literal );
						abort();
					}
					switch (r.opType[i]) {
						case Registro:
							if( isValidReg(line[0]) )
								save(1, &position, line);
							else{
								fprintf(stderr, "No existe el registro `%c`", line[0]);
								abort();
							}
							break;
						case Numero: case Direccion:
							if(line[0] == '#'){
								saver = getOrSubscribePos(line+1, position, labels);
							} else
								saver = atoi(line);
							if( !strncmp(r.literal, "INTE", LITERAL_SIZE)){
								#include "sintax/syscallLibraryPointers.txt"
								{
									fprintf(stderr, "No se encontro el syscall `%s`", line);
									saver = atoi(line);
								}
							}
							save(4, &position, (void*)&saver);
							break;
					}
					line = strtok(NULL, ",");
				}
			}
		}
	}
	free(aux);
}
