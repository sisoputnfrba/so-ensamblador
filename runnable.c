#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "assemble.h"


FILE* saveTo = NULL;


void print(short sz, unsigned int *where, char* m){
	int i;
	printf("[%3d]\t", *where);
	for(i=0; i<sz; i++)
		printf("%c(%3d) ", m[i], m[i]);
	printf("\n");
	*where += sz;
}

void save(short sz, unsigned int *where, char* m){
	fseek(saveTo, *where, SEEK_SET);
	fwrite(m, sz, 1, saveTo);
	*where += sz;
}

void savePrint(short sz, unsigned int *where, char* m){
	print(sz, where, m);
	*where -= sz; //Correjir por hacelo 2 veces
	save(sz, where, m);
}
#define PASS(A) \
		begin = end = buffer;\
		buffer_end = buffer + fs.st_size;\
		while( 1 ){\
			if( !(*end == EOF || *end == '\n') )\
				if(++end < buffer_end) continue;\
			A;\
			if ((begin = ++end) >= buffer_end)\
				break;\
		}


int main(int argc, char **argv) {
	char* saveFilePath = "out";
	enum{ COMPILE, DECOMPILE } mode = COMPILE;
	int c;
	void (*fun)(short, unsigned int*, char*) = save;
	opterr = 0;

	while ((c = getopt(argc, argv, "vdco:")) != -1)
		switch (c) {
		case 'v':
			fun = print;
			break;
		case 'o':
			saveFilePath = optarg;
			saveTo = (FILE*)true;
			if( fun == print )
				fun = savePrint;
			else
				fun = save;
			break;
		case 'd':
			mode = DECOMPILE;
			break;
		case 'c':
			mode = COMPILE;
			break;
		case '?':
			return 1;
		default:
			abort();
		}

	int i;

	if( saveTo ){
		if(mode == COMPILE)
			saveTo = fopen(saveFilePath, "wb");
		else
			saveTo = fopen(saveFilePath, "w");
	}


	for (i = optind; i < argc; i++){
		int fp = open(argv[i], O_RDONLY);
		if( fp == -1 ){
			fprintf(stderr, "No se encontro el input: `%s`", argv[i]);
			abort();
		}
		struct stat fs;
		char* buffer, *begin, *end, *buffer_end;
		fstat(fp, &fs);
		buffer = (char*)mmap(0, fs.st_size, PROT_READ, MAP_SHARED, fp, 0); //levantar el archivo a memoria

		if(mode == COMPILE){
			t_labels* labelTrans = initLabels();
			PASS(if(*begin== ':')
					addLabel(begin+1, end-(begin+1), begin, labelTrans)
			) //Primera pasada para encontrar todas las etiquetas
			PASS(assembleLine(begin, end-(begin), fun, labelTrans)) //Segunda pasada para traducir todo
			destroyLabels(labelTrans); //Limpiar la memoria de las etiquetas
		} else if(mode == DECOMPILE){
			decompile(buffer, buffer+fs.st_size);
		}
		munmap(buffer, fs.st_size); //Liberar el texto
		close(fp); //Cerrarlo
	}

	if( saveTo!= NULL )
		fclose(saveTo);
	puts("Done!");
	return EXIT_SUCCESS;
}
