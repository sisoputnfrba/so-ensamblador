#include "labels.h"

void addLabel(char* start, int startSize, char* pointer, t_labels* base){
	base->x = realloc(base->x, (base->size+1)*sizeof(t_label));
	base->x[base->size].label = calloc(startSize+1, sizeof(char));
	sprintf(base->x[base->size].label, "%.*s", startSize, start);
	base->x[base->size].obs = NULL;
	base->x[base->size].point = -1;
	base->x[base->size].obsSize = 0;
	base->size++;
}
t_label* findLabel(char* needle, t_labels* haystack){
	int i;
	for(i=0; i<haystack->size; i++)
		if( !strcmp(needle, haystack->x[i].label))
			return &(haystack->x[i]);
	fprintf(stderr, "No se encontro la etiqueta `:%s`", needle);
	abort();
	return NULL;
}

t_labels* initLabels(){
	return calloc(1, sizeof(t_labels));
}
void destroyLabels(t_labels* victim){
	int i;
	for(i=0; i<victim->size; i++){
		free(victim->x[i].label);
		if(victim->x[i].obsSize != 0)
			free(victim->x[i].obs);
	}
	free(victim->x);
	free(victim);
}

unsigned int getOrSubscribePos(char* label, unsigned int where, t_labels* base){
	t_label* aux = findLabel(label, base);
	if(aux->point == -1){
		aux->obs = realloc(aux->obs, aux->obsSize+1);
		aux->obs[aux->obsSize++] = where;
		return -1;
	}
	return aux->point;
}
void postTranslate(char* label, unsigned int newData, t_labels* base, void (*fun)(short, unsigned int*, char*)){
	t_label* aux = findLabel(label, base);
	aux->point = newData;
	while( aux->obsSize-- ){
		unsigned int cache = aux->obs[aux->obsSize];
		fun(sizeof(unsigned int), &cache, (char*)&newData);
	}
	free(aux->obs);
	aux->obs=NULL;
}
