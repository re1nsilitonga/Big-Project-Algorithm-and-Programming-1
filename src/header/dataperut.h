#ifndef DATAPERUT_H
#define DATAPERUT_H

#include "stack.h"

// Struktur untuk menyimpan data perut pasien
typedef struct {
    int IdPasien;
    Stack Perut;
} PerutPasien;

// Struktur untuk menyimpan data perut seluruh pasien
typedef struct {
    PerutPasien *data;
    int jumlah;
    int kapasitas;
} DataPerutPasien;

#endif
