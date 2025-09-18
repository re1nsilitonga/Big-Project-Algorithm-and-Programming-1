#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diagnosis.h"
#include "auth.h"
#include "daftarcheckup.h"

// Fungsi untuk membandingkan dua string
int stringEquals(const char *a, const char *b)
{
    int i = 0;
    for (i = 0; a[i] != '\0' || b[i] != '\0'; i++)
    {
        if (a[i] != b[i])
        {
            return 0;
        }
    }
    return 1;
}

// Fungsi untuk meng-copy string dari src ke dest
void copyString(char *dest, const char *src)
{
    int i = 0;
    for (i = 0; src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}

// Fungsi untuk melakukan parsing string menjadi float
float parse_float(char *s)
{
    float res = 0.0f;
    float frac_part = 0.1f;
    int sign = 1;
    int i = 0;
    boolean decimal_found = false;

    if (s == NULL)
    {
        return 0.0f;
    }

    if (s[0] == '-')
    {
        sign = -1;
        i = 1;
    }
    else if (s[0] == '+')
    {
        i = 1;
    }

    for (; s[i] != '\0'; i++)
    {
        if (s[i] == '.')
        {
            decimal_found = true;
            continue;
        }
        if (s[i] >= '0' && s[i] <= '9')
        {
            if (!decimal_found)
            {
                res = res * 10.0f + (float)(s[i] - '0');
            }
            else
            {
                res = res + (float)(s[i] - '0') * frac_part;
                frac_part *= 0.1f;
            }
        }
        else
        {
            break;
        }
    }
    return res * sign;
}

// Fungsi untuk melakukan parsing string menjadi integer
int parse_int(char *s)
{
    int res = 0;
    int sign = 1;
    int i = 0;

    if (s == NULL)
    {
        return 0;
    }

    if (s[0] == '-')
    {
        sign = -1;
        i = 1;
    }
    else if (s[0] == '+')
    {
        i = 1;
    }

    for (; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            res = res * 10 + (s[i] - '0');
        }
        else
        {
            break;
        }
    }
    return res * sign;
}

// Fungsi untuk mengecek apakah pasien sudah memiliki diagnosis
boolean isDiagnosis(Akun *pasien)
{
    if (pasien == NULL)
        return false;

    // Diagnosis valid jika RiwayatPenyakit tidak kosong dan bukan "Tidak ada diagnosis yang cocok"
    return strlen(pasien->RiwayatPenyakit) > 0 &&
           strcmp(pasien->RiwayatPenyakit, "Tidak ada diagnosis yang cocok") != 0;
}

// Fungsi untuk mendiagnosis pasien
void diagnosis(dataAkun *da, dataPenyakit *dp, MapAkun *akunMap, Akun *CurrentUser, Denah *hospital, DoctorQueueMap *doctorQueues)
{
    // Validasi apakah current user adalah dokter
    if (!stringEquals(CurrentUser->Role, "dokter"))
    {
        printf("Akses ditolak! Fitur ini hanya untuk dokter.\n");
        return;
    }

    // Mencari ruangan dokter berdasarkan ID dokter yang sedang login
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

    // Jika tidak dokter tidak ditemukan di ruangan manapun atau tidak ada pasien di ruangan maka tampilkan pesan
    if (ruang_dokter == NULL || ruang_dokter->jumlahPasien == 0)
    {
        printf("Tidak ada pasien di ruangan Anda.\n");
        return;
    }

    // Ambil pasien pertama di ruangan
    Akun *pasienToDiagnose = &(ruang_dokter->pasien[0]);

    char capPasienUsername[50];
    strcpy(capPasienUsername, pasienToDiagnose->Username);
    capitalizeCommand(capPasienUsername);

    // Validasi apakah pasien sudah pernah didiagnosis
    if (isDiagnosis(pasienToDiagnose))
    {
        printf("Pasien %s sudah pernah didiagnosis.\n", capPasienUsername);
        return;
    }

    if (strcmp(pasienToDiagnose->RiwayatPenyakit, "Tidak ada diagnosis yang cocok") == 0)
    {
        printf("Pasien sudah dalam keadaan sehat!\n");
        return;
    }

    printf("Mendiagnosa pasien: %s (ID: %d)\n", capPasienUsername, pasienToDiagnose->Id);
    printf("Data Pasien:\n");
    printf("  Suhu Tubuh: %.1f C\n", pasienToDiagnose->SuhuTubuh);
    printf("  Tekanan Darah: %d/%d mmHg\n", pasienToDiagnose->TekananDarahSistolik, pasienToDiagnose->TekananDarahDiastolik);
    printf("  Detak Jantung: %d bpm\n", pasienToDiagnose->DetakJantung);
    printf("  Saturasi Oksigen: %.1f%%\n", pasienToDiagnose->SaturasiOksigen);
    printf("  Kadar Gula Darah: %d mg/dL\n", pasienToDiagnose->KadarGulaDarah);
    printf("  Berat Badan: %.1f kg\n", pasienToDiagnose->BeratBadan);
    printf("  Tinggi Badan: %d cm\n", pasienToDiagnose->TinggiBadan);
    printf("  Kadar Kolesterol: %d mg/dL\n", pasienToDiagnose->KadarKolesterol);
    printf("  Trombosit: %d x10^3/uL\n", pasienToDiagnose->Trombosit);

    boolean found_diagnosis = false;

    // Mendiagnosis pasien berdasarkan data penyakit yang ada
    for (int i = 0; i < dp->jumlah; i++)
    {
        Penyakit *p = &dp->data[i];

        if (pasienToDiagnose->SuhuTubuh >= p->SuhuTubuhMin && pasienToDiagnose->SuhuTubuh <= p->SuhuTubuhMax &&
            pasienToDiagnose->TekananDarahSistolik >= p->TekananDarahSistolikMin && pasienToDiagnose->TekananDarahSistolik <= p->TekananDarahSistolikMax &&
            pasienToDiagnose->TekananDarahDiastolik >= p->TekananDarahDiastolikMin && pasienToDiagnose->TekananDarahDiastolik <= p->TekananDarahDiastolikMax &&
            pasienToDiagnose->DetakJantung >= p->DetakJantungMin && pasienToDiagnose->DetakJantung <= p->DetakJantungMax &&
            pasienToDiagnose->SaturasiOksigen >= p->SaturasiOksigenMin && pasienToDiagnose->SaturasiOksigen <= p->SaturasiOksigenMax &&
            pasienToDiagnose->KadarGulaDarah >= p->KadarGulaDarahMin && pasienToDiagnose->KadarGulaDarah <= p->KadarGulaDarahMax &&
            pasienToDiagnose->BeratBadan >= p->BeratBadanMin && pasienToDiagnose->BeratBadan <= p->BeratBadanMax &&
            pasienToDiagnose->TinggiBadan >= p->TinggiBadanMin && pasienToDiagnose->TinggiBadan <= p->TinggiBadanMax &&
            pasienToDiagnose->KadarKolesterol >= p->KadarKolesterolMin && pasienToDiagnose->KadarKolesterol <= p->KadarKolesterolMax &&
            pasienToDiagnose->Trombosit >= p->TrombositMin && pasienToDiagnose->Trombosit <= p->TrombositMax)
        {
            copyString(pasienToDiagnose->RiwayatPenyakit, p->NamaPenyakit);
            for (int i = 0; i < da->jumlah; i++)
            {
                if (da->data[i].Id == pasienToDiagnose->Id)
                {
                    strcpy(da->data[i].RiwayatPenyakit, p->NamaPenyakit);
                }
            }

            char capPenyakit[100];
            strcpy(capPenyakit, p->NamaPenyakit);
            capitalizeCommand(capPenyakit);
            printf("Pasien %s terdiagnosa penyakit %s.\n", capPasienUsername, capPenyakit);
            found_diagnosis = true;
            break;
        }
        for (int i = 0 ; i < da->jumlah ; i++){
            if (da->data[i].Id == pasienToDiagnose->Id) {
                strcpy(da->data[i].RiwayatPenyakit, "Sehat");
            }
        }
    }

    // Jika tidak ditemukan diagnosis yang cocok maka berikan pesan
    if (!found_diagnosis)
    {
        strcpy(pasienToDiagnose->RiwayatPenyakit, "Sehat");
        printf("Pasien dinyatakan sehat!\n");
    }
}