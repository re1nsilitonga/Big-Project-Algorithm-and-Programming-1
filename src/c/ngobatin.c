#include <stdio.h>
#include <string.h>
#include "ngobatin.h"
#include "user.h"
#include "map.h"
#include "obat.h"
#include "queue.h"

boolean isSehat(Akun *pasien)
{
    if (pasien == NULL)
        return false;

    // Pasien sehat jika RiwayatPenyakit sehat
    return strcmp(pasien->RiwayatPenyakit, "Sehat") == 0;
}

void ngobatin(Akun *CurrentUser, DoctorQueueMap *doctorQueues, MapObatPenyakit *mapObatPenyakit, MapObat *mapObat, dataPenyakit *dataPenyakit, Denah *hospital)
{
    if (!stringEquals(CurrentUser->Role, "dokter"))
    {
        printf("Akses ditolak! Fitur ini hanya untuk dokter.\n");
        return;
    }

    Ruangan *ruang_dokter = NULL;
    for (int i = 0; i < hospital->panjang && ruang_dokter == NULL; i++)
    {
        for (int j = 0; j < hospital->lebar && ruang_dokter == NULL; j++)
        {
            Ruangan *ruang = &hospital->grid[i][j];
            if (ruang->dokter != NULL && ruang->dokter->Id == CurrentUser->Id)
            {
                ruang_dokter = ruang;
            }
        }
    }

    if (ruang_dokter == NULL || ruang_dokter->jumlahPasien == 0)
    {
        printf("Tidak ada pasien di ruangan Anda.\n");
        return;
    }

    Akun *pasien = &(ruang_dokter->pasien[0]);
    extern dataAkun tabelAkun;
    Akun *real_pasien = NULL;
    for (int i = 0; i < tabelAkun.jumlah; i++)
    {
        if (tabelAkun.data[i].Id == pasien->Id)
        {
            real_pasien = &tabelAkun.data[i];
            break;
        }
    }
    if (real_pasien == NULL)
    {
        printf("Data pasien tidak ditemukan di database utama.\n");
        return;
    }

    char capPasienUsername[50];
    strcpy(capPasienUsername, pasien->Username);
    capitalizeCommand(capPasienUsername);

    // Cek apakah pasien sudah pernah didiagnosis
    if (!isDiagnosis(pasien))
    {
        printf("Pasien belum didiagnosis.\n");
        return;
    }

    if (isSehat(pasien))
    {
        printf("Pasien %s sudah dalam keadaan sehat!\n", capPasienUsername);
        return;
    }

    // Cari semua obat yang harus diberikan untuk penyakit ini
    int idPenyakitPasien = -1;
    for (int k = 0; k < dataPenyakit->jumlah; k++)
    {
        if (strcmp(dataPenyakit->data[k].NamaPenyakit, pasien->RiwayatPenyakit) == 0)
        {
            idPenyakitPasien = dataPenyakit->data[k].Id;
            break;
        }
    }

    // Kumpulkan semua obat yang harus diberikan (urutkan berdasarkan urutan_minum)
    ObatPenyakit daftarObat[32];
    int jumlahObat = 0;

    for (int i = 0; i < mapObatPenyakit->capacity; i++)
    {
        if (mapObatPenyakit->data[i].occupied)
        {
            ObatPenyakit *relasi = mapObatPenyakit->data[i].value;
            if (relasi->penyakit.Id == idPenyakitPasien)
            {
                daftarObat[jumlahObat] = *relasi;
                jumlahObat++;
            }
        }
    }

    // Urutkan berdasarkan urutan_minum
    for (int i = 0; i < jumlahObat - 1; i++)
    {
        for (int j = 0; j < jumlahObat - i - 1; j++)
        {
            if (daftarObat[j].urutan_minum > daftarObat[j + 1].urutan_minum)
            {
                ObatPenyakit temp = daftarObat[j];
                daftarObat[j] = daftarObat[j + 1];
                daftarObat[j + 1] = temp;
            }
        }
    }

    if (jumlahObat == 0)
    {
        printf("Tidak ditemukan obat yang sesuai untuk penyakit %s.\n", pasien->RiwayatPenyakit);
        return;
    }

    int obatDiberikan = 0;
    char daftarNamaObat[32][100];
    boolean semuaObatSudahAda = true;
    for (int i = 0; i < jumlahObat; i++)
    {
        // Cek apakah obat sudah ada di inventory pasien
        boolean sudahAda = false;
        for (int j = 0; j < real_pasien->inventoryObat.jumlah; j++)
        {
            if (real_pasien->inventoryObat.data[j].id == daftarObat[i].obat.id)
            {
                sudahAda = true;
                break;
            }
        }
        if (!sudahAda)
        {
            semuaObatSudahAda = false;
            Obat *obatLengkap = NULL;
            for (int k = 0; k < mapObat->capacity; k++)
            {
                if (mapObat->data[k].occupied && mapObat->data[k].value->id == daftarObat[i].obat.id)
                {
                    obatLengkap = mapObat->data[k].value;
                    break;
                }
            }
            if (obatLengkap != NULL)
            {
                insertLastObat(&real_pasien->inventoryObat, *obatLengkap);
                strcpy(daftarNamaObat[obatDiberikan], obatLengkap->nama);
                obatDiberikan++;
            }
        }
    }
    if (semuaObatSudahAda)
    {
        printf("Semua obat sudah ada di inventory pasien.\n");
    }
    else if (obatDiberikan > 0)
    {
        printf("Obat yang diberikan:\n");
        for (int i = 0; i < obatDiberikan; i++)
        {
            printf("%d. %s\n", i + 1, daftarNamaObat[i]);
        }
    }
}
