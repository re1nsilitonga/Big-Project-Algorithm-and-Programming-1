#include "auth.h"
#include "user.h"
#include "listdin.h"
#include "set.h"
#include "map.h"
#include "load.h"
#include "denah.h"
#include "queue.h"
#include "minum.h"
#include "exit.h"
#include "save.h"
#include "pasien.h"
#include "cariuser.h"
#include "diagnosis.h"
#include "daftarcheckup.h"
#include "ngobatin.h"
#include "diagnosis.h"
#include "pulangdok.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

dataAkun tabelAkun;

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <nama_folder>\n", argv[0]);
        return 1;
    }

    const char *folder = argv[1];

    // Alokasi memori untuk tabel data akun, tabel penyakit, tabel obat, inisialisasi map, dan denah
    createTableAkun(&tabelAkun, 1000);

    dataPenyakit tabelPenyakit;
    createTablePenyakit(&tabelPenyakit, 1000);

    dataObat tabelObat;
    createTableObat(&tabelObat, 1000);

    dataObatPenyakit tabelObatPenyakit;
    createTableObatPenyakit(&tabelObatPenyakit, 1000);

    DataPerutPasien DPP;
    createTablePerutPasien(&DPP, 1000);

    MapAkun akunMap;
    createMapAkun(&akunMap);
    MapPenyakit penyakitMap;
    createMapPenyakit(&penyakitMap);
    MapObat obatMap;
    createMapObat(&obatMap);
    MapObatPenyakit obatPenyakitMap;
    createMapObatPenyakit(&obatPenyakitMap);
    DoctorQueueMap dokterQueueMap;
    createDoctorQueueMap(&dokterQueueMap);
    MapLinkedListQueue linkedListQueueMap;
    createMapLinkedListQueue(&linkedListQueueMap);
    Denah hospital;

    if (!tabelAkun.data)
    {
        perror("Gagal alokasi memori");
        return 1;
    }
    if (!tabelPenyakit.data)
    {
        perror("Gagal alokasi memori");
        free(tabelAkun.data);
        return 1;
    }
    if (!tabelObat.data)
    {
        perror("Gagal alokasi memori");
        free(tabelAkun.data);
        free(tabelPenyakit.data);
        return 1;
    }
    if (!tabelObatPenyakit.data)
    {
        perror("Gagal alokasi memori");
        free(tabelAkun.data);
        free(tabelPenyakit.data);
        free(tabelObat.data);
        return 1;
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // ASCII Art
    const char *ascii_art[] = {
        "██████╗ ██╗   ██╗███╗   ███╗ █████╗ ██╗  ██╗    ███████╗ █████╗ ██╗  ██╗██╗████████╗    ███╗   ██╗██╗███╗   ███╗ ██████╗ ███╗   ██╗███████╗",
        "██╔══██╗██║   ██║████╗ ████║██╔══██╗██║  ██║    ██╔════╝██╔══██╗██║ ██╔╝██║╚══██╔══╝    ████╗  ██║██║████╗ ████║██╔═══██╗████╗  ██║██╔════╝",
        "██████╔╝██║   ██║██╔████╔██║███████║███████║    ███████╗███████║█████╔╝ ██║   ██║       ██╔██╗ ██║██║██╔████╔██║██║   ██║██╔██╗ ██║███████╗",
        "██╔══██╗██║   ██║██║╚██╔╝██║██╔══██║██╔══██║    ╚════██║██╔══██║██╔═██╗ ██║   ██║       ██║╚██╗██║██║██║╚██╔╝██║██║   ██║██║╚██╗██║╚════██║",
        "██║  ██║╚██████╔╝██║ ╚═╝ ██║██║  ██║██║  ██║    ███████║██║  ██║██║  ██╗██║   ██║       ██║ ╚████║██║██║ ╚═╝ ██║╚██████╔╝██║ ╚████║███████║",
        "╚═╝  ╚═╝ ╚═════╝ ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝    ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝   ╚═╝       ╚═╝  ╚═══╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝"};

    int color_gradient[] = {21, 27, 33, 39, 45, 51, 50, 49, 48, 82, 118, 154, 190, 226};
    int num_colors = sizeof(color_gradient) / sizeof(color_gradient[0]);

    for (int i = 0; i < 6; i++)
    {
        const char *line = ascii_art[i];
        int len = strlen(line);
        for (int j = 0; j < len; j++)
        {
            unsigned char c = line[j];

            if ((unsigned char)c >= 0xC0)
            {
                int color = color_gradient[(j * num_colors) / len];
                printf("\033[38;5;%dm", color);
                while ((line[j] & 0xC0) == 0x80 || (line[j] & 0xC0) == 0xC0)
                {
                    printf("%c", line[j]);
                    j++;
                    if ((line[j] & 0xC0) != 0x80)
                        break;
                }
                printf("\033[0m");
                j--;
            }
            else
            {
                printf("%c", c);
            }
        }
        printf("\n");
    }

    // Template message sistem hospital setelah ASCII art
    printf("\n");
    printf("=====================================================================================\n");
    printf("                     Selamat Datang di Sistem Informasi Rumah Sakit                 \n");
    printf("=====================================================================================\n");
    printf(" Silakan masukkan perintah berikut sesuai kebutuhan:\n");
    printf(" -----------------------------------------------------------------------------------\n");
    printf(" - Login                                 : Untuk masuk ke akun Anda\n");
    printf(" - Logout                                : Untuk keluar dari akun Anda\n");
    printf(" - Register                              : Untuk membuat akun baru\n");
    printf(" - Help                                  : Menampilkan bantuan perintah\n");
    printf(" - Lupa_password                         : Untuk reset password akun\n");
    printf(" - Lihat_denah                           : Melihat denah rumah sakit\n");
    printf(" - Lihat_ruangan <kode>                  : Melihat detail ruangan berdasarkan kode\n");
    printf(" - Ubah_denah <rows> <cols>              : Mengubah ukuran denah rumah sakit\n");
    printf(" - Pindah_dokter <kodeAsal> <kodeTujuan> : Memindahkan dokter antar ruangan\n");
    printf(" - Tambah_dokter                         : Menambahkan dokter baru\n");
    printf(" - Assign_dokter                         : Menugaskan dokter ke ruangan\n");
    printf(" - Lihat_semua_antrian                   : Melihat antrian pasien\n");
    printf(" - Antrian                               : Melihat status antrian Anda\n");
    printf(" - Cancel_antrian                        : Membatalkan antrian check-up\n");
    printf(" - Skip_antrian                          : Maju ke depan antrian check-up\n");
    printf(" - Lihat_user                            : Melihat daftar akun user\n");
    printf(" - Cari_user                             : Mencari akun user berdasarkan ID\n");
    printf(" - Daftar_checkup                        : Melakukan pendaftaran check-up\n");
    printf(" - Diagnosis                             : Melakukan diagnosis pasien\n");
    printf(" - Ngobatin                              : Melakukan proses pengobatan pasien\n");
    printf(" - Minum_obat                            : Meminum obat di inventory\n");
    printf(" - Penawar                               : Mengeluarkan kembali obat di perut ke inventory\n");
    printf(" - Pulang_dok                            : Proses pulang pasien dari rumah sakit\n");
    printf(" - Save                                  : Menyimpan data ke folder\n");
    printf(" - Exit                                  : Keluar dari aplikasi\n");
    printf("=====================================================================================\n\n");

    // Load data akun, penyakit, obat, obatpenyakit lalu masukkan ke map dan denah
    if (!loadData(&tabelAkun, folder, &akunMap, &hospital, &tabelPenyakit, &penyakitMap, &tabelObat, &obatMap, &tabelObatPenyakit, &obatPenyakitMap, &DPP, &dokterQueueMap))
    {
        fprintf(stderr, "Gagal memuat data dari folder %s\n", folder);
        free(tabelAkun.data);
        free(tabelPenyakit.data);
        free(tabelObat.data);
        free(tabelObatPenyakit.data);
        return 1;
    }

    boolean isLogin = false;
    Akun akun;
    initAkun(&akun);

    // Menu utama
    for (;;)
    {
        char input[100];
        printf(">>> ");
        if (!fgets(input, sizeof(input), stdin))
            break;
        stripNewline(input);

        // Ubah input jadi Capitalize di awal kata, sisanya kecil
        capitalizeCommand(input);

        if (strcmp(input, "Login") == 0)
        {
            login(&tabelAkun, &akun, &isLogin);
        }
        else if (strcmp(input, "Logout") == 0)
        {
            logout(&akun, &isLogin);
        }
        else if (strcmp(input, "Register") == 0)
        {
            regist(&tabelAkun, &akunMap, isLogin);
        }
        else if (strcmp(input, "Help") == 0)
        {
            help(&akun, &isLogin);
        }
        else if (strcmp(input, "Lupa_password") == 0)
        {
            forgotPassword(&tabelAkun, &akun, &isLogin);
        }
        else if (strcmp(input, "Lihat_denah") == 0)
        {
            LIHAT_DENAH(&hospital, isLogin);
        }
        else if (strncmp(input, "Lihat_ruangan", 13) == 0)
        {
            if (!isLogin)
            {
                printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
                continue;
            }
            int i = 13;
            while (input[i] == ' ')
                i++; // skip spasi

            char kode[10];
            int j = 0;
            while (input[i] != '\0' && input[i] != '\n' && input[i] != ' ' && j < 9)
            {
                capitalizeCommand(&input[i]);
                kode[j++] = input[i++];
            }
            kode[j] = '\0'; // null-terminate

            if (j > 0)
            {
                LIHAT_RUANGAN(&hospital, kode, isLogin);
            }
            else
            {
                printf("Kode ruangan tidak ditemukan!\n");
            }
        }
        else if (strncmp(input, "Ubah_denah", 10) == 0)
        {
            int i = 10;
            // skip spasi
            while (input[i] == ' ')
                i++;

            // ambil angka pertama (newRows)
            int newRows = 0;
            while (input[i] >= '0' && input[i] <= '9')
            {
                newRows = newRows * 10 + (input[i] - '0');
                i++;
            }

            // skip spasi
            while (input[i] == ' ')
                i++;

            // ambil angka kedua (newCols)
            int newCols = 0;
            while (input[i] >= '0' && input[i] <= '9')
            {
                newCols = newCols * 10 + (input[i] - '0');
                i++;
            }

            if (newRows > 0 && newCols > 0)
            {
                UBAH_DENAH(&hospital, newRows, newCols, isLogin, &akun);
            }
            else
            {
                printf("Format perintah salah. Contoh: Ubah_denah 3 4\n");
            }
        }
        else if (strncmp(input, "Pindah_dokter", 13) == 0)
        {
            if (!isLogin)
            {
                printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
                continue;
            }
            int i = 13;
            // skip spasi
            while (input[i] == ' ')
                i++;

            // ambil kodeAsal
            char kodeAsal[16];
            int j = 0;
            while (input[i] != ' ' && input[i] != '\0' && input[i] != '\n' && j < 15)
            {
                capitalizeCommand(&input[i]);
                kodeAsal[j++] = input[i++];
            }
            kodeAsal[j] = '\0';

            // skip spasi
            while (input[i] == ' ')
                i++;

            // ambil kodeTujuan
            char kodeTujuan[16];
            j = 0;
            while (input[i] != ' ' && input[i] != '\0' && input[i] != '\n' && j < 15)
            {
                capitalizeCommand(&input[i]);
                kodeTujuan[j++] = input[i++];
            }
            kodeTujuan[j] = '\0';

            if (kodeAsal[0] != '\0' && kodeTujuan[0] != '\0')
            {
                PINDAH_DOKTER(&hospital, kodeAsal, kodeTujuan, isLogin, &akun);
            }
            else
            {
                printf("Format perintah salah. Contoh: Pindah_dokter A2 C4\n");
            }
        }
        else if (strcmp(input, "Tambah_dokter") == 0)
        {
            TambahDokter(&tabelAkun, &akunMap, &akun, isLogin);
        }
        else if (strcmp(input, "Assign_dokter") == 0)
        {
            AssignDokter(&hospital, &tabelAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Cari_user") == 0)
        {
            dataAkun tempDataAkun;
            createTableAkun(&tempDataAkun, tabelAkun.jumlah);
            for (int i = 0; i < tabelAkun.jumlah; i++)
            {
                insertLastAkun(&tempDataAkun, tabelAkun.data[i]);
            }
            sortID(&tempDataAkun, true);
            cariUser(&tempDataAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Cari_pasien") == 0)
        {
            cariPasien(&tabelAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Cari_dokter") == 0)
        {
            cariDokter(&tabelAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Lihat_semua_antrian") == 0)
        {
            LIHAT_ANTRIAN(&hospital, &akun, isLogin);
        }
        else if (strcmp(input, "Antrian") == 0)
        {
            antrianSaya(&hospital, &akun, isLogin);
        }
        else if (strcmp(input, "Skip_antrian") == 0)
        {
            skipAntrian(&hospital, &akun, isLogin);
        }
        else if (strcmp(input, "Cancel_antrian") == 0)
        {
            cancelAntrian(&hospital, &akun, isLogin);
        }
        else if (strcmp(input, "Lihat_antrian") == 0)
        {
            LIHAT_ANTRIAN(&hospital, &akun, isLogin);
        }
        else if (strcmp(input, "Lihat_user") == 0)
        {
            LihatUser(&tabelAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Lihat_pasien") == 0)
        {
            LihatPasien(&tabelAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Lihat_dokter") == 0)
        {
            LihatDokter(&tabelAkun, &akun, isLogin);
        }
        else if (strcmp(input, "Diagnosis") == 0)
        {
            diagnosis(&tabelAkun, &tabelPenyakit, &akunMap, &akun, &hospital, &dokterQueueMap);
        }
        else if (strcmp(input, "Ngobatin") == 0)
        {
            ngobatin(&akun, &dokterQueueMap, &obatPenyakitMap, &obatMap, &tabelPenyakit, &hospital);
        }
        else if (strcmp(input, "Pulang_dok") == 0)
        {
            PulangDok(&akun, isLogin, &hospital, &DPP, &obatPenyakitMap, &obatMap, &tabelPenyakit, &tabelAkun, &linkedListQueueMap);
        }
        else if (strcmp(input, "Minum_obat") == 0)
        {
            MinumObat(&akun, isLogin, &DPP, &tabelAkun);
        }
        else if (strcmp(input, "Daftar_checkup") == 0)
        {
            Akun *real_pasien = NULL;
            for (int i = 0; i < tabelAkun.jumlah; i++)
            {
                if (tabelAkun.data[i].Id == akun.Id)
                {
                    real_pasien = &tabelAkun.data[i];
                    break;
                }
            }
            if (real_pasien != NULL)
            {
                checkUpRegistration(real_pasien, &dokterQueueMap, &hospital);
            }
            else
            {
                printf("Data akun pasien tidak ditemukan!\n");
            }
        }
        else if (strcmp(input, "Penawar") == 0)
        {
            Penawar(&akun, isLogin, &DPP, &tabelAkun);
        }
        else if (strcmp(input, "Exit") == 0)
        {
            Exit(folder, tabelAkun, hospital, DPP);
            break;
        }
        else if (strcmp(input, "Save") == 0)
        {
            char folderName[100];
            printf("Masukkan nama folder: ");
            if (fgets(folderName, sizeof(folderName), stdin))
            {
                folderName[strcspn(folderName, "\n")] = 0;
                Save(folder, folderName, tabelAkun, hospital, DPP);
            }
        }
        else
        {
            printf("Perintah tidak dikenali. Silakan coba lagi.\n");
            printf("Masukkan perintah 'EXIT' untuk mengakhiri program.\n");
        }
    }

    // Membersihkan memori
    free(tabelAkun.data);
    for (int i = 0; i < hospital.panjang; ++i)
    {
        free(hospital.grid[i]);
    }
    free(hospital.grid);

    return 0;
}
