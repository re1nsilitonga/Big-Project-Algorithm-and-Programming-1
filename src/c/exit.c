#include "exit.h"

void Exit(const char *sourceFolder, dataAkun akunData, Denah denah, DataPerutPasien DPP)
{
    char respon;
    int inputvalid = 0;
    while (!inputvalid)
    {
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n): ");
        respon = getchar();
        while (getchar() != '\n')
            ;
        if (respon == 'y' || respon == 'Y') // Jika pengguna memilih untuk menyimpan
        {
            inputvalid = 1;
            Save(sourceFolder, sourceFolder, akunData, denah, DPP);
        }
        else if (respon == 'n' || respon == 'N') // Jika pengguna memilih untuk tidak menyimpan
        {
            inputvalid = 1;
        }
        else  // Jika input tidak valid
        {
            printf("Input tidak valid. Silakan masukkan ulang 'y' atau 'n'!\n");
        }
    }
    
    printf("Terima kasih telah menggunakan program ini. Sampai jumpa!\n");
    return;
}