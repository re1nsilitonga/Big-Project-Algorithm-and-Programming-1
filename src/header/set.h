#ifndef SET_H
#define SET_H

typedef struct {
    char **data;  // Array of strings
    int size;     // Jumlah elemen saat ini
    int capacity; // Kapasitas maksimum sebelum realloc
} Set;

void createSet(Set *s, int capacity);
/* I.S. : Set belum terinisialisasi.
   F.S. : Set terinisialisasi dengan kapasitas awal sebesar 'capacity' dan kosong. */

void freeSet(Set *s);
/* I.S. : Set telah terisi atau belum, memori dialokasikan.
   F.S. : Semua memori yang digunakan Set dibebaskan. */

int containsSet(Set *s, const char *value);
/* I.S. : Set dan nilai 'value' terdefinisi.
   F.S. : Mengembalikan nilai 1 jika 'value' ada dalam Set, 0 jika tidak ada. */

void insertSet(Set *s, const char *value);
/* I.S. : Set terdefinisi dan mungkin sudah berisi beberapa nilai.
   F.S. : Jika 'value' belum ada, maka 'value' ditambahkan ke dalam Set. */

void removeValueSet(Set *s, const char *value);
/* I.S. : Set terdefinisi dan mungkin mengandung 'value'.
   F.S. : Jika 'value' ada di dalam Set, maka nilai tersebut dihapus. */

#endif
