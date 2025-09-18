#include <stdlib.h>
#include <string.h>
#include "obat.h"

void insertLastObat(dataObat *list, Obat obat) {
    if (list->jumlah == list->kapasitas) {
        // Expand kapasitas
        int new_kapasitas = (list->kapasitas == 0) ? 2 : list->kapasitas * 2;
        list->data = realloc(list->data, new_kapasitas * sizeof(Obat));
        list->kapasitas = new_kapasitas;
    }
    list->data[list->jumlah++] = obat;
}
