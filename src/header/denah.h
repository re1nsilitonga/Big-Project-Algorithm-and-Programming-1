#ifndef DENAH_H
#define DENAH_H

#include "user.h"
#include "boolean.h"
#include "map.h"
#include "queue.h"
#include "lihat.h"
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char kode[22];
    int jumlahPasien;
    Akun *dokter;
    Akun *pasien;
    Queue antrian;
} Ruangan;

typedef struct
{
    int panjang, lebar, kapasitasRuang, kapasitasAntrian;
    Ruangan **grid;
} Denah;

void LIHAT_DENAH(Denah *hospital, boolean isLogin);
/* I.S. : hospital terdefinisi, isLogin sudah terdefinisi.
   F.S. : Menampilkan denah rumah sakit jika user sudah login. */

void LIHAT_RUANGAN(Denah *hospital, const char *kode, boolean isLogin);
/* I.S. : hospital terdefinisi, kode ruangan terdefinisi, isLogin terdefinisi.
   F.S. : Menampilkan informasi ruangan sesuai kode jika user sudah login. */

void UBAH_DENAH(Denah *hospital, int newRows, int newCols, boolean isLogin, Akun *CurrentUser);
/* I.S. : hospital dan CurrentUser terdefinisi, isLogin terdefinisi, CurrentUser terdefinisi.
   F.S. : Denah rumah sakit diubah ukurannya menjadi newRows x newCols jika valid dan user berwenang. */

void PINDAH_DOKTER(Denah *hospital, const char *kodeAsal, const char *kodeTujuan, boolean isLogin, Akun *CurrentUser);
/* I.S. : hospital dan CurrentUser terdefinisi, isLogin == true, CurrentUser adalah manager.
   F.S. : Dokter dari ruangan kodeAsal dipindahkan ke ruangan kodeTujuan jika valid. */

void createGrid(int nRows, int nCols, Ruangan ***grid);
/* I.S. : nRows dan nCols terdefinisi dan mungkin <= 0, grid belum teralokasi.
   F.S. : grid dialokasikan dengan ukuran nRows x nCols yang sudah valid dan diinisialisasi. */

void updateGrid(Denah *hospital, int newRows, int newCols);
/* I.S. : hospital terdefinisi.
   F.S. : Denah rumah sakit diperbarui dengan ukuran newRows x newCols, data lama disesuaikan. */

void LIHAT_ANTRIAN(Denah *hospital, Akun *CurrentUser, boolean isLogin);
/* I.S. : hospital dan CurrentUser terdefinisi, isLogin terdefinisi.
   F.S. : Menampilkan daftar antrian pasien di rumah sakit sesuai hak akses CurrentUser. */

void LihatUser(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : da dan CurrentUser terdefinisi, isLogin terdefinisi.
   F.S. : Menampilkan daftar semua user jika user sudah login dan memiliki hak akses. */

void LihatPasien(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : da dan CurrentUser terdefinisi, isLogin terdefinisi.
   F.S. : Menampilkan daftar pasien yang terdaftar jika user memiliki hak akses. */

void LihatDokter(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : da dan CurrentUser terdefinisi, isLogin terdefinisi.
   F.S. : Menampilkan daftar dokter yang terdaftar jika user memiliki hak akses. */

#endif