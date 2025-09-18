#include <string.h>
#include "user.h"
#include "listdin.h"

// Fungsi inisialisasi akun
void initAkun(Akun *a)
{
    a->Id = -1;

    // Set semua string ke kosong
    a->Username[0] = '\0';
    a->Password[0] = '\0';
    a->Role[0] = '\0';
    a->RiwayatPenyakit[0] = '\0';

    // Inisialisasi numeric dengan sentinel value -1
    a->SuhuTubuh = -1;
    a->TekananDarahSistolik = -1;
    a->TekananDarahDiastolik = -1;
    a->DetakJantung = -1;
    a->SaturasiOksigen = -1;
    a->KadarGulaDarah = -1;
    a->BeratBadan = -1;
    a->TinggiBadan = -1;
    a->KadarKolesterol = -1;
    a->Trombosit = -1;

    // Inisialisasi inventoryObat
    dataObat do_;
    createTableObat(&do_, 1000);
    a->inventoryObat = do_;
    a->inventoryObat.jumlah = 0;
    a->jumlahObat = 0;
}

void capitalizeCommand(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (i == 0)
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = str[i] - 'a' + 'A';
            }
        }
        else
        {
            if (str[i] >= 'A' && str[i] <= 'Z')
            {
                str[i] = str[i] - 'A' + 'a';
            }
        }
        i++;
    }
}

int isAngka(char c)
{
    return (c >= '0' && c <= '9');
}