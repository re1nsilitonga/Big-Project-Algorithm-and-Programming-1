#ifndef AUTH_H
#define AUTH_H

#include "boolean.h"
#include "listdin.h"
#include "set.h"
#include "denah.h"
#include "user.h"
#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void flushInput();
/* I.S. : Terdapat karakter sisa di dalam buffer input (stdin).
   F.S. : Buffer input dikosongkan hingga newline ('\n') atau EOF. */

void stripNewline(char *input);
/* I.S. : input adalah string yang kemungkinan berakhiran '\n'.
   F.S. : Jika ditemukan '\n' dalam input, karakter tersebut diganti dengan '\0'. */

void registerAccount(dataAkun *da, MapAkun *akunMap, Akun *akun);
/* I.S. : da dan akunMap terdefinisi, akun belum ditambahkan.
   F.S. : Akun baru ditambahkan ke da dan akunMap jika username belum digunakan. */

int findAccount(dataAkun *da, const char username[]);
/* I.S. : da berisi daftar akun valid.
   F.S. : Mengembalikan indeks akun dengan username sesuai jika ditemukan, -1 jika tidak. */

void login(dataAkun *da, Akun *akun, boolean *isLogin);
/* I.S. : *isLogin bernilai false, akun berisi data kosong.
   F.S. : Jika login berhasil, *isLogin bernilai true dan akun berisi data user yang login. */

void logout(Akun *CurrentUser, boolean *isLogin);
/* I.S. : *isLogin bernilai true, CurrentUser berisi data user yang sedang login.
   F.S. : *isLogin bernilai false, CurrentUser dikosongkan. */

void regist(dataAkun *da, MapAkun *akunMap, boolean isLogin);
/* I.S. : *isLogin bernilai false, daftar akun (da dan akunMap) terdefinisi.
   F.S. : Jika username valid dan belum digunakan, akun pasien baru ditambahkan. */

void TambahDokter(dataAkun *da, MapAkun *akunMap, Akun *CurrentUser, boolean isLogin);
/* I.S. : *isLogin == true dan CurrentUser memiliki role "manager".
   F.S. : Jika input valid, akun dokter baru ditambahkan ke sistem. */

void AssignDokter(Denah *hospital, dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : *isLogin == true, CurrentUser adalah manager, hospital dan da terdefinisi.
   F.S. : Dokter yang valid ditugaskan ke ruangan sesuai permintaan. */

void forgotPassword(dataAkun *da, Akun *CurrentUser, boolean *isLogin);
/* I.S. : *isLogin bernilai false, user belum login.
   F.S. : Jika username ditemukan dan proses validasi berhasil, password akun diubah. */

void help(Akun *akun, boolean *isLogin);
/* I.S. : akun bisa kosong atau berisi data login, *isLogin bebas.
   F.S. : Menampilkan daftar perintah yang tersedia sesuai status login. */

#endif
