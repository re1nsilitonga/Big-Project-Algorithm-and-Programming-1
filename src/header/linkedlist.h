#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "user.h"
#include "boolean.h"

typedef struct NodeQueue {
    Akun *pasien;
    struct NodeQueue *next;
} NodeQueue;

typedef struct {
    NodeQueue *head;
    NodeQueue *tail;
    int length;
} LinkedListQueue;

void createLinkedListQueue(LinkedListQueue *q);
/* I.S. : Queue belum terinisialisasi atau berisi nilai tidak valid 
   F.S. : Queue kosong berhasil dibuat, pointer head dan tail bernilai NULL */

boolean isLinkedListQueueEmpty(LinkedListQueue *q);
/* I.S. : Queue mungkin kosong atau berisi beberapa elemen 
   F.S. : Mengembalikan true jika queue kosong (head == NULL), false jika tidak kosong */

void enqueueLinkedListQueue(LinkedListQueue *q, Akun *p);
/* I.S. : Queue mungkin kosong atau berisi beberapa elemen 
   F.S. : Elemen baru (pointer ke Akun) ditambahkan di akhir queue (tail) */

Akun *dequeueLinkedListQueue(LinkedListQueue *q);
/* I.S. : Queue tidak kosong (minimal ada satu elemen) 
   F.S. : Elemen pertama queue (head) dihapus dan dikembalikan, head berpindah ke elemen berikutnya */

void displayLinkedListQueue(LinkedListQueue *q);
/* I.S. : Queue mungkin kosong atau berisi elemen 
   F.S. : Isi queue ditampilkan ke layar, urut dari head ke tail */

void freeLinkedListQueue(LinkedListQueue *q);
/* I.S. : Queue mungkin berisi satu atau lebih elemen 
   F.S. : Semua node queue dibebaskan dari memori, queue menjadi kosong (head dan tail = NULL) */

Akun* peekLinkedListQueue(LinkedListQueue *queue);
/* I.S. : Queue tidak kosong 
   F.S. : Mengembalikan pointer ke elemen pertama (head) tanpa menghapusnya */


#endif
