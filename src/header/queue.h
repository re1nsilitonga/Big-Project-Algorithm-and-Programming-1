#ifndef QUEUE_H
#define QUEUE_H

#include "user.h"
#include "user.h"
#include "boolean.h"
#include "map.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 1000

typedef struct
{
    Akun **pasien; // array pointer ke Akun (pasien)
    int kapasitas; // kapasitas array
    int length;    // jumlah elemen saat ini
    int head;      // indeks head (elemen pertama)
} Queue;


void createQueue(Queue *q);
/* I.S. : Queue q belum terinisialisasi
   F.S. : Queue q terinisialisasi dalam keadaan kosong */

void enqueue(Queue *q, Akun *p);
/* I.S. : Queue q terdefinisi, p menunjuk ke data Akun yang valid
   F.S. : Data Akun *p ditambahkan ke belakang queue */

Akun *dequeue(Queue *q);
/* I.S. : Queue q tidak kosong
   F.S. : Elemen pertama queue dihapus dan dikembalikan sebagai hasil fungsi */

int isQueueEmpty(Queue *q);
/* I.S. : Queue q terdefinisi
   F.S. : Mengembalikan 1 jika queue kosong, 0 jika tidak */

void freeQueue(Queue *q);
void freeQueue(Queue *q);
/* I.S. : Queue q terdefinisi dan mungkin berisi elemen
   F.S. : Semua elemen dalam queue dibebaskan dari memori dan queue dikosongkan */

#endif
