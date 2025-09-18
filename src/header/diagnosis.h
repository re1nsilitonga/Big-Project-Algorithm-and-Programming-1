#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "user.h"
#include "map.h"
#include "denah.h"
#include "linkedlist.h"
#include "boolean.h"
#include "daftarcheckup.h"
#include "penyakit.h"

int stringEquals(const char *a, const char *b);
/* I.S. : a dan b adalah string valid (null-terminated)
   F.S. : mengembalikan 1 jika a sama dengan b, 0 jika tidak */

void copyString(char *dest, const char *src);
/* I.S. : dest memiliki ruang cukup, src adalah string valid (null-terminated)
   F.S. : isi dest adalah salinan string src */

boolean isDiagnosis(Akun *pasien);
/* I.S. : pasien terdefinisi (bisa NULL atau tidak), RiwayatPenyakit bisa kosong atau tidak
   F.S. : mengembalikan true jika pasien sudah punya diagnosis valid, false jika tidak */

void diagnosis(dataAkun *da, dataPenyakit *dp, MapAkun *akunMap, Akun *CurrentUser, Denah *hospital, DoctorQueueMap *doctorQueues);
/* I.S. : data terinisialisasi, CurrentUser adalah akun yang sedang login
   F.S. : pasien di ruang dokter didiagnosis dan RiwayatPenyakit pasien diperbarui sesuai hasil diagnosis */


#endif