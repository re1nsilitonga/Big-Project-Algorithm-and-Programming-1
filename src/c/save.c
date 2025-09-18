// save.c
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "user.h"
#include "denah.h"
#include "queue.h"
#include "save.h"
#include "dataperut.h"

void Save(const char *sourceFolder, const char *folderName, dataAkun akunData, Denah denah, DataPerutPasien DPP)
{
    struct stat st = {0};
    char folderPath[256];

    // Karena program dijalankan dari dalam src/, folder simpanan langsung folderName
    snprintf(folderPath, sizeof(folderPath), "%s", folderName);

    // Cek apakah folder sudah ada
    if (stat(folderPath, &st) == -1)
    {
        printf("# Folder %s belum ada\n", folderName);
        printf("Saving…\n");
        printf("Membuat folder %s...\n", folderPath);

#ifdef _WIN32
        if (mkdir(folderPath) == -1)
        {
            perror("Gagal membuat folder");
            return;
        }
#else
        if (mkdir(folderPath, 0700) == -1)
        {
            perror("Gagal membuat folder");
            return;
        }
#endif
    }
    SaveUser(folderName, akunData);
    SaveKonfig(folderName, denah, akunData, DPP);
    CopyStaticFiles(sourceFolder, folderName);
}

void SaveUser(const char *folderName, dataAkun akunData)
{
    // Path file CSV user.csv
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/user.csv", folderName);

    FILE *f = fopen(filePath, "w");
    if (!f)
    {
        perror("Gagal membuka file user.csv untuk ditulis");
        return;
    }

    // Tulis header
    fprintf(f, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;"
               "tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;"
               "berat_badan;tinggi_badan;kadar_kolesterol;trombosit\n");

    int count = 0;
    for (int i = 0; i < akunData.jumlah; i++)
    {
        Akun a = akunData.data[i];
        if (a.Id == 0)
            continue;
        if (count > 0)
            fprintf(f, "\n");
        fprintf(f, "%d;%s;%s;%s;", a.Id, a.Username, a.Password, a.Role);

        if (strlen(a.RiwayatPenyakit) > 0 &&
            strcmp(a.RiwayatPenyakit, "Tidak ada diagnosis yang cocok") != 0 &&
            strcmp(a.RiwayatPenyakit, "Sehat") != 0)
            fprintf(f, "%s;", a.RiwayatPenyakit);
        else
            fprintf(f, ";");
        {
            /* code */
        }

        if (a.SuhuTubuh >= 0)
            fprintf(f, "%.1f;", a.SuhuTubuh);
        else
            fprintf(f, ";");
        if (a.TekananDarahSistolik >= 0)
            fprintf(f, "%d;", a.TekananDarahSistolik);
        else
            fprintf(f, ";");
        if (a.TekananDarahDiastolik >= 0)
            fprintf(f, "%d;", a.TekananDarahDiastolik);
        else
            fprintf(f, ";");
        if (a.DetakJantung >= 0)
            fprintf(f, "%d;", a.DetakJantung);
        else
            fprintf(f, ";");
        if (a.SaturasiOksigen >= 0)
            fprintf(f, "%.1f;", a.SaturasiOksigen);
        else
            fprintf(f, ";");
        if (a.KadarGulaDarah >= 0)
            fprintf(f, "%d;", a.KadarGulaDarah);
        else
            fprintf(f, ";");
        if (a.BeratBadan >= 0)
            fprintf(f, "%.1f;", a.BeratBadan);
        else
            fprintf(f, ";");
        if (a.TinggiBadan >= 0)
            fprintf(f, "%d;", a.TinggiBadan);
        else
            fprintf(f, ";");
        if (a.KadarKolesterol >= 0)
            fprintf(f, "%d;", a.KadarKolesterol);
        else
            fprintf(f, ";");
        if (a.Trombosit >= 0)
            fprintf(f, "%d", a.Trombosit);
        else
            fprintf(f, ";");
        count++;
    }

    fclose(f);

    printf("Berhasil menyimpan data di folder %s!\n", folderName);
}

void SaveKonfig(const char *folderName, Denah denah, dataAkun akunData, DataPerutPasien dataPerut)
{
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/config.txt", folderName);

    // Gunakan buffer string untuk menampung semua baris, lalu tulis ke file tanpa newline di akhir
    char *lines[4096];
    int lineCount = 0;
    char linebuf[1024];

    // Ukuran denah
    snprintf(linebuf, sizeof(linebuf), "%d %d", denah.panjang, denah.lebar);
    lines[lineCount++] = strdup(linebuf);

    // Kapasitas ruangan dan antrian
    snprintf(linebuf, sizeof(linebuf), "%d %d", denah.kapasitasRuang, ((denah.panjang == 0 && denah.lebar == 0) ? 0 : denah.grid[0][0].antrian.kapasitas));
    lines[lineCount++] = strdup(linebuf);

    for (int i = 0; i < denah.panjang; i++)
    {
        for (int j = 0; j < denah.lebar; j++)
        {
            Ruangan r = denah.grid[i][j];

            if (r.dokter == NULL || r.dokter->Id == 0)
            {
                snprintf(linebuf, sizeof(linebuf), "0");
                lines[lineCount++] = strdup(linebuf);
                continue;
            }

            int pos = 0;
            pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, "%d", r.dokter->Id);

            for (int k = 0; k < r.jumlahPasien; k++)
            {
                pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, " %d", r.pasien[k].Id);
            }

            if (r.antrian.length == 0 && r.jumlahPasien == 0)
            {
                pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, " 0");
            }
            else if (r.antrian.length > 0)
            {
                int idx = r.antrian.head;
                for (int k = 0; k < r.antrian.length; k++)
                {
                    pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, " %d", r.antrian.pasien[idx]->Id);
                    idx = (idx + 1) % r.antrian.kapasitas;
                }
            }
            lines[lineCount++] = strdup(linebuf);
        }
    }

    // Inventory pasien
    int jumlah_pasien_inventory = 0;
    for (int i = 0; i < akunData.jumlah; i++)
    {
        Akun *pasien = &akunData.data[i];
        if (pasien->inventoryObat.jumlah > 0)
        {
            jumlah_pasien_inventory++;
        }
    }
    snprintf(linebuf, sizeof(linebuf), "%d", jumlah_pasien_inventory);
    lines[lineCount++] = strdup(linebuf);

    for (int i = 0; i < akunData.jumlah; i++)
    {
        Akun *pasien = &akunData.data[i];
        if (pasien->inventoryObat.jumlah > 0)
        {
            int pos = 0;
            pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, "%d", pasien->Id);
            for (int j = 0; j < pasien->inventoryObat.jumlah; j++)
            {
                pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, " %d", pasien->inventoryObat.data[j].id);
            }
            lines[lineCount++] = strdup(linebuf);
        }
    }

    // Hitung jumlah pasien dengan perut tidak kosong dan id valid
    int jumlah_perut_terisi = 0;
    for (int i = 0; i < dataPerut.jumlah; i++)
    {
        if (IsEmpty(dataPerut.data[i].Perut))
            continue;
        int found = 0;
        for (int j = 0; j < akunData.jumlah; j++)
        {
            if (akunData.data[j].Id == dataPerut.data[i].IdPasien && strcmp(akunData.data[j].Role, "pasien") == 0)
            {
                found = 1;
                break;
            }
        }
        if (found)
            jumlah_perut_terisi++;
    }
    snprintf(linebuf, sizeof(linebuf), "%d", jumlah_perut_terisi);
    lines[lineCount++] = strdup(linebuf);

    for (int i = 0; i < dataPerut.jumlah; i++)
    {
        PerutPasien *entry = &dataPerut.data[i];
        if (IsEmpty(entry->Perut))
            continue;
        int found = 0;
        for (int j = 0; j < akunData.jumlah; j++)
        {
            if (akunData.data[j].Id == entry->IdPasien && strcmp(akunData.data[j].Role, "pasien") == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
            continue;
        int pos = 0;
        pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, "%d", entry->IdPasien);

        // Ambil isi stack ke array, urutan dari top ke bottom
        Stack tempStack;
        CreateEmpty(&tempStack);
        Obat tempArr[100];
        int count = 0;
        while (!IsEmpty(entry->Perut))
        {
            Obat topObat;
            Pop(&entry->Perut, &topObat);
            tempArr[count++] = topObat;
            Push(&tempStack, topObat);
        }
        // Kembalikan stack ke semula
        for (int j = count - 1; j >= 0; j--)
        {
            Push(&entry->Perut, tempArr[j]);
        }

        // Format: <idPasien> <Top> <sisanya>
        if (count > 0)
        {
            pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, " %d", tempArr[0].id);
            for (int j = 1; j < count; j++)
            {
                pos += snprintf(linebuf + pos, sizeof(linebuf) - pos, " %d", tempArr[j].id);
            }
        }
        lines[lineCount++] = strdup(linebuf);
    }

    // Tulis ke file tanpa newline di akhir
    FILE *f = fopen(filePath, "w");
    if (!f)
    {
        perror("Gagal membuka config.txt");
        for (int i = 0; i < lineCount; i++)
            free(lines[i]);
        return;
    }
    for (int i = 0; i < lineCount; i++)
    {
        fputs(lines[i], f);
        if (i < lineCount - 1)
            fputc('\n', f);
        free(lines[i]);
    }
    fclose(f);
}

void CopyFile(const char *srcPath, const char *destPath)
{
    FILE *src = fopen(srcPath, "rb");
    if (!src)
    {
        perror("Gagal membuka file sumber");
        return;
    }

    FILE *dst = fopen(destPath, "wb");
    if (!dst)
    {
        perror("Gagal membuka file tujuan");
        fclose(src);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        fwrite(buffer, 1, bytes, dst);
    }

    fclose(src);
    fclose(dst);
}

void CopyStaticFiles(const char *sourceFolder, const char *targetFolder)
{
    char src[256], dst[256];

    snprintf(src, sizeof(src), "%s/obat.csv", sourceFolder);
    snprintf(dst, sizeof(dst), "%s/obat.csv", targetFolder);
    CopyFile(src, dst);

    snprintf(src, sizeof(src), "%s/penyakit.csv", sourceFolder);
    snprintf(dst, sizeof(dst), "%s/penyakit.csv", targetFolder);
    CopyFile(src, dst);

    snprintf(src, sizeof(src), "%s/obat_penyakit.csv", sourceFolder);
    snprintf(dst, sizeof(dst), "%s/obat_penyakit.csv", targetFolder);
    CopyFile(src, dst);
}