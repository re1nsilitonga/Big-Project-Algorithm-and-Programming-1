#include <stdio.h>
#include <string.h>
#include "listdin.h"

void createTablePenyakit(dataPenyakit *dp, int kapasitas)
{
    dp->data = (Penyakit *)malloc(kapasitas * sizeof(Penyakit));
    dp->jumlah = 0;
    dp->kapasitas = kapasitas;
}

void dealocateTablePenyakit(dataPenyakit *dp)
{
    free(dp->data);
    dp->jumlah = 0;
    dp->kapasitas = 0;
}

void insertLastPenyakit(dataPenyakit *dp, Penyakit penyakit)
{
    if (dp->jumlah == dp->kapasitas)
    {
        dp->kapasitas *= 2;
        dp->data = realloc(dp->data, dp->kapasitas * sizeof(Penyakit));
        if (dp->data == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    dp->data[dp->jumlah] = penyakit;
    dp->jumlah++;
}

// Fungsi bantu untuk qsort
// Perhatikan: compare_func harus mengambil dua pointer ke const void.
// Kita akan menggunakan pointer ke Akun untuk perbandingan.
static int compare_for_qsort(const void *a, const void *b, boolean asc)
{
    if (asc)
    {
        return ((Akun *)a)->Id - ((Akun *)b)->Id; // Ascending
    }
    else
    {
        return ((Akun *)b)->Id - ((Akun *)a)->Id; // Descending
    }
}

static int compare_asc(const void *a, const void *b)
{
    return ((Akun *)a)->Id - ((Akun *)b)->Id;
}

static int compare_desc(const void *a, const void *b)
{
    return ((Akun *)b)->Id - ((Akun *)a)->Id;
}

void sortID(dataAkun *da, boolean asc)
{
    if (da != NULL && da->data != NULL && da->jumlah > 1)
    {

        if (asc)
        {
            qsort(da->data, da->jumlah, sizeof(Akun), compare_asc);
        }
        else
        {
            qsort(da->data, da->jumlah, sizeof(Akun), compare_desc);
        }
    }
}

static int compare_nama_asc(const void *a, const void *b)
{
    return strcmp(((Akun *)a)->Username, ((Akun *)b)->Username);
}

static int compare_nama_desc(const void *a, const void *b)
{
    return strcmp(((Akun *)b)->Username, ((Akun *)a)->Username);
}

void sortNama(dataAkun *da, boolean asc)
{
    if (da != NULL && da->data != NULL && da->jumlah > 1)
    {
        if (asc)
        {
            qsort(da->data, da->jumlah, sizeof(Akun), compare_nama_asc);
        }
        else
        {
            qsort(da->data, da->jumlah, sizeof(Akun), compare_nama_desc);
        }
    }
}

void createTableObat(dataObat *do_, int kapasitas)
{
    do_->data = (Obat *)malloc(kapasitas * sizeof(Obat));
    do_->jumlah = 0;
    do_->kapasitas = kapasitas;
}

void dealocateTableObat(dataObat *do_)
{
    free(do_->data);
    do_->jumlah = 0;
    do_->kapasitas = 0;
}

void insertLastObat(dataObat *do_, Obat obat)
{
    if (do_->jumlah == do_->kapasitas)
    {
        do_->kapasitas *= 2;
        do_->data = realloc(do_->data, do_->kapasitas * sizeof(Obat));
        if (do_->data == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    do_->data[do_->jumlah] = obat;
    do_->jumlah++;
}

void DeleteObatAt(dataObat *do_, int idx)
{
    if (idx < 0 || idx >= do_->jumlah)
    {
        printf("Index di luar batas!\n");
        return;
    }

    for (int i = idx; i < do_->jumlah - 1; i++)
    {
        do_->data[i] = do_->data[i + 1];
    }

    do_->jumlah--;
}

void createTableObatPenyakit(dataObatPenyakit *dop, int kapasitas)
{
    dop->data = (ObatPenyakit *)malloc(kapasitas * sizeof(ObatPenyakit));
    dop->jumlah = 0;
    dop->kapasitas = kapasitas;
}

void dealocateTableObatPenyakit(dataObatPenyakit *dop)
{
    free(dop->data);
    dop->jumlah = 0;
    dop->kapasitas = 0;
}

void insertLastObatPenyakit(dataObatPenyakit *dop, ObatPenyakit op)
{
    if (dop->jumlah == dop->kapasitas)
    {
        dop->kapasitas *= 2;
        dop->data = realloc(dop->data, dop->kapasitas * sizeof(ObatPenyakit));
        if (dop->data == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    dop->data[dop->jumlah] = op;
    dop->jumlah++;
}

void createTableAkun(dataAkun *da, int kapasitas)
{
    da->data = (Akun *)malloc(kapasitas * sizeof(Akun));
    da->jumlah = 0;
    da->kapasitas = kapasitas;
}

void dealocateTableAkun(dataAkun *da)
{
    free(da->data);
    da->jumlah = 0;
    da->kapasitas = 0;
}

void insertLastAkun(dataAkun *da, Akun akun)
{
    if (da->jumlah == da->kapasitas)
    {
        da->kapasitas *= 2;
        da->data = realloc(da->data, da->kapasitas * sizeof(Akun));
        if (da->data == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    da->data[da->jumlah] = akun;
    da->jumlah++;
}

void createListAkun(Akun **akun, int kapasitas)
{
    *akun = (Akun *)malloc(kapasitas * sizeof(Akun));
    if (*akun == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
}

void dealocateListAkun(Akun **akun)
{
    free(*akun);
    *akun = NULL;
}

void insertLastListAkun(Akun **akun, Akun akunBaru, int *jumlah, int *kapasitas)
{
    if (*jumlah == *kapasitas)
    {
        *kapasitas *= 2;
        *akun = realloc(*akun, *kapasitas * sizeof(Akun));
        if (*akun == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
    (*akun)[*jumlah] = akunBaru;
    (*jumlah)++;
}

void createTablePerutPasien(DataPerutPasien *DPP, int kapasitas)
{
    DPP->data = (PerutPasien *)malloc(kapasitas * sizeof(PerutPasien));
    DPP->jumlah = 0;
    DPP->kapasitas = kapasitas;
}

void dealocateTablePerutPasien(DataPerutPasien *DPP)
{
    free(DPP->data);
    DPP->jumlah = 0;
    DPP->kapasitas = 0;
}

void insertLastPerutPasien(DataPerutPasien *DPP, int idPasien, Obat obatPertama)
{
    if (DPP->jumlah == DPP->kapasitas)
    {
        int newCap = DPP->kapasitas > 0 ? DPP->kapasitas * 2 : 8;
        PerutPasien *newData = realloc(DPP->data, newCap * sizeof(PerutPasien));
        if (newData == NULL)
        {
            printf("Gagal alokasi memori untuk data perut pasien.\n");
            return;
        }
        DPP->data = newData;
        DPP->kapasitas = newCap;
    }
    DPP->data[DPP->jumlah].IdPasien = idPasien;
    CreateEmpty(&(DPP->data[DPP->jumlah].Perut));
    Push(&(DPP->data[DPP->jumlah].Perut), obatPertama);
    DPP->jumlah++;
}
