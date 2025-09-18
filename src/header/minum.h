#ifndef MINUM_H
#define MINUM_H

#include "auth.h"
#include "stack.h"
#include "user.h"
#include "dataperut.h"
#include "ngobatin.h"

void MinumObat(Akun *CurrentUser, boolean isLogin, DataPerutPasien *DaPerutPasien, dataAkun *da);
/* I.S. : CurrentUser adalah user yang sedang login (harus bertipe Pasien), isLogin bernilai true,
          DaPerutPasien dan data akun sudah terisi dengan data-data valid
   F.S. : Jika pasien memiliki obat di inventory, salah satu obat dapat dipilih untuk diminum.
          Obat yang diminum dimasukkan ke dalam stack perut pasien (DaPerutPasien) berdasarkan ID-nya */

void Penawar(Akun *CurrentUser, boolean isLogin, DataPerutPasien *DaPerutPasien, dataAkun *da);
/* I.S. : CurrentUser adalah user yang sedang login (harus bertipe Pasien), isLogin bernilai true,
          DaPerutPasien dan data akun sudah terisi dengan data-data valid
   F.S. : Jika pasien telah meminum obat sebelumnya (stack perut tidak kosong),
          maka satu obat terakhir yang diminum akan dihapus dari stack perut pasien */

#endif
