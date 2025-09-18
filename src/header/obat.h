#ifndef OBAT_H
#define OBAT_H

#include "boolean.h"
#include "penyakit.h"

typedef struct
{
    int id;        // obat_id
    char nama[64]; // nama_obat
} Obat;

typedef struct
{
    Obat *data;    // array of Obat
    int jumlah;    // jumlah obat
    int kapasitas; // kapasitas obat
} dataObat;

typedef struct
{
    Obat obat;         // relasi ke Obat
    Penyakit penyakit; // relasi ke Penyakit
    int urutan_minum;  // urutan pemberian obat
} ObatPenyakit;

typedef struct
{
    ObatPenyakit *data; // array of ObatPenyakit
    int jumlah;         // jumlah relasi
    int kapasitas;      // kapasitas relasi
} dataObatPenyakit;

void insertLastObat(dataObat *list, Obat obat);
/* I.S. : list telah dialokasikan dan mungkin berisi sejumlah data obat
   F.S. : Obat baru ditambahkan di akhir list dataObat; jika kapasitas tidak cukup, list dapat diperbesar */

#endif
