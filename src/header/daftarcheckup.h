#ifndef DAFTARCHECKUP_H
#define DAFTARCHECKUP_H

#include "boolean.h"
#include "user.h"
#include "linkedlist.h"
#include "map.h"
#include "listdin.h"
#include "denah.h"

#define MAX_ANTRIAN 100

typedef struct
{
    MapLinkedListQueue doctorQueues;
} DoctorQueueMap;

extern dataAkun tabelAkun;
extern Akun *findDoctorById(int idDokter, dataAkun *da);
extern boolean isPatientAlreadyInQueue(Akun *pasien, DoctorQueueMap *dqm);

void createDoctorQueueMap(DoctorQueueMap *dqm);
/* I.S. : dqm belum terinisialisasi.
   F.S. : dqm terinisialisasi sebagai map kosong untuk antrian dokter. */

void checkUpRegistration(Akun *pasien, DoctorQueueMap *dqm, Denah *hospital);
/* I.S. : pasien, dqm, dan hospital terdefinisi.
   F.S. : Pasien didaftarkan ke antrian check-up dokter sesuai aturan. */

void displayPatientQueue(Akun *pasien, DoctorQueueMap *dqm);
/* I.S. : pasien dan dqm terdefinisi.
   F.S. : Menampilkan daftar antrian check-up yang sedang diikuti pasien. */

void freeDoctorQueueMap(DoctorQueueMap *dqm);
/* I.S. : dqm sudah terinisialisasi dan mungkin berisi antrian.
   F.S. : Semua memori yang terkait dengan dqm dibebaskan dan dqm dikosongkan. */
   
#endif