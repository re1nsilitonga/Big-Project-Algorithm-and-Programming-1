#ifndef LOAD_H
#define LOAD_H

#include "boolean.h"
#include "listdin.h"
#include "set.h"
#include "user.h"
#include "map.h"
#include "denah.h"
#include "penyakit.h"
#include "queue.h"
#include "obat.h"
#include "dataperut.h"
#include "daftarcheckup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

boolean loadData(
    dataAkun *da,
    const char *folder,
    MapAkun *mapAkun,
    Denah *hospital,
    dataPenyakit *daPenyakit,
    MapPenyakit *mapPenyakit,
    dataObat *daObat,
    MapObat *mapObat,
    dataObatPenyakit *daObatPenyakit,
    MapObatPenyakit *mapObatPenyakit,
    DataPerutPasien *dataPerutPasien,
    DoctorQueueMap *doctorQueues);
/* I.S. : Semua struktur data masih kosong dan belum terisi dari file eksternal
   F.S. : File user.csv di folder yang diberikan dibaca;
          data akun (da), MapAkun, dan struktur pendukung lainnya (Denah, data penyakit, obat, relasi obat-penyakit, perut pasien, antrean dokter) dapat juga diproses jika diperlukan;
          data akun dan map akun diisi berdasarkan isi file user.csv;
          fungsi mengembalikan true jika pembacaan berhasil, false jika gagal */

boolean loadHospitalData(Denah *hospital, const char *folder, dataAkun *da, MapAkun *map, dataObat *data_obat, MapObat *map_obat, DataPerutPasien *dataPerut, DoctorQueueMap *doctorQueues);
/* I.S. : Struktur Denah, dataAkun, MapAkun, dataObat, MapObat, DataPerutPasien, dan DoctorQueueMap belum berisi data dari file
   F.S. : File config.txt di folder yang diberikan dibaca;
          struktur Denah rumah sakit diisi;
          data akun, obat, map-nya, dan antrean dokter dimuat;
          perut pasien yang pernah meminum obat juga diinisialisasi bila ada;
          fungsi mengembalikan true jika pembacaan berhasil, false jika gagal */

boolean loadDataPenyakit(dataPenyakit *daPenyakit, const char *folder, MapPenyakit *mapPenyakit);
/* I.S. : Struktur dataPenyakit dan MapPenyakit belum berisi data dari file
   F.S. : File penyakit.csv dari folder yang diberikan dibaca;
          daftar penyakit dan map-nya diisi;
          fungsi mengembalikan true jika pembacaan berhasil, false jika gagal */

boolean loadDataObat(dataObat *daObat, const char *folder, MapObat *mapObat);
/* I.S. : Struktur dataObat dan MapObat belum berisi data dari file
   F.S. : File obat.csv dari folder yang diberikan dibaca;
          daftar obat dan map-nya diisi;
          fungsi mengembalikan true jika pembacaan berhasil, false jika gagal */

boolean loadDataObatPenyakit(dataObatPenyakit *daObatPenyakit, const char *folder, MapObatPenyakit *mapObatPenyakit);
/* I.S. : Struktur dataObatPenyakit dan MapObatPenyakit belum berisi data dari file
   F.S. : File obat_penyakit.csv dari folder yang diberikan dibaca;
          daftar relasi obat-penyakit dan map-nya diisi;
          fungsi mengembalikan true jika pembacaan berhasil, false jika gagal */


#endif
