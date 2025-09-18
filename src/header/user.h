#ifndef USER_H
#define USER_H

#include "obat.h"

typedef struct
{
    char Username[50];
    char Password[50];
    int Id;
    char Role[10];
    char RiwayatPenyakit[100];

    float SuhuTubuh;
    int TekananDarahSistolik;
    int TekananDarahDiastolik;
    int DetakJantung;
    float SaturasiOksigen;
    int KadarGulaDarah;
    float BeratBadan;
    int TinggiBadan;
    int KadarKolesterol;
    int Trombosit;

    dataObat inventoryObat;
    int jumlahObat;
} Akun;

typedef struct
{
    Akun *data;
    int jumlah;
    int kapasitas;
} dataAkun;

void initAkun(Akun *a);
/* I.S. : Pointer a mengarah ke suatu variabel bertipe Akun yang belum diinisialisasi nilainya.
   F.S. : Semua field dalam struct Akun *a di-set ke nilai default (kosong, nol, atau false sesuai tipe datanya). */

void capitalizeCommand(char *str);
/* I.S. : str merupakan string dengan huruf kecil atau campuran huruf kecil dan besar.
   F.S. : Semua huruf dalam string str dikonversi menjadi huruf kapital. */

int isAngka(char c);
/* I.S. : Karakter c terdefinisi.
   F.S. : Mengembalikan 1 jika karakter c adalah angka ('0'–'9'), dan 0 jika bukan. */

#endif
