#ifndef MAP_H
#define MAP_H

#include "user.h"
#include "boolean.h"
#include "penyakit.h"
#include "obat.h"
#include <string.h>
#include "linkedlist.h"


#define MAP_CAPACITY 100007
#define MAP_LOAD_FACTOR 0.7

typedef struct
{
    int key;
    Akun *value;
    boolean occupied;
} MapEntryAkun;

typedef struct
{
    int key;
    Penyakit *value;
    boolean occupied;
} MapEntryPenyakit;

typedef struct
{
    int key;
    Obat *value;
    boolean occupied;
} MapEntryObat;

typedef struct
{
    int key;
    ObatPenyakit *value;
    boolean occupied;
} MapEntryObatPenyakit;

typedef struct
{
    MapEntryAkun *data;
    int capacity;
    int size;
} MapAkun;

typedef struct
{
    MapEntryPenyakit *data;
    int capacity;
    int size;
} MapPenyakit;

typedef struct
{
    MapEntryObat *data;
    int capacity;
    int size;
} MapObat;

typedef struct
{
    MapEntryObatPenyakit *data;
    int capacity;
    int size;
} MapObatPenyakit;

typedef struct {
    int key;
    LinkedListQueue *value;
    boolean occupied;
} MapEntryLinkedListQueue;

typedef struct {
    MapEntryLinkedListQueue *data;
    int capacity;
    int size;
} MapLinkedListQueue;

void createMapAkun(MapAkun *map);
/* I.S. : map belum terinisialisasi
   F.S. : map terinisialisasi kosong dan siap digunakan untuk penyimpanan pasangan key-value Akun */


void createMapPenyakit(MapPenyakit *map);
/* I.S. : map belum terinisialisasi
   F.S. : map terinisialisasi kosong dan siap digunakan untuk penyimpanan pasangan key-value Penyakit */

void createMapObat(MapObat *map);
/* I.S. : map belum terinisialisasi
   F.S. : map terinisialisasi kosong dan siap digunakan untuk penyimpanan pasangan key-value Obat */


void createMapObatPenyakit(MapObatPenyakit *map);
/* I.S. : map belum terinisialisasi
   F.S. : map terinisialisasi kosong dan siap digunakan untuk penyimpanan pasangan key-value ObatPenyakit */

void createMapLinkedListQueue(MapLinkedListQueue *map);
/* I.S. : map belum terinisialisasi
   F.S. : map terinisialisasi kosong dan siap digunakan untuk penyimpanan pasangan key-value LinkedListQueue */



void insertMapAkun(MapAkun *map, int key, Akun *value);
/* I.S. : map mungkin kosong atau berisi beberapa pasangan key-value
   F.S. : pasangan (key, value) ditambahkan ke dalam map atau menggantikan value jika key sudah ada */

void insertMapPenyakit(MapPenyakit *map, int key, Penyakit *value);
/* I.S. : map mungkin kosong atau berisi beberapa pasangan key-value
   F.S. : pasangan (key, value) ditambahkan ke dalam map atau menggantikan value jika key sudah ada */

void insertMapObat(MapObat *map, int key, Obat *value);
/* I.S. : map mungkin kosong atau berisi beberapa pasangan key-value
   F.S. : pasangan (key, value) ditambahkan ke dalam map atau menggantikan value jika key sudah ada */

void insertMapObatPenyakit(MapObatPenyakit *map, int key, ObatPenyakit *value);
/* I.S. : map mungkin kosong atau berisi beberapa pasangan key-value
   F.S. : pasangan (key, value) ditambahkan ke dalam map atau menggantikan value jika key sudah ada */

void insertMapLinkedListQueue(MapLinkedListQueue *map, int key, LinkedListQueue *value);
/* I.S. : map mungkin kosong atau berisi beberapa pasangan key-value
   F.S. : pasangan (key, value) ditambahkan ke dalam map atau menggantikan value jika key sudah ada */


Akun *mapGetAkun(MapAkun *map, int key);
/* I.S. : map terisi dengan beberapa pasangan key-value
   F.S. : mengembalikan pointer ke value (Akun) yang sesuai dengan key, atau NULL jika tidak ditemukan */


Penyakit *mapGetPenyakit(MapPenyakit *map, int key);
/* I.S. : map terisi dengan beberapa pasangan key-value
   F.S. : mengembalikan pointer ke value (Penyakit) yang sesuai dengan key, atau NULL jika tidak ditemukan */

Obat *mapGetObat(MapObat *map, int key);
/* I.S. : map terisi dengan beberapa pasangan key-value
   F.S. : mengembalikan pointer ke value (Obat) yang sesuai dengan key, atau NULL jika tidak ditemukan */

ObatPenyakit *mapGetObatPenyakit(MapObatPenyakit *map, int key);
/* I.S. : map terisi dengan beberapa pasangan key-value
   F.S. : mengembalikan pointer ke value (ObatPenyakit) yang sesuai dengan key, atau NULL jika tidak ditemukan */

LinkedListQueue *mapGetLinkedListQueue(MapLinkedListQueue *map, int key);
/* I.S. : map terisi dengan beberapa pasangan key-value
   F.S. : mengembalikan pointer ke value (LinkedListQueue) yang sesuai dengan key, atau NULL jika tidak ditemukan */


void freeMapAkun(MapAkun *map);
/* I.S. : map berisi pasangan key-value Akun
   F.S. : semua data pada map dibebaskan dari memori dan map menjadi kosong */

void freeMapPenyakit(MapPenyakit *map);
/* I.S. : map berisi pasangan key-value Penyakit
   F.S. : semua data pada map dibebaskan dari memori dan map menjadi kosong */

void freeMapObat(MapObat *map);
/* I.S. : map berisi pasangan key-value Obat
   F.S. : semua data pada map dibebaskan dari memori dan map menjadi kosong */

void freeMapObatPenyakit(MapObatPenyakit *map);
/* I.S. : map berisi pasangan key-value ObatPenyakit
   F.S. : semua data pada map dibebaskan dari memori dan map menjadi kosong */

void freeMapLinkedListQueue(MapLinkedListQueue *map);
/* I.S. : map berisi pasangan key-value LinkedListQueue
   F.S. : semua data pada map dibebaskan dari memori dan map menjadi kosong */


#endif
