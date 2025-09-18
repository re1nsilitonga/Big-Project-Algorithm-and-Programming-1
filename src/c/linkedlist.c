#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

void createLinkedListQueue(LinkedListQueue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
}

boolean isLinkedListQueueEmpty(LinkedListQueue *q) {
    return q->head == NULL;
}

void enqueueLinkedListQueue(LinkedListQueue *q, Akun *p) {
    NodeQueue *newNode = (NodeQueue *)malloc(sizeof(NodeQueue));
    if (newNode == NULL) {
        fprintf(stderr, "Alokasi memori gagal untuk NodeQueue.\n");
        exit(EXIT_FAILURE);
    }
    newNode->pasien = p;
    newNode->next = NULL;

    if (isLinkedListQueueEmpty(q)) {
        q->head = newNode;
        q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->length++;
}

Akun *dequeueLinkedListQueue(LinkedListQueue *q) {
    if (isLinkedListQueueEmpty(q)) {
        return NULL;
    }

    NodeQueue *temp = q->head;
    Akun *pasien = temp->pasien;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(temp);
    q->length--;
    return pasien;
}

void displayLinkedListQueue(LinkedListQueue *q) {
    if (isLinkedListQueueEmpty(q)) {
        printf("Antrian kosong.\n");
        return;
    }

    NodeQueue *current = q->head;
    int i = 1;
    printf("Isi Antrian (%d pasien):\n", q->length);
    while (current != NULL) {
        printf("%d. ID: %d, Nama: %s\n", i++, current->pasien->Id, current->pasien->Username);
        current = current->next;
    }
}

void freeLinkedListQueue(LinkedListQueue *q) {
    NodeQueue *current = q->head;
    NodeQueue *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
}

Akun* peekLinkedListQueue(LinkedListQueue *q) {
    if (isLinkedListQueueEmpty(q)) {
        return NULL;
    }
    return q->head->pasien;
}
