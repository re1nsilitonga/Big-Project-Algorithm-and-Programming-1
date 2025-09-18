#ifndef CARI_USER_H
#define CARI_USER_H

#include "auth.h"
#include "boolean.h"
#include "listdin.h"
#include "set.h"
#include "denah.h"
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortDataAkunByID(dataAkun *da);
/* I.S. : dataAkun da terdefinisi dengan elemen-elemen akun yang belum terurut.
   F.S. : Elemen pada da diurutkan berdasarkan ID akun secara menaik. */

void cariUser(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : *isLogin == true, CurrentUser memiliki hak akses pencarian.
   F.S. : Menampilkan informasi akun (dokter & pasien) berdasarkan input pengguna. */

void cariPasien(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : *isLogin == true, CurrentUser adalah dokter atau manajer.
   F.S. : Menampilkan daftar pasien berdasarkan ID atau nama sesuai input. */

void cariDokter(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : *isLogin == true, CurrentUser adalah manajer.
   F.S. : Menampilkan daftar dokter berdasarkan ID atau nama sesuai input. */

int binarySearchID(dataAkun *da, int targetId);
/* I.S. : dataAkun da terurut berdasarkan ID akun.
   F.S. : Mengembalikan indeks akun dengan ID == targetId, atau -1 jika tidak ditemukan. */

int sequentialSearchName(dataAkun *da, const char *targetUsername);
/* I.S. : da terdefinisi, targetUsername valid.
   F.S. : Mengembalikan indeks akun dengan nama == targetUsername (case-insensitive), atau -1 jika tidak ditemukan. */

#endif
