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

    if (map->buckets[posicionValida] == NULL || map->buckets[posicionValida]->key == NULL)
        return posicionValida;
    else 
    {
        while(map->buckets[posicionValida] != NULL && map->buckets[posicionValida]->key != NULL)
        {
            posicionValida = (posicionValida + 1) % map->capacity;
        }
        return posicionValida;
    }
}

void insertMap(HashMap * map, char * key, void * value) {

    int posicion_a_insertar = get_valid_location(map, key);
    Pair* newElemento = (Pair*) malloc(sizeof(Pair));
    if (newElemento == NULL) return;

    newElemento->key = key;
    newElemento->value = value;
    map->buckets[posicion_a_insertar] = newElemento;
    map->size++;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

    int old_capacity = map->capacity;
    Pair** old_pair = map->buckets;
    map->capacity = 2 * old_capacity;
    map->buckets = (Pair**) calloc(map->capacity, sizeof(Pair*));
    map->size = 0;

    for (int i = 0 ; i < old_capacity ; i++)
    {
        if (old_pair[i] != NULL)
        {
            insertMap(map, old_pair[i]->key, old_pair[i]->value);
            free(old_pair[i]);
        }
    }
    free(old_pair);
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

    Pair* bucket_eliminar = searchMap(map, key);
    if (bucket_eliminar == NULL) return;

    bucket_eliminar->key = NULL;
    map->size--;

    return;
}

Pair * searchMap(HashMap * map,  char * key) {   

    int pos = hash(key, map->capacity);
    if (map->buckets[pos] != NULL && map->buckets[pos]->key != NULL && is_equal(map->buckets[pos]->key, key))
    {
        map->current = pos;
        return map->buckets[pos];
    }
    else
    {
        while (map->buckets[pos] != NULL)
        {
            if (map->buckets[pos]->key != NULL && is_equal(map->buckets[pos]->key, key))
            {
                map->current = pos;
                return map->buckets[pos];
            }
            
            pos = (pos + 1) % map->capacity;
        }
        return NULL;
    }
}

Pair * firstMap(HashMap * map) {

    int pos = 0;
    while (pos < map->capacity && (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL))
    {
        pos++;
    }

    if (pos == map->capacity) return NULL;

    map->current = pos;
    return map->buckets[pos];
}

Pair * nextMap(HashMap * map) {

    int pos = map->current + 1;
    while (pos < map->capacity && (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL))
    {
        pos++;
    }

    if (pos == map->capacity && map->buckets[pos] == NULL) return NULL;

    map->current = pos;
    return map->buckets[pos];
}
