#ifndef LISTDIN_H
#define LISTDIN_H
#include "user.h"
#include "obat.h"
#include "penyakit.h"
#include "dataperut.h"

void createTableAkun(dataAkun *da, int kapasitas);
/* I.S. : Struktur dataAkun belum terinisialisasi atau masih kosong
   F.S. : Struktur dataAkun dialokasikan dengan kapasitas tertentu dan jumlah akun di-set ke 0 */

void dealocateTableAkun(dataAkun *da);
/* I.S. : Struktur dataAkun telah dialokasikan
   F.S. : Memori untuk dataAkun dibebaskan dan pointer menjadi NULL */

void insertLastAkun(dataAkun *da, Akun akun);
/* I.S. : Struktur dataAkun telah dialokasikan dan belum penuh
   F.S. : Akun baru ditambahkan di akhir array dan jumlah akun bertambah satu */

void sortID(dataAkun *da, boolean asc);
/* I.S. : Data dalam dataAkun belum terurut berdasarkan ID
   F.S. : Data dalam dataAkun terurut berdasarkan ID secara ascending jika asc = true, descending jika asc = false */

void sortNama(dataAkun *da, boolean asc);
/* I.S. : Data dalam dataAkun belum terurut berdasarkan nama
   F.S. : Data dalam dataAkun terurut berdasarkan nama secara ascending jika asc = true, descending jika asc = false */


void createTableObat(dataObat *do_, int kapasitas);
/* I.S. : Struktur dataObat belum terinisialisasi
   F.S. : Struktur dataObat dialokasikan dengan kapasitas tertentu dan jumlah obat di-set ke 0 */

void dealocateTableObat(dataObat *do_);
/* I.S. : Struktur dataObat telah dialokasikan
   F.S. : Memori untuk dataObat dibebaskan dan pointer menjadi NULL */

void insertLastObat(dataObat *do_, Obat obat);
/* I.S. : Struktur dataObat telah teralokasi dan belum penuh
   F.S. : Obat baru ditambahkan di akhir array dan jumlah obat bertambah satu */

void DeleteObatAt(dataObat *do_, int idx);
/* I.S. : Terdapat elemen obat pada indeks yang valid dalam struktur dataObat
   F.S. : Obat pada indeks ke-idx dihapus, elemen setelahnya digeser ke kiri, dan jumlah obat berkurang satu */


void createTablePenyakit(dataPenyakit *dp, int kapasitas);
/* I.S. : Struktur dataPenyakit belum terinisialisasi atau tidak valid
   F.S. : Struktur dataPenyakit dialokasikan dengan kapasitas tertentu dan jumlah data di-set ke 0 */

void dealocateTablePenyakit(dataPenyakit *dp);
/* I.S. : Struktur dataPenyakit telah terisi atau dialokasikan sebelumnya
   F.S. : Memori yang digunakan oleh dataPenyakit dibebaskan dan pointer menjadi NULL */

void insertLastPenyakit(dataPenyakit *dp, Penyakit penyakit);
/* I.S. : Struktur dataPenyakit telah teralokasi dan belum penuh
   F.S. : Penyakit baru ditambahkan di akhir array dan jumlah data bertambah satu */


void createTableObatPenyakit(dataObatPenyakit *dop, int kapasitas);
/* I.S. : Struktur dataObatPenyakit belum terinisialisasi atau tidak valid
   F.S. : Struktur dataObatPenyakit dialokasikan dengan kapasitas tertentu dan jumlah data di-set ke 0 */

void dealocateTableObatPenyakit(dataObatPenyakit *dop);
/* I.S. : Struktur dataObatPenyakit telah terisi atau dialokasikan sebelumnya
   F.S. : Memori yang digunakan oleh dataObatPenyakit dibebaskan dan pointer menjadi NULL */

void insertLastObatPenyakit(dataObatPenyakit *dop, ObatPenyakit op);
/* I.S. : Struktur dataObatPenyakit telah teralokasi dan belum penuh
   F.S. : ObatPenyakit baru ditambahkan di akhir array dan jumlah data bertambah satu */


void createListAkun(Akun **akun, int kapasitas);
/* I.S. : Pointer ke array Akun belum teralokasi
   F.S. : Array Akun dialokasikan dengan kapasitas tertentu dan siap digunakan */

void dealocateListAkun(Akun **akun);
/* I.S. : Pointer ke array Akun telah dialokasikan
   F.S. : Memori untuk array Akun dibebaskan dan pointer menjadi NULL */

void insertLastListAkun(Akun **akun, Akun akunBaru, int *jumlah, int *kapasitas);
/* I.S. : Array Akun memiliki ruang yang cukup atau akan direalokasi jika penuh
   F.S. : Akun baru ditambahkan di akhir array dan jumlah akun bertambah satu.
          Jika kapasitas tidak cukup, array diperbesar sebelum penambahan */


void createTablePerutPasien(DataPerutPasien *DPP, int kapasitas);
/* I.S. : Struktur DataPerutPasien belum terinisialisasi atau tidak valid
   F.S. : Struktur DataPerutPasien dialokasikan dengan kapasitas tertentu dan jumlah di-set ke 0 */

void dealocateTablePerutPasien(DataPerutPasien *DPP);
/* I.S. : Struktur DataPerutPasien telah dialokasikan sebelumnya
   F.S. : Memori dibebaskan dan pointer menjadi NULL */

void insertLastPerutPasien(DataPerutPasien *DPP, int idPasien, Obat obatPertama);
/* I.S. : Struktur DataPerutPasien telah teralokasi dan belum penuh
   F.S. : Data pasien baru dengan ID dan obat pertama ditambahkan ke akhir array,
          stack perut pasien diinisialisasi dan diisi obat pertama, jumlah bertambah satu */


#endif
