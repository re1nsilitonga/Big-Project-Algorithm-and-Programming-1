#include "map.h"
#include <stdlib.h>
#include <stdio.h>

static int _nextPrime(int n)
{
    while (1)
    {
        boolean is_prime = true;
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
            return n;
        n++;
    }
}

static void _mapResizeAkun(MapAkun *map)
{
    int new_capacity = _nextPrime(map->capacity * 2);
    MapEntryAkun *new_data = calloc(new_capacity, sizeof(MapEntryAkun));
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->data[i].occupied)
        {
            int new_idx = map->data[i].key % new_capacity;
            while (new_data[new_idx].occupied)
            {
                new_idx = (new_idx + 1) % new_capacity;
            }
            new_data[new_idx] = map->data[i];
        }
    }
    free(map->data);
    map->data = new_data;
    map->capacity = new_capacity;
}

static void _mapResizePenyakit(MapPenyakit *map)
{
    int new_capacity = _nextPrime(map->capacity * 2);
    MapEntryPenyakit *new_data = calloc(new_capacity, sizeof(MapEntryPenyakit));
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->data[i].occupied)
        {
            int new_idx = map->data[i].key % new_capacity;
            while (new_data[new_idx].occupied)
            {
                new_idx = (new_idx + 1) % new_capacity;
            }
            new_data[new_idx] = map->data[i];
        }
    }
    free(map->data);
    map->data = new_data;
    map->capacity = new_capacity;
}

static void _mapResizeObat(MapObat *map)
{
    int new_capacity = _nextPrime(map->capacity * 2);
    MapEntryObat *new_data = calloc(new_capacity, sizeof(MapEntryObat));
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->data[i].occupied)
        {
            int new_idx = map->data[i].key % new_capacity;
            while (new_data[new_idx].occupied)
            {
                new_idx = (new_idx + 1) % new_capacity;
            }
            new_data[new_idx] = map->data[i];
        }
    }
    free(map->data);
    map->data = new_data;
    map->capacity = new_capacity;
}

static void _mapResizeObatPenyakit(MapObatPenyakit *map)
{
    int new_capacity = _nextPrime(map->capacity * 2);
    MapEntryObatPenyakit *new_data = calloc(new_capacity, sizeof(MapEntryObatPenyakit));
    for (int i = 0; i < map->capacity; i++)
    {
        if (map->data[i].occupied)
        {
            int new_idx = map->data[i].key % new_capacity;
            while (new_data[new_idx].occupied)
            {
                new_idx = (new_idx + 1) % new_capacity;
            }
            new_data[new_idx] = map->data[i];
        }
    }
    free(map->data);
    map->data = new_data;
    map->capacity = new_capacity;
}

void createMapAkun(MapAkun *map)
{
    map->data = calloc(MAP_CAPACITY, sizeof(MapEntryAkun));
    map->capacity = MAP_CAPACITY;
    map->size = 0;
}

void createMapPenyakit(MapPenyakit *map)
{
    map->data = calloc(MAP_CAPACITY, sizeof(MapEntryPenyakit));
    map->capacity = MAP_CAPACITY;
    map->size = 0;
}

void createMapObat(MapObat *map)
{
    map->data = calloc(MAP_CAPACITY, sizeof(MapEntryObat));
    map->capacity = MAP_CAPACITY;
    map->size = 0;
}

void createMapObatPenyakit(MapObatPenyakit *map)
{
    map->data = calloc(MAP_CAPACITY, sizeof(MapEntryObatPenyakit));
    map->capacity = MAP_CAPACITY;
    map->size = 0;
}

void createMapLinkedListQueue(MapLinkedListQueue *map) {
    map->data = calloc(MAP_CAPACITY, sizeof(MapEntryLinkedListQueue));
    map->capacity = MAP_CAPACITY;
    map->size = 0;
}

void insertMapAkun(MapAkun *map, int key, Akun *value)
{
    if ((float)map->size / map->capacity > MAP_LOAD_FACTOR)
    {
        _mapResizeAkun(map);
    }
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied && map->data[idx].key != key)
    {
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
        {
            fprintf(stderr, "MapAkun penuh! Gagal insert key %d\n", key);
            return;
        }
    }
    if (!map->data[idx].occupied)
        map->size++;
    map->data[idx] = (MapEntryAkun){key, value, true};
}

void insertMapPenyakit(MapPenyakit *map, int key, Penyakit *value)
{
    if ((float)map->size / map->capacity > MAP_LOAD_FACTOR)
    {
        _mapResizePenyakit(map);
    }
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied && map->data[idx].key != key)
    {
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
        {
            fprintf(stderr, "MapPenyakit penuh! Gagal insert key %d\n", key);
            return;
        }
    }
    if (!map->data[idx].occupied)
        map->size++;
    map->data[idx] = (MapEntryPenyakit){key, value, true};
}

void insertMapObat(MapObat *map, int key, Obat *value)
{
    if ((float)map->size / map->capacity > MAP_LOAD_FACTOR)
    {
        _mapResizeObat(map);
    }
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied && map->data[idx].key != key)
    {
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
        {
            fprintf(stderr, "MapObat penuh! Gagal insert key %d\n", key);
            return;
        }
    }
    if (!map->data[idx].occupied)
        map->size++;
    map->data[idx] = (MapEntryObat){key, value, true};
}

void insertMapObatPenyakit(MapObatPenyakit *map, int key, ObatPenyakit *value)
{
    if ((float)map->size / map->capacity > MAP_LOAD_FACTOR)
    {
        _mapResizeObatPenyakit(map);
    }
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied && map->data[idx].key != key)
    {
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
        {
            fprintf(stderr, "MapObatPenyakit penuh! Gagal insert key %d\n", key);
            return;
        }
    }
    if (!map->data[idx].occupied)
        map->size++;
    map->data[idx] = (MapEntryObatPenyakit){key, value, true};
}

void insertMapLinkedListQueue(MapLinkedListQueue *map, int key, LinkedListQueue *value) {
    if ((float)map->size / map->capacity > MAP_LOAD_FACTOR) {
        int new_capacity = _nextPrime(map->capacity * 2);
        MapEntryLinkedListQueue *new_data = calloc(new_capacity, sizeof(MapEntryLinkedListQueue));
        for (int i = 0; i < map->capacity; i++) {
            if (map->data[i].occupied) {
                int new_idx = map->data[i].key % new_capacity;
                while (new_data[new_idx].occupied) {
                    new_idx = (new_idx + 1) % new_capacity;
                }
                new_data[new_idx] = map->data[i];
            }
        }
        free(map->data);
        map->data = new_data;
        map->capacity = new_capacity;
    }

    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied && map->data[idx].key != key) {
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx) {
            fprintf(stderr, "MapLinkedListQueue penuh! Gagal insert key %d\n", key);
            return;
        }
    }
    if (!map->data[idx].occupied)
        map->size++;
    map->data[idx] = (MapEntryLinkedListQueue){key, value, true};
}

Akun *mapGetAkun(MapAkun *map, int key)
{
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied)
    {
        if (map->data[idx].key == key)
        {
            return map->data[idx].value;
        }
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
            break;
    }
    return NULL;
}

Penyakit *mapGetPenyakit(MapPenyakit *map, int key)
{
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied)
    {
        if (map->data[idx].key == key)
        {
            return map->data[idx].value;
        }
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
            break;
    }
    return NULL;
}

Obat *mapGetObat(MapObat *map, int key)
{
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied)
    {
        if (map->data[idx].key == key)
        {
            return map->data[idx].value;
        }
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
            break;
    }
    return NULL;
}

ObatPenyakit *mapGetObatPenyakit(MapObatPenyakit *map, int key)
{
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied)
    {
        if (map->data[idx].key == key)
        {
            return map->data[idx].value;
        }
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
            break;
    }
    return NULL;
}

LinkedListQueue *mapGetLinkedListQueue(MapLinkedListQueue *map, int key) {
    int idx = key % map->capacity;
    int start_idx = idx;
    while (map->data[idx].occupied) {
        if (map->data[idx].key == key) {
            return map->data[idx].value;
        }
        idx = (idx + 1) % map->capacity;
        if (idx == start_idx)
            break;
    }
    return NULL;
}

void freeMapAkun(MapAkun *map)
{
    free(map->data);
    map->data = NULL;
    map->capacity = 0;
    map->size = 0;
}

void freeMapPenyakit(MapPenyakit *map)
{
    free(map->data);
    map->data = NULL;
    map->capacity = 0;
    map->size = 0;
}

void freeMapObat(MapObat *map)
{
    free(map->data);
    map->data = NULL;
    map->capacity = 0;
    map->size = 0;
}

void freeMapObatPenyakit(MapObatPenyakit *map)
{
    free(map->data);
    map->data = NULL;
    map->capacity = 0;
    map->size = 0;
}

void freeMapLinkedListQueue(MapLinkedListQueue *map) {
    free(map->data);
    map->data = NULL;
    map->capacity = 0;
    map->size = 0;
}