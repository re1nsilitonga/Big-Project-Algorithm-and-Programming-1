#ifndef PULANGDOK_H
#define PULANGDOK_H

#include <stdio.h>
#include <string.h>
#include "boolean.h"
#include "user.h"
#include "obat.h"
#include "penyakit.h"
#include "stack.h"
#include "map.h"
#include "queue.h"
#include "linkedlist.h"
#include "denah.h"
#include "ngobatin.h"
#include "dataperut.h"
#include "diagnosis.h"

void GetUrutanObatByPenyakitFromMap(char *namaPenyakit, MapObatPenyakit *mapObatPenyakit, MapObat *mapObat, dataPenyakit *dataPenyakit, Obat *urutanObat, int *jumlahUrutan);
/* I.S. : Tersedia nama penyakit, map obat-penyakit, map obat, dan data penyakit
   F.S. : Array urutanObat berisi daftar obat yang digunakan untuk mengobati penyakit tersebut,
          jumlahUrutan menyimpan jumlah obat yang ditemukan */

void PulangDok(Akun *CurrentUser, boolean isLogin, Denah *hospital, DataPerutPasien *DaPerutPasien, MapObatPenyakit *mapObatPenyakit, MapObat *mapObat, dataPenyakit *dataPenyakit, dataAkun *da, MapLinkedListQueue *mapDoctorQueue);
/* I.S. : User login sebagai pasien, sistem berisi data pasien dan antrean
   F.S. : pasien keluar dari sistem antrean, pasien terakhir yang ditangani akan disembuhkan (obat diberikan),
          perut pasien diperbarui jika sesuai, dan data antrean pasien dihapus dari map */

#endif
