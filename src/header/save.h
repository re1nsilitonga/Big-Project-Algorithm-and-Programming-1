#ifndef SAVE_H
#define SAVE_H

#include "user.h" 
#include "dataperut.h"

void Save(const char *sourceFolder, const char *targetFolder, dataAkun da, Denah denah, DataPerutPasien DPP);
/* I.S. : Data akun, denah rumah sakit, dan data perut pasien terdefinisi.
   F.S. : Seluruh data disimpan ke folder tujuan (targetFolder) dengan struktur yang sesuai, 
          dan file statis dari sourceFolder disalin ke targetFolder. */

void SaveUser(const char *folderName, dataAkun akunData);
/* I.S. : Data akun terdefinisi.
   F.S. : Data akun disimpan ke file user.csv dalam folder folderName. */

void SaveKonfig(const char *folderName, Denah denah, dataAkun akunData, DataPerutPasien DPP);
/* I.S. : Data denah, akun, dan perut pasien terdefinisi.
   F.S. : Data disimpan ke file config.txt dalam folder folderName. */

void CopyFile(const char *src, const char *dest);
/* I.S. : File src ada dan dapat dibaca.
   F.S. : File src disalin ke lokasi dest, membuat file baru atau menimpa yang lama. */

void CopyStaticFiles(const char* sourceFolder, const char* targetFolder);
/* I.S. : Folder sumber (sourceFolder) berisi file-file statis.
   F.S. : Semua file dari sourceFolder disalin ke targetFolder. */

#endif 
