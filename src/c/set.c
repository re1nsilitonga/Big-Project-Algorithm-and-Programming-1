#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createSet(Set *s, int capacity) {
    s->data = (char **)malloc(sizeof(char *) * capacity);
    s->size = 0;
    s->capacity = capacity;
}

void freeSet(Set *s) {
    for (int i = 0; i < s->size; ++i) {
        free(s->data[i]);
    }
    free(s->data);
    s->size = 0;
    s->capacity = 0;
}

int containsSet(Set *s, const char *value) {
    for (int i = 0; i < s->size; ++i) {
        if (strcmp(s->data[i], value) == 0)
            return 1;
    }
    return 0;
}

void insertSet(Set *s, const char *value) {
    if (containsSet(s, value))
        return;

    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, sizeof(char *) * s->capacity);
    }

    s->data[s->size] = strdup(value);
    s->size++;
}

void removeValueSet(Set *s, const char *value) {
    for (int i = 0; i < s->size; ++i) {
        if (strcmp(s->data[i], value) == 0) {
            free(s->data[i]);
            for (int j = i; j < s->size - 1; ++j) {
                s->data[j] = s->data[j + 1];
            }
            s->size--;
            return;
        }
    }
}
