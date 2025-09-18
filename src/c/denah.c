#include <stdio.h>
#include "user.h"
#include "denah.h"

// Fungsi untuk mengubah indeks ke kode ruangan A1, Z1, AA1, AB1, dst.
void indexToCode(int idx, char *kode)
{
    int n = idx + 1;
    int len = 0;
    char temp[10];
    while (n > 0)
    {
        n--;
        temp[len++] = 'A' + (n % 26);
        n /= 26;
    }
    // Reverse hasil
    for (int i = 0; i < len; i++)
    {
        kode[i] = temp[len - i - 1];
    }
    kode[len] = '\0';
}

// Fungsi untuk menampilkan denah rumah sakit
void LIHAT_DENAH(Denah *hospital, boolean isLogin)
{
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    int lebar_grid = 4 + (hospital->lebar * 6) - 1; // 4 untuk border kiri dan kanan, 6 untuk setiap sel (3 spasi + 3 karakter)
    int panjang_judul = strlen("DENAH RUMAH SAKIT NIMONS");
    int lebar_judul = lebar_grid > panjang_judul + 4 ? lebar_grid : panjang_judul + 4;
    int spasi = (lebar_judul - panjang_judul) / 2;

    printf("\n");
    printf("╔");
    for (int i = 0; i < lebar_judul; i++)
        printf("═");
    printf("╗\n");

    printf("║");
    for (int i = 0; i < spasi; i++)
        printf(" ");
    printf("DENAH RUMAH SAKIT NIMONS");
    for (int i = 0; i < lebar_judul - spasi - panjang_judul; i++)
        printf(" ");
    printf("║\n");

    printf("╚");
    for (int i = 0; i < lebar_judul; i++)
        printf("═");
    printf("╝\n\n");

    // Header kolom
    printf("     ");
    for (int j = 0; j < hospital->lebar; j++)
    {
        int num = j + 1;
        if (num < 10)
            printf("  %d   ", num);
        else
            printf(" %d   ", num);
    }
    printf("\n");

    printf("   ╔");
    for (int j = 0; j < hospital->lebar; j++)
    {
        printf("═════");
        if (j < hospital->lebar - 1)
            printf("╦");
    }
    printf("╗\n");

    for (int i = 0; i < hospital->panjang; i++)
    {
        char kode[10];
        indexToCode(i, kode);

        printf("%-3s║", kode);
        for (int j = 0; j < hospital->lebar; j++)
        {
            printf(" %-3s ║", hospital->grid[i][j].kode);
        }
        printf("\n");

        if (i < hospital->panjang - 1)
        {
            printf("   ╠");
            for (int j = 0; j < hospital->lebar; j++)
            {
                printf("═════");
                if (j < hospital->lebar - 1)
                    printf("╬");
            }
            printf("╣\n");
        }
    }

    printf("   ╚");
    for (int j = 0; j < hospital->lebar; j++)
    {
        printf("═════");
        if (j < hospital->lebar - 1)
            printf("╩");
    }
    printf("╝\n\n");
}

// Fungsi untuk mencari ruangan berdasarkan kode
Ruangan *cariRuangan(Denah *hospital, const char *kode)
{
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            if (strcmp(hospital->grid[i][j].kode, kode) == 0)
            {
                return &hospital->grid[i][j];
            }
        }
    }
    return NULL; // Tidak ditemukan
}

// Fungsi untuk menampilkan informasi ruangan tertentu
void LIHAT_RUANGAN(Denah *hospital, const char *kode, boolean isLogin)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Mencari ruangan berdasarkan kode
    Ruangan *ruangan = cariRuangan(hospital, kode);
    if (!ruangan) // Jika ruangan tidak ditemukan berikan pesan
    {
        printf("Ruangan dengan kode %s tidak ditemukan!\n", kode);
        return;
    }

    // Menampilkan detail ruangan
    printf("------------- Detail Ruangan %s -------------\n", ruangan->kode);

    if (ruangan->dokter != NULL)
    {
        printf("Kapasitas  : %d\n", hospital->kapasitasRuang);
        char capUsername[50];
        strcpy(capUsername, ruangan->dokter->Username);
        capitalizeCommand(capUsername);
        printf("Dokter     : Dr. %s\n", capUsername);
    }
    else
    {
        printf("Kapasitas  : %d\n", hospital->kapasitasRuang);
        printf("Dokter     : -\n");
    }

    if (ruangan->jumlahPasien > 0)
    {
        printf("Pasien di dalam ruangan:\n");
        for (int i = 0; i < ruangan->jumlahPasien; i++)
        {
            char capUsername[50];
            strcpy(capUsername, ruangan->pasien[i].Username);
            capitalizeCommand(capUsername);
            printf("  %d. %s\n", i + 1, capUsername);
        }
    }
    else
    {
        printf("Pasien di dalam ruangan:\n");
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    }
    printf("---------------------------------------------\n");
}

// Fungsi untuk membuat grid denah rumah sakit
void createGrid(int nRows, int nCols, Ruangan ***grid)
{
    *grid = malloc(nRows * sizeof(Ruangan *));
    for (int i = 0; i < nRows; i++)
    {
        (*grid)[i] = malloc(nCols * sizeof(Ruangan));
    }
}

// Fungsi untuk melakukan update grid denah rumah sakit
void updateGrid(Denah *hospital, int newRows, int newCols)
{
    int oldRows = hospital->panjang;
    int oldCols = hospital->lebar;

    // Tambah/kurangi baris
    if (newRows != oldRows)
    {
        hospital->grid = realloc(hospital->grid, newRows * sizeof(Ruangan *));
        if (newRows > oldRows)
        {
            // Inisialisasi baris baru
            for (int i = oldRows; i < newRows; i++)
            {
                hospital->grid[i] = malloc(newCols * sizeof(Ruangan));
                for (int j = 0; j < newCols; j++)
                {
                    char kode[10];
                    indexToCode(i, kode);
                    snprintf(hospital->grid[i][j].kode, sizeof(hospital->grid[i][j].kode), "%s%d", kode, j + 1);
                    hospital->grid[i][j].dokter = NULL;
                    hospital->grid[i][j].jumlahPasien = 0;
                    hospital->grid[i][j].pasien = NULL;
                    createQueue(&hospital->grid[i][j].antrian);
                    hospital->grid[i][j].antrian.kapasitas = hospital->kapasitasAntrian;
                }
            }
        }
        else
        {
            // Free baris yang dihapus
            for (int i = newRows; i < oldRows; i++)
            {
                free(hospital->grid[i]);
            }
        }
    }

    // Tambah/kurangi kolom pada setiap baris
    for (int i = 0; i < newRows; i++)
    {
        hospital->grid[i] = realloc(hospital->grid[i], newCols * sizeof(Ruangan));
        if (newCols > oldCols)
        {
            // Inisialisasi kolom baru
            for (int j = oldCols; j < newCols; j++)
            {
                char kode[10];
                indexToCode(i, kode);
                snprintf(hospital->grid[i][j].kode, sizeof(hospital->grid[i][j].kode), "%s%d", kode, j + 1);
                hospital->grid[i][j].dokter = NULL;
                hospital->grid[i][j].jumlahPasien = 0;
                hospital->grid[i][j].pasien = NULL;
                createQueue(&hospital->grid[i][j].antrian);
                hospital->grid[i][j].antrian.kapasitas = hospital->kapasitasAntrian;
            }
        }
    }

    // Update kode ruangan untuk semua ruangan yang masih ada
    for (int i = 0; i < newRows; i++)
    {
        for (int j = 0; j < newCols; j++)
        {
            char kode[10];
            indexToCode(i, kode);
            snprintf(hospital->grid[i][j].kode, sizeof(hospital->grid[i][j].kode), "%s%d", kode, j + 1);
        }
    }

    hospital->panjang = newRows;
    hospital->lebar = newCols;
}

// Fungsi untuk memindahkan dokter dari satu ruangan ke ruangan lain
void PINDAH_DOKTER(Denah *hospital, const char *kodeAsal, const char *kodeTujuan, boolean isLogin, Akun *CurrentUser)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    Ruangan *asal = cariRuangan(hospital, kodeAsal);
    Ruangan *tujuan = cariRuangan(hospital, kodeTujuan);

    if (!asal || !tujuan)
    {
        printf("Ruangan asal atau tujuan tidak ditemukan.\n");
        return;
    }
    if (!asal->dokter)
    {
        printf("Pemindahan gagal. Ruangan %s Kosong.\n", kodeAsal);
        return;
    }
    if (tujuan->dokter)
    {
        printf("Pemindahan gagal. Ruangan %s Sudah ditempati.\n", kodeTujuan);
        return;
    }

    tujuan->dokter = asal->dokter;
    asal->dokter = NULL;
    char dokterUsername[20];
    strncpy(dokterUsername, tujuan->dokter->Username, sizeof(dokterUsername) - 1);
    dokterUsername[sizeof(dokterUsername) - 1] = '\0';
    capitalizeCommand(dokterUsername);
    printf("Dr. %s berhasil dipindahkan dari ruangan %s ke ruangan %s.\n", dokterUsername, kodeAsal, kodeTujuan);
}

// Fungsi untuk mengubah ukuran denah rumah sakit
void UBAH_DENAH(Denah *hospital, int newRows, int newCols, boolean isLogin, Akun *CurrentUser)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    if (newRows <= 0 || newCols <= 0)
    {
        printf("Ukuran denah tidak valid. Harus lebih besar dari 0.\n");
        return;
    }
    // Cek apakah ada dokter/pasien di ruangan yang akan terhapus
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            if (i >= newRows || j >= newCols)
            {
                Ruangan *r = &hospital->grid[i][j];
                if (r->dokter)
                {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh %s. Silakan pindahkan dokter terlebih dahulu.\n",
                           'A' + i, j + 1, r->dokter->Username);
                    return;
                }
                if (r->jumlahPasien > 0)
                {
                    printf("Tidak dapat mengubah ukuran denah. Ruangan %c%d masih ditempati oleh pasien. Silakan pindahkan pasien terlebih dahulu.\n",
                           'A' + i, j + 1);
                    return;
                }
            }
        }
    }

    updateGrid(hospital, newRows, newCols);
    printf("Denah rumah sakit berhasil diubah menjadi %d baris dan %d kolom.\n", newRows, newCols);
}

// Fungsi untuk melihat antrian pasien di setiap ruangan
void LIHAT_ANTRIAN(Denah *hospital, Akun *CurrentUser, boolean isLogin)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    LIHAT_DENAH(hospital, isLogin);

    for (int i = 0; i < hospital->panjang; ++i)
    {
        for (int j = 0; j < hospital->lebar; ++j)
        {
            Ruangan *ruangan = &hospital->grid[i][j];
            if (ruangan->dokter == NULL)
                continue; // skip ruangan kosong

            // Cek apakah ruangan memiliki pasien atau antrian
            boolean adaPasien = ruangan->jumlahPasien > 0;
            boolean adaAntrian = ruangan->antrian.length > 0;

            char dokterUsername[20];
            strncpy(dokterUsername, ruangan->dokter->Username, sizeof(dokterUsername) - 1);
            dokterUsername[sizeof(dokterUsername) - 1] = '\0';
            capitalizeCommand(dokterUsername);

            // Header ruangan
            printf("============ %s ============\n", ruangan->kode);
            printf("Kapasitas  : %d\n", hospital->kapasitasRuang);
            printf("Dokter     : Dr. %s\n", dokterUsername);

            // Pasien di dalam ruangan
            printf("Pasien di dalam ruangan:\n");
            if (ruangan->jumlahPasien > 0 && ruangan->pasien != NULL)
            {
                for (int k = 0; k < ruangan->jumlahPasien; ++k)
                {
                    char pasienUsername[20];
                    strncpy(pasienUsername, ruangan->pasien[k].Username, sizeof(pasienUsername) - 1);
                    pasienUsername[sizeof(pasienUsername) - 1] = '\0';
                    capitalizeCommand(pasienUsername);
                    printf("  %d. %s\n", k + 1, pasienUsername);
                }
            }
            else
            {
                printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
            }

            // Antrian pasien
            printf("Pasien di antrian:\n");
            if (ruangan->antrian.length > 0 && ruangan->antrian.pasien != NULL)
            {
                for (int k = 0; k < ruangan->antrian.length; ++k)
                {
                    char pasienAntrianUsername[20];
                    strncpy(
                        pasienAntrianUsername,
                        ruangan->antrian.pasien[(ruangan->antrian.head + k) % ruangan->antrian.kapasitas]->Username,
                        sizeof(pasienAntrianUsername) - 1);
                    pasienAntrianUsername[sizeof(pasienAntrianUsername) - 1] = '\0';
                    capitalizeCommand(pasienAntrianUsername);
                    printf("  %d. %s\n", k + 1, pasienAntrianUsername);
                }
            }
            else
            {
                printf("  Tidak ada pasien di antrian saat ini.\n");
            }
        }
    }
}