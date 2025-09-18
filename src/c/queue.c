#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

void createQueue(Queue *q)
{
    q->kapasitas = INITIAL_CAPACITY;
    q->pasien = malloc(sizeof(Akun *) * q->kapasitas);
    q->length = 0;
    q->head = 0;
}

void enqueue(Queue *q, Akun *p)
{
    if (q->length == q->kapasitas)
    {
        // Resize pasien
        int newkapasitas = q->kapasitas * 2;
        Akun **newpasien = malloc(sizeof(Akun *) * newkapasitas);
        for (int i = 0; i < q->length; i++)
        {
            newpasien[i] = q->pasien[(q->head + i) % q->kapasitas];
        }
        free(q->pasien);
        q->pasien = newpasien;
        q->kapasitas = newkapasitas;
        q->head = 0;
    }

    int tail = (q->head + q->length) % q->kapasitas;
    q->pasien[tail] = p;
    q->length++;
}

Akun *dequeue(Queue *q)
{
    if (q->length == 0)
        return NULL;

    Akun *front = q->pasien[q->head];
    q->head = (q->head + 1) % q->kapasitas;
    q->length--;
    return front;
}

int isQueueEmpty(Queue *q)
{
    return q->length == 0;
}

void freeQueue(Queue *q)
{
    free(q->pasien);
    q->pasien = NULL;
    q->kapasitas = 0;
    q->length = 0;
    q->head = 0;
}
