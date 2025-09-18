#ifndef LIHAT_H
#define LIHAT_H
#include "user.h"
#include "listdin.h"
#include "boolean.h"

char toLower(char c);
/* I.S. : Menerima character c 
   F.S. : Mengubah character c menjadi huruf kecil */

void toLowerString(char *str);
/* I.S. : Menerima string str 
   F.S. : Mengubah seluruh character pada str menjadi huruf kecil */

dataAkun Filter(dataAkun da, char *filter);
/* I.S. : DataAkun terdefinisi dan filter disesuaikan referensi pengguna (pasien/dokter) 
   F.S. : Menghasilkan copy DataAkun dengan role yang telah difilter (pasien saja/dokter saja) */

dataAkun SortAscID(dataAkun da);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menghasilkan copy DataAkun yang telah disort ascending berdasarkan ID (skema sort yang digunakan adalah selection sort) */

dataAkun SortDscID(dataAkun da);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menghasilkan copy DataAkun yang telah disort descending berdasarkan ID */

dataAkun SortAscUN(dataAkun da);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menghasilkan copy DataAkun yang telah disort ascending berdasarkan username */

dataAkun SortDscUN(dataAkun da);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menghasilkan copy DataAkun yang telah disort descending berdasarkan username */

void TampilkanDataUser(dataAkun daRes, char *urutan, char *klasifikasi);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menampilkan DataAkun seluruh user yang telah disort dalam bentuk tabel */

void TampilkanDataPasien(dataAkun daRes, char *urutan, char *klasifikasi);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menampilkan DataAkun seluruh pasien yang telah disort dalam bentuk tabel */

void TampilkanDataDokter(dataAkun daRes, char *urutan, char *klasifikasi);
/* I.S. : DataAkun terdefinisi 
   F.S. : Menampilkan DataAkun seluruh dokter yang telah disort dalam bentuk tabel */

void LihatUser(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : DataAkun terdefinisi, pengguna yang sudah login dengan role manager dapat mengakses fitur ini 
   F.S. : Menampilkan data seluruh pengguna dalam bentuk tabel dengan urutan berdasarkan preferensi pengguna */

void LihatPasien(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : DataAkun terdefinisi, pengguna yang sudah login dengan role manager dapat mengakses fitur ini 
   F.S. : Menampilkan data seluruh pengguna dalam bentuk tabel dengan urutan berdasarkan preferensi pengguna */

void LihatDokter(dataAkun *da, Akun *CurrentUser, boolean isLogin);
/* I.S. : DataAkun terdefinisi, pengguna yang sudah login dengan role manager dapat mengakses fitur ini 
   F.S. : Menampilkan data seluruh pengguna dalam bentuk tabel dengan urutan berdasarkan preferensi pengguna */


#endif
