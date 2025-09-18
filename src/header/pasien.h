#ifndef PASIEN_H
#define PASIEN_H
#include "user.h"
#include "denah.h"

void antrianSaya(Denah *hospital, Akun *CurrentUser, boolean isLogin);
/* I.S. : User telah login sebagai pasien, hospital berisi antrean pasien di tiap ruangan
   F.S. : Menampilkan informasi antrean user saat ini di rumah sakit (jika ada) beserta posisinya dalam antrean */

void skipAntrian(Denah *hospital, Akun *CurrentUser, boolean isLogin);
/* I.S. : User telah login sebagai pasien, hospital berisi antrean pasien di tiap ruangan
   F.S. : Jika user berada dalam antrean, posisinya ditukar dengan pasien berikutnya (jika ada) dalam antrean tersebut */

void cancelAntrian(Denah *hospital, Akun *CurrentUser, boolean isLogin);
/* I.S. : User telah login sebagai pasien, hospital berisi antrean pasien di tiap ruangan
   F.S. : Jika user berada dalam antrean, maka user dikeluarkan dari antrean tersebut */

#endif
