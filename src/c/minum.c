#include "minum.h"

void InitPerut(dataAkun *da, DataPerutPasien *DPP)
{
    // Data Perut Pasien
    for (int i = 0; i < da->jumlah; i++)
    {
        if (strcmp(da->data[i].Role, "pasien") == 0)
        {
            // Cek apakah sudah ada entri untuk pasien ini
            int sudahAda = 0;
            for (int j = 0; j < DPP->jumlah; j++)
            {
                if (DPP->data[j].IdPasien == da->data[i].Id)
                {
                    sudahAda = 1;
                    break;
                }
            }
            if (!sudahAda)
            {
                CreateEmpty(&(DPP->data[DPP->jumlah].Perut));
                DPP->data[DPP->jumlah].IdPasien = da->data[i].Id;
                DPP->jumlah++;
            }
        }
    }
}

void MinumObat(Akun *CurrentUser, boolean isLogin, DataPerutPasien *DaPerutPasien, dataAkun *da)
{
    int idx;
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "pasien") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh pasien!\n");
        return;
    }

    for (int i = 0; i < da->jumlah; i++)
    {
        if (da->data[i].Id == CurrentUser->Id)
        {
            idx = i;
        }
    }

    if (isSehat(CurrentUser))
    {
        printf("Kamu udah sembuh, tidak perlu minum obat lagi!\n");
        return;
    }

    // Jika pengguna adalah pasien
    if (da->data[idx].inventoryObat.jumlah == 0)
    {
        printf("Kamu tidak memiliki obat di inventory.\n");
        return;
    }

    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < da->data[idx].inventoryObat.jumlah; i++)
    {
        printf("%d. %s\n", i + 1, da->data[idx].inventoryObat.data[i].nama);
    }

    char input[100];
    printf(">>> Pilih obat untuk diminum: ");
    fgets(input, sizeof(input), stdin);

    // Hapus newline di akhir jika ada
    input[strcspn(input, "\n")] = '\0';

    // Validasi: apakah semua karakter adalah digit
    boolean isAngka = true;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!(input[i] >= '0' && input[i] <= '9'))
        {
            isAngka = false;
            break;
        }
    }

    if (!isAngka)
    {
        printf("Input tidak valid. Masukkan angka.\n");
        return;
    }

    int pilihan = atoi(input) - 1;

    // Jika pilihan tidak valid
    if (pilihan < 0 || pilihan >= da->data[idx].inventoryObat.jumlah)
    {
        printf("Pilihan tidak valid.\n");
        return;
    }

    // Pilihan valid
    Obat obatDipilih = da->data[idx].inventoryObat.data[pilihan];
    boolean found = false;
    for (int i = 0; i < DaPerutPasien->jumlah; i++)
    {
        if (DaPerutPasien->data[i].IdPasien == CurrentUser->Id)
        {
            Push(&(DaPerutPasien->data[i].Perut), obatDipilih);
            found = true;
            break;
        }
    }
    // Jika belum ada entri perut untuk pasien ini, tambahkan satu entri baru
    if (!found)
    {
        insertLastPerutPasien(DaPerutPasien, CurrentUser->Id, obatDipilih);
        found = true;
    }

    // Hapus obat dari inventory
    DeleteObatAt(&(da->data[idx].inventoryObat), pilihan);

    printf("GLEKGLEKGLEK... %s berhasil diminum!\n", obatDipilih.nama);
}

void Penawar(Akun *CurrentUser, boolean isLogin, DataPerutPasien *DaPerutPasien, dataAkun *da)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "pasien") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh pasien!\n");
        return;
    }

    Obat ObatBuang;
    boolean found = false;
    for (int i = 0; i < DaPerutPasien->jumlah; i++)
    {
        if (DaPerutPasien->data[i].IdPasien == CurrentUser->Id)
        {
            if (IsEmpty(DaPerutPasien->data[i].Perut))
            {
                printf("Perut kosong belum ada obat yang dimakan.\n");
                return;
            }
            Pop(&(DaPerutPasien->data[i].Perut), &ObatBuang);
            found = true;
            break;
        }
    }
    if (!found)
    {
        printf("Data perut pasien tidak ditemukan.\n");
        return;
    }

    // Tambah obat ke inventory
    for (int i = 0; i < da->jumlah; i++)
    {
        if (da->data[i].Id == CurrentUser->Id)
        {
            insertLastObat(&(da->data[i].inventoryObat), ObatBuang);
        }
    }
    printf("UWEKKK... %s keluar dan kembali ke inventory!\n", ObatBuang.nama);
}