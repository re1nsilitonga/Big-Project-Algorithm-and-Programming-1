#ifndef STACK_H
#define STACK_H

#include "boolean.h"
#include "obat.h"

#define Nil -1
#define MaxEl 100

typedef struct{
    Obat data[MaxEl]; // Array of obat
    int TOP; // Elemen puncak
} Stack;

#define Top(S) (S).TOP
#define InfoTop(S) (S).data[(S).TOP]

void CreateEmpty(Stack *S);
/* I.S. : Stack S belum terinisialisasi.
   F.S. : Stack S terinisialisasi kosong (top berada pada posisi -1). */

boolean IsEmpty(Stack S);
/* I.S. : Stack S terdefinisi.
   F.S. : Mengembalikan true jika Stack kosong, false jika tidak. */

boolean IsFull(Stack S);
/* I.S. : Stack S terdefinisi.
   F.S. : Mengembalikan true jika Stack penuh, false jika tidak. */

void Push(Stack * S, Obat X);
/* I.S. : Stack S terdefinisi dan mungkin kosong atau terisi sebagian (tidak penuh).
   F.S. : Elemen X ditambahkan ke atas Stack, top bertambah satu. */

void Pop(Stack * S, Obat* X);
/* I.S. : Stack S tidak kosong.
   F.S. : Elemen paling atas Stack dihapus dan disimpan dalam X, top berkurang satu. */

#endif

