#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "boolean.h"
#include "map.h"
#include "user.h"
#include "obat.h"
#include "daftarcheckup.h"
#include "diagnosis.h"

boolean isSehat(Akun *pasien);
/* Fungsi untuk mengecek apakah pasien sudah dalam keadaan sehat
   I.S. : pasien terdefinisi
   F.S. : mengembalikan true jika pasien sehat, false jika tidak */

void ngobatin(Akun *CurrentUser, DoctorQueueMap *doctorQueues, MapObatPenyakit *mapObatPenyakit, MapObat *mapObat, dataPenyakit *dataPenyakit, Denah *hospital);
/* I.S. : CurrentUser sedang login sebagai Dokter, doctorQueues berisi antrean pasien untuk setiap dokter,
          mapObatPenyakit dan mapObat telah berisi data relasi penyakit-obat dan data obat secara lengkap,
          dataPenyakit berisi daftar penyakit yang dikenali, hospital berisi data denah rumah sakit
   F.S. : Dokter memeriksa antrean pasiennya. Jika ada pasien dalam antrean:
          - Pasien akan diberikan obat yang sesuai dengan penyakitnya berdasarkan data ObatPenyakit
          - Obat ditambahkan ke inventory pasien
          - Pasien dikeluarkan dari antrean dokter */

#endif
