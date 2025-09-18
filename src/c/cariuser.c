#include "cariuser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fungsi mencari ID user menggunakan binary search
int binarySearchID(dataAkun *da, int targetId)
{
    int low = 0;
    int high = da->jumlah - 1;
    int mid;

    while (low <= high)
    {
        mid = low + (high - low) / 2;

        if (da->data[mid].Id == targetId)
        {
            return mid;
        }
        else if (da->data[mid].Id < targetId)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

// Print header untuk tabel cari user
void printCariUserTableHeading()
{
    printf("%-4s| %-10s | %-7s | %s\n", "ID", "Nama", "Role", "Penyakit");
    printf("----|------------|---------|----------\n");
}

// Print detail akun user yang ditemukan
void printCariUserAkunDetails(const Akun *akun)
{
    if (akun != NULL)
    {
        char capUsername[50];
        strcpy(capUsername, akun->Username);
        capitalizeCommand(capUsername);
        printf("%-4d| %-10s | %-7s | %s\n",
               akun->Id,
               capUsername,
               akun->Role,
               akun->RiwayatPenyakit);
    }
}

// Print header untuk tabel cari pasien
void printCariPasienTableHeading()
{
    printf("%-4s| %-10s | %s\n", "ID", "Nama", "Penyakit");
    printf("----|------------|----------\n");
}

// Print detail akun user yang ditemukan untuk pasien
void printCariPasienAkunDetails(const Akun *akun)
{
    if (akun != NULL)
    {
        char capUsername[50];
        strcpy(capUsername, akun->Username);
        capitalizeCommand(capUsername);
        printf("%-4d| %-10s | %-8s\n",
               akun->Id,
               capUsername,
               akun->RiwayatPenyakit);
    }
}

// Print header untuk tabel cari dokter
void printCariDokterTableHeading()
{
    printf("%-4s| %-10s\n", "ID", "Nama");
    printf("----|------------\n");
}

// Print detail akun user yang ditemukan untuk dokter
void printCariDokterAkunDetails(const Akun *akun)
{
    if (akun != NULL)
    {
        char capUsername[50];
        strcpy(capUsername, akun->Username);
        capitalizeCommand(capUsername);
        printf("%-4d| %-10s\n",
               akun->Id,
               capUsername);
    }
}

// Fungsi mencari username user menggunakan sequential search
int sequentialSearchName(dataAkun *da, const char *targetUsername)
{
    for (int i = 0; i < da->jumlah; i++)
    {
        if (strcmp(da->data[i].Username, targetUsername) == 0)
        {
            return i; // Jika ditemukan, kembalikan indeks
        }
    }
    return -1; // Kasus tidak ditemukan
}

void cariUser(dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silakan login terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Jika pengguna sudah log in maka perlu validasi role manager
    if (strcmp(CurrentUser->Role, "manager") != 0)
    {
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    char pilihanInput[10];
    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("Pilihan: ");
    fgets(pilihanInput, sizeof(pilihanInput), stdin);
    stripNewline(pilihanInput);

    // Validasi input
    if (strlen(pilihanInput) == 1 && (pilihanInput[0] == '1' || pilihanInput[0] == '2'))
    {
        pilihan = atoi(pilihanInput);
    }
    else
    {
        printf("Pilihan tidak valid. Harap masukkan '1' atau '2'.\n");
        return;
    }

    // Jika pilihan 1 maka mencari berdasarkan ID
    if (pilihan == 1)
    {
        int targetID;
        char idInput[50];
        printf("Masukkan nomor ID user: ");
        fgets(idInput, sizeof(idInput), stdin);
        stripNewline(idInput);

        // Validasi apakah input ID adalah angka
        boolean isNumeric = true;
        for (int i = 0; i < strlen(idInput); i++)
        {
            if (!isAngka(idInput[i]))
            {
                isNumeric = false;
                break;
            }
        }

        if (!isNumeric)
        {
            printf("ID tidak valid. Harap masukkan angka.\n");
            return;
        }

        targetID = atoi(idInput);

        // Pastikan data sudah terurut berdasarkan ID sebelum binary search
        dataAkun daTemp = *da;
        sortID(&daTemp, true);

        int index = binarySearchID(&daTemp, targetID);

        // Jika ditemukan, tampilkan detail akun
        if (index != -1)
        {
            // Cari index asli di da berdasarkan ID
            int idxAsli = -1;
            for (int i = 0; i < da->jumlah; i++)
            {
                if (da->data[i].Id == targetID)
                {
                    idxAsli = i;
                    break;
                }
            }
            printf("Menampilkan pengguna dengan nomor ID %d...\n", targetID);
            printCariUserTableHeading();
            if (idxAsli != -1)
                printCariUserAkunDetails(&da->data[idxAsli]);
        }
        else // Jika tidak ditemukan, tampilkan pesan
        {
            printf("Tidak ditermukan pengguna dengan ID %d\n", targetID);
        }
    }

    // Jika pilihan 2 maka mencari berdasarkan nama
    else if (pilihan == 2)
    {
        char targetUsername[50];
        printf("Masukkan nama user: ");
        fgets(targetUsername, sizeof(targetUsername), stdin);
        stripNewline(targetUsername);

        // Mencari indeks akun berdasarkan nama menggunakan sequential search
        int index = sequentialSearchName(da, targetUsername);

        // Jika ditemukan, tampilkan detail akun
        if (index != -1)
        {
            printf("Menampilkan pengguna dengan nama %s...\n", targetUsername);
            printCariUserTableHeading();
            printCariUserAkunDetails(&da->data[index]);
        }
        else // Jika tidak ditemukan, tampilkan pesan
        {
            printf("Tidak ditemukan pengguna dengan nama %s!\n", targetUsername);
        }
    }
}

// Fungsi untuk mencari pasien berdasarkan ID, nama, atau penyakit
void cariPasien(dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silakan login terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    char pilihanInput[10];
    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Penyakit\n");
    printf("Pilihan: ");
    fgets(pilihanInput, sizeof(pilihanInput), stdin);
    stripNewline(pilihanInput);

    // Validasi input
    if (strlen(pilihanInput) == 1 && (pilihanInput[0] == '1' || pilihanInput[0] == '2' || pilihanInput[0] == '3'))
    {
        pilihan = atoi(pilihanInput);
    }
    else
    {
        printf("Pilihan tidak valid. Harap masukkan '1', '2', atau '3'.\n");
        return;
    }

    // Jika pilihan 1 maka mencari berdasarkan ID
    if (pilihan == 1)
    {
        int targetID;
        char idInput[50];
        printf("Masukkan nomor ID pasien: ");
        fgets(idInput, sizeof(idInput), stdin);
        stripNewline(idInput);

        // Validasi apakah input ID adalah angka
        boolean isNumeric = true;
        for (int i = 0; i < strlen(idInput); i++)
        {
            if (!isAngka(idInput[i]))
            {
                isNumeric = false;
                break;
            }
        }

        if (!isNumeric)
        {
            printf("ID tidak valid. Harap masukkan angka.\n");
            return;
        }

        targetID = atoi(idInput);

        // Pastikan data sudah terurut berdasarkan ID sebelum binary search
        dataAkun daTemp = *da;
        sortID(&daTemp, true);

        int foundIndex = binarySearchID(&daTemp, targetID);

        if (foundIndex != -1)
        {
            // Cari index asli di da berdasarkan ID dan role pasien
            int idxAsli = -1;
            for (int i = 0; i < da->jumlah; i++)
            {
                if (da->data[i].Id == targetID && strcmp(da->data[i].Role, "pasien") == 0)
                {
                    idxAsli = i;
                    break;
                }
            }
            if (idxAsli != -1)
            {
                printf("Menampilkan pasien dengan nomor ID %d...\n", targetID);
                printCariPasienTableHeading();
                printCariPasienAkunDetails(&da->data[idxAsli]);
            }
            else
            {
                printf("Tidak ditemukan pasien dengan ID %d\n", targetID);
            }
        }
        else // Jika tidak ditemukan atau bukan pasien, tampilkan pesan
        {
            printf("Tidak ditemukan pasien dengan ID %d\n", targetID);
        }
    }

    // Jika pilihan 2 maka mencari berdasarkan nama
    else if (pilihan == 2)
    {
        char targetUsername[50];
        printf("Masukkan nama pasien: ");
        fgets(targetUsername, sizeof(targetUsername), stdin);
        stripNewline(targetUsername);

        // Mencari indeks akun berdasarkan nama menggunakan sequential search
        int index = sequentialSearchName(da, targetUsername);

        if (index != -1 && strcmp(da->data[index].Role, "pasien") == 0)
        {
            printf("Menampilkan pasien dengan nama %s...\n", targetUsername);
            printCariPasienTableHeading();
            printCariPasienAkunDetails(&da->data[index]);
        }
        else
        {
            printf("Tidak ditemukan pasien dengan nama %s!\n", targetUsername);
        }
    }

    // Jika pilihan 3 maka mencari berdasarkan penyakit
    else if (pilihan == 3)
    {
        char targetPenyakit[100];
        printf("Masukkan nama penyakit: ");
        fgets(targetPenyakit, sizeof(targetPenyakit), stdin);
        stripNewline(targetPenyakit);

        dataAkun foundPasien;
        createTableAkun(&foundPasien, 10); // inisialisasi

        boolean foundAny = false;

        // Mengubah targetPenyakit menjadi capitalizeCommand supaya case-insensitive
        char capitalizeTargetPenyakit[100];
        strcpy(capitalizeTargetPenyakit, targetPenyakit);
        capitalizeCommand(capitalizeTargetPenyakit);

        for (int i = 0; i < da->jumlah; i++)
        {
            char capitalizeRiwayatPenyakit[100];
            strcpy(capitalizeRiwayatPenyakit, da->data[i].RiwayatPenyakit);
            capitalizeCommand(capitalizeRiwayatPenyakit);

            if (strcmp(da->data[i].Role, "pasien") == 0 && strcmp(capitalizeRiwayatPenyakit, capitalizeTargetPenyakit) == 0)
            {
                insertLastAkun(&foundPasien, da->data[i]);
                foundAny = true;
            }
        }

        // Jika tidak ditemukan pasien dengan penyakit yang dimaksud
        if (!foundAny)
        {
            printf("Tidak ditemukan pasien dengan riwayat penyakit %s.\n", targetPenyakit);
            dealocateTableAkun(&foundPasien);
            return;
        }

        // Jika ditemukan, diberikan opsi untuk mengurutkan hasil pencarian
        char pilihanUrut[10];
        int urutBerdasarkan;
        printf("Urutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf("Pilihan: ");
        fgets(pilihanUrut, sizeof(pilihanUrut), stdin);
        stripNewline(pilihanUrut);

        // Validasi input
        if (strlen(pilihanUrut) == 1 && (pilihanUrut[0] == '1' || pilihanUrut[0] == '2'))
        {
            urutBerdasarkan = atoi(pilihanUrut);
        }
        else
        {
            printf("Pilihan tidak valid. Harap masukkan '1' atau '2'.\n");
            dealocateTableAkun(&foundPasien);
            return;
        }

        char pilihanSort[10];
        int pilihanCara;

        // Menentukan cara pengurutan berdasarkan pilihan urutBerdasarkan
        printf("Urutan sort %s?\n", urutBerdasarkan == 1 ? "ID" : "Nama");
        printf("1. ASC (A-Z)\n");
        printf("2. DESC (Z-A)\n");
        printf("Pilihan: ");
        fgets(pilihanSort, sizeof(pilihanSort), stdin);
        stripNewline(pilihanSort);

        // Validasi input pilihanSort
        if (strlen(pilihanSort) == 1 && (pilihanSort[0] == '1' || pilihanSort[0] == '2'))
        {
            pilihanCara = atoi(pilihanSort);
        }
        else
        {
            printf("Pilihan tidak valid. Harap masukkan '1' atau '2'.\n");
            dealocateTableAkun(&foundPasien);
            return;
        }

        char urutan[15];
        if (foundPasien.jumlah > 1)
        {
            if (urutBerdasarkan == 1) // ID
            {
                sortID(&foundPasien, pilihanCara == 1); // Sudah sesuai dengan listdin.c
            }
            else // Nama
            {
                sortNama(&foundPasien, pilihanCara == 1); // Pastikan sortNama juga ada di listdin.c
            }
            strcpy(urutan, (pilihanCara == 1) ? "ascendant" : "descendant");
        }
        else
        {
            strcpy(urutan, (pilihanCara == 1) ? "ascendant" : "descendant");
        }

        printf("Menampilkan pasien dengan penyakit %s dengan %s terurut %s...\n", targetPenyakit, urutBerdasarkan == 1 ? "ID" : "nama", urutan);
        printCariPasienTableHeading();
        for (int i = 0; i < foundPasien.jumlah; i++)
        {
            printCariPasienAkunDetails(&foundPasien.data[i]);
        }

        dealocateTableAkun(&foundPasien);
    }
}

void cariDokter(dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silakan login terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    {
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    // Menerima input pengguna untuk memilih cara pencarian
    char pilihanInput[10];
    int pilihan;
    printf("Cari berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("Pilihan: ");
    fgets(pilihanInput, sizeof(pilihanInput), stdin);
    stripNewline(pilihanInput);

    // Validasi input
    if (strlen(pilihanInput) == 1 && (pilihanInput[0] == '1' || pilihanInput[0] == '2'))
    {
        pilihan = atoi(pilihanInput);
    }
    else
    {
        printf("Pilihan tidak valid. Harap masukkan '1' atau '2'.\n");
        return;
    }

    // Jika pilihan 1 maka mencari berdasarkan ID
    if (pilihan == 1)
    {
        int targetID;
        char idInput[50];
        printf("Masukkan nomor ID dokter: ");
        fgets(idInput, sizeof(idInput), stdin);
        stripNewline(idInput);

        boolean isNumeric = true;
        for (int i = 0; i < strlen(idInput); i++)
        {
            if (!isAngka(idInput[i]))
            {
                isNumeric = false;
                break;
            }
        }

        if (!isNumeric)
        {
            printf("ID tidak valid. Harap masukkan angka.\n");
            return;
        }

        targetID = atoi(idInput);

        // Pastikan data sudah terurut berdasarkan ID sebelum binary search
        dataAkun daTemp = *da;
        sortID(&daTemp, true);

        int foundIndex = binarySearchID(&daTemp, targetID);

        if (foundIndex != -1)
        {
            // Cari index asli di da berdasarkan ID dan role dokter
            int idxAsli = -1;
            for (int i = 0; i < da->jumlah; i++)
            {
                if (da->data[i].Id == targetID && strcmp(da->data[i].Role, "dokter") == 0)
                {
                    idxAsli = i;
                    break;
                }
            }
            if (idxAsli != -1)
            {
                printf("Menampilkan dokter dengan nomor ID %d...\n", targetID);
                printCariDokterTableHeading();
                printCariDokterAkunDetails(&da->data[idxAsli]);
            }
            else
            {
                printf("Tidak ditemukan dokter dengan ID %d\n", targetID);
            }
        }
        else
        {
            printf("Tidak ditemukan dokter dengan ID %d\n", targetID);
        }
    }

    // Jika pilihan 2 maka mencari berdasarkan nama
    else if (pilihan == 2)
    {
        char targetUsername[50];
        printf("Masukkan nama dokter: ");
        fgets(targetUsername, sizeof(targetUsername), stdin);
        stripNewline(targetUsername);

        // Mencari indeks akun berdasarkan nama menggunakan sequential search
        int index = sequentialSearchName(da, targetUsername);

        if (index != -1 && strcmp(da->data[index].Role, "dokter") == 0)
        {
            printf("Menampilkan dokter dengan nama %s...\n", targetUsername);
            printCariDokterTableHeading();
            printCariDokterAkunDetails(&da->data[index]);
        }
        else
        {
            printf("Tidak ditemukan dokter dengan nama %s!\n", targetUsername);
        }
    }
}
