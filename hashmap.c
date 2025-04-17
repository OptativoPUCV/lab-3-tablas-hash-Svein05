#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

int get_valid_location(HashMap* map, char* key)
{
    int posicionValida = hash(key, map->capacity);

    if (map->buckets[posicionValida] == NULL)
        return posicionValida;
    else
    {
        while(map->buckets[posicionValida] != NULL)
        {
            posicionValida++;
        }
        return posicionValida;
    }
}

void insertMap(HashMap * map, char * key, void * value) {

    int posicion_a_insertar = get_valid_location(map, key);
    Pair* newElemento = (Pair*) malloc(sizeof(Pair));
    if (newElemento == NULL) return EXIT_FAILURE;

    newElemento->key = key;
    newElemento->value = value;
    map->buckets[posicion_a_insertar] = newElemento;
    map->size++;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {

    HashMap* newMapa = (HashMap *) malloc(sizeof(HashMap));
    if (newMapa == NULL) return EXIT_FAILURE;

    newMapa->capacity = capacity;
    newMapa->current = -1;
    newMapa->size = 0;

    newMapa->buckets = (Pair**) calloc(capacity, sizeof(Pair*));
    if (newMapa->buckets == NULL)
    {
        free(newMapa);
        return EXIT_FAILURE;
    }

    return newMapa;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
