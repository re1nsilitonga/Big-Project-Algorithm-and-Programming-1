#include "pasien.h"

void antrianSaya(Denah *hospital, Akun *CurrentUser, boolean isLogin)
{
    printf("\n");
    // Validasi apakah pengguna sudah login
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Validasi apakah pengguna adalah pasien
    if (strcmp(CurrentUser->Role, "pasien") != 0)
    { // Bukan pasien
        printf("Menu ini hanya dapat diakses oleh pasien!\n");
        return;
    }

    // Cek apakah pasien sedang berada di dalam ruangan dokter
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            Ruangan *ruang = &hospital->grid[i][j];
            for (int k = 0; k < ruang->jumlahPasien; k++)
            {
                if (ruang->pasien[k].Id == CurrentUser->Id)
                {
                    printf("Anda sedang berada di dalam ruangan dokter!\n");
                    return;
                }
            }
        }
    }

    // Cek apakah pasien ada di antrian
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            for (int k = 0; k < hospital->grid[i][j].antrian.length; k++)
            {
                if (hospital->grid[i][j].antrian.pasien[k]->Id == CurrentUser->Id)
                {
                    printf("Status antrian Anda:\n");
                    char capDokterUsername[50];
                    strcpy(capDokterUsername, hospital->grid[i][j].dokter->Username);
                    capitalizeCommand(capDokterUsername);
                    printf("Dokter: %s\n", capDokterUsername);
                    printf("Ruangan: %s\n", hospital->grid[i][j].kode);
                    printf("Posisi antrian: %d dari %d\n", k + 1, hospital->grid[i][j].antrian.length);
                    return;
                }
            }
        }
    }

    printf("Anda belum terdaftar dalam antrian check-up!\n");
    printf("Silakan mendaftar untuk pemeriksaan dokter.\n");
    return;
}

void skipAntrian(Denah *hospital, Akun *CurrentUser, boolean isLogin)
{
    // Validasi apakah pengguna sudah login
    if (!isLogin)
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Validasi apakah pengguna adalah pasien
    if (strcmp(CurrentUser->Role, "pasien") != 0)
    {
        printf("Menu ini hanya dapat diakses oleh pasien!\n");
        return;
    }

    // Proses
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            Ruangan *ruang = &hospital->grid[i][j];
            for (int k = 0; k < ruang->antrian.length; k++)
            {
                if (ruang->antrian.pasien[k]->Id == CurrentUser->Id)
                {
                    if (k == 0)
                    {
                        printf("Anda sudah berada di posisi paling depan antrian! Tidak bisa skip lagi.\n");
                        return;
                    }
                    // Geser pasien di depan ke belakang satu posisi
                    Akun *temp = ruang->antrian.pasien[k];
                    for (int l = k; l > 0; l--)
                    {
                        ruang->antrian.pasien[l] = ruang->antrian.pasien[l - 1];
                    }
                    ruang->antrian.pasien[0] = temp;
                    char capDokterUsername[50];
                    strcpy(capDokterUsername, ruang->dokter->Username);
                    capitalizeCommand(capDokterUsername);
                    printf("Anda berhasil maju ke depan antrian %s di ruangan %s!\n", capDokterUsername, ruang->kode);
                    printf("Posisi antrian Anda sekarang: 1\n");
                    return;
                }
            }
        }
    }
    printf("Skip antrian gagal! Anda tidak sedang terdaftar dalam antrian manapun!\n");
}

void cancelAntrian(Denah *hospital, Akun *CurrentUser, boolean isLogin)
{
    // Validasi apakah pengguna sudah login
    if (!isLogin)
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Validasi apakah pengguna adalah pasien
    if (strcmp(CurrentUser->Role, "pasien") != 0)
    {
        printf("Menu ini hanya dapat diakses oleh pasien!\n");
        return;
    }

    // Proses pembatalan antrian
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            Ruangan *ruang = &hospital->grid[i][j];
            for (int k = 0; k < ruang->antrian.length; k++)
            {
                if (ruang->antrian.pasien[k]->Id == CurrentUser->Id)
                {
                    char capDokterUsername[50];
                    strcpy(capDokterUsername, ruang->dokter->Username);
                    capitalizeCommand(capDokterUsername);
                    printf("Anda berhasil keluar dari antrian %s di ruangan %s.\n", capDokterUsername, ruang->kode);
                    // Geser pasien di belakang ke depan satu posisi, lalu kurangi panjang antrian
                    for (int l = k; l < ruang->antrian.length - 1; l++)
                    {
                        ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                    }
                    ruang->antrian.length--;
                    return;
                }
            }
        }
    }
    printf("Pembatalan antrian gagal! Anda tidak sedang terdaftar dalam antrian manapun!\n");
}