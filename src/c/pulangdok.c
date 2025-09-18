#include "pulangdok.h"

void PulangDok(Akun *CurrentUser, boolean isLogin, Denah *hospital, DataPerutPasien *DaPerutPasien, MapObatPenyakit *mapObatPenyakit, MapObat *mapObat, dataPenyakit *dataPenyakit, dataAkun *da, MapLinkedListQueue *mapDoctorQueue)
{
    // Validasi apakah pengguna sudah login
    if (!isLogin)
    {
        printf("Silakan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Validasi apakah pengguna adalah pasien
    if (strcmp(CurrentUser->Role, "pasien") != 0)
    {
        printf("Menu ini hanya dapat diakses oleh pasien!\n");
        return;
    }

    printf("Dokter sedang memeriksa keadaanmu...\n\n");

    if (isSehat(CurrentUser))
    {
        // Cek apakah pasien sudah ada di dataAkun
        int idxPasien = -1;
        for (int i = 0; i < da->jumlah; i++)
        {
            if (da->data[i].Id == CurrentUser->Id)
            {
                idxPasien = i;
                break;
            }
        }

        if (idxPasien == -1)
        {
            printf("Data pasien tidak ditemukan!\n");
            return;
        }

        // Cek apakah pasien sudah ada di dataPerutPasien
        int idxPerut = -1;
        for (int i = 0; i < DaPerutPasien->jumlah; i++)
        {
            if (DaPerutPasien->data[i].IdPasien == CurrentUser->Id)
            {
                idxPerut = i;
                break;
            }
        }

        printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n");
        // Reset data pada CurrentUser dan pada dataAkun utama
        copyString(CurrentUser->RiwayatPenyakit, "");
        CurrentUser->SuhuTubuh = -1;
        CurrentUser->TekananDarahSistolik = -1;
        CurrentUser->TekananDarahDiastolik = -1;
        CurrentUser->DetakJantung = -1;
        CurrentUser->SaturasiOksigen = -1;
        CurrentUser->KadarGulaDarah = -1;
        CurrentUser->BeratBadan = -1;
        CurrentUser->TinggiBadan = -1;
        CurrentUser->KadarKolesterol = -1;
        CurrentUser->Trombosit = -1;
        CurrentUser->inventoryObat.jumlah = 0;

        // Reset juga pada dataAkun utama
        da->data[idxPasien].SuhuTubuh = -1;
        da->data[idxPasien].TekananDarahSistolik = -1;
        da->data[idxPasien].TekananDarahDiastolik = -1;
        da->data[idxPasien].DetakJantung = -1;
        da->data[idxPasien].SaturasiOksigen = -1;
        da->data[idxPasien].KadarGulaDarah = -1;
        da->data[idxPasien].BeratBadan = -1;
        da->data[idxPasien].TinggiBadan = -1;
        da->data[idxPasien].KadarKolesterol = -1;
        da->data[idxPasien].Trombosit = -1;
        da->data[idxPasien].inventoryObat.jumlah = 0;
        copyString(da->data[idxPasien].RiwayatPenyakit, "");

        // Hapus pasien dari ruangan/antrian
        for (int i = 0; i < hospital->panjang; i++)
        {
            for (int j = 0; j < hospital->lebar; j++)
            {
                Ruangan *ruang = &hospital->grid[i][j];
                // Hapus dari ruangan
                for (int k = 0; k < ruang->jumlahPasien; k++)
                {
                    if (ruang->pasien[k].Id == CurrentUser->Id)
                    {
                        for (int l = k; l < ruang->jumlahPasien - 1; l++)
                        {
                            ruang->pasien[l] = ruang->pasien[l + 1];
                        }
                        ruang->jumlahPasien--;
                        break;
                    }
                }
                // Hapus dari antrian
                for (int k = 0; k < ruang->antrian.length; k++)
                {
                    if (ruang->antrian.pasien[k]->Id == CurrentUser->Id)
                    {
                        for (int l = k; l < ruang->antrian.length - 1; l++)
                        {
                            ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                        }
                        ruang->antrian.length--;
                        break;
                    }
                }
                // Setelah penghapusan, isi slot kosong dengan pasien dari antrian (FIFO)
                while (ruang->jumlahPasien < hospital->kapasitasRuang && ruang->antrian.length > 0)
                {
                    // Ambil pasien terdepan dari antrian
                    Akun *nextPasien = ruang->antrian.pasien[0];
                    // Geser antrian ke kiri
                    for (int l = 0; l < ruang->antrian.length - 1; l++)
                    {
                        ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                    }
                    ruang->antrian.length--;
                    // Masukkan ke ruangan
                    ruang->pasien[ruang->jumlahPasien++] = *nextPasien;
                }
            }
        }
        return;
    }

    // Cek diagnosis pada dataAkun utama
    if (strlen(CurrentUser->RiwayatPenyakit) == 0 ||
        strcmp(CurrentUser->RiwayatPenyakit, "Tidak ada diagnosis yang cocok") == 0 ||
        strcmp(CurrentUser->RiwayatPenyakit, "Tidak ada diagnosis (file penyakit.csv tidak ditemukan)") == 0)
    {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    // Cek apakah pasien sudah ada di dataAkun
    int idxPasien = -1;
    for (int i = 0; i < da->jumlah; i++)
    {
        if (da->data[i].Id == CurrentUser->Id)
        {
            idxPasien = i;
            break;
        }
    }

    if (idxPasien == -1)
    {
        printf("Data pasien tidak ditemukan!\n");
        return;
    }

    // Cek apakah pasien sudah ada di dataPerutPasien
    int idxPerut = -1;
    for (int i = 0; i < DaPerutPasien->jumlah; i++)
    {
        if (DaPerutPasien->data[i].IdPasien == CurrentUser->Id)
        {
            idxPerut = i;
            break;
        }
    }

    if (idxPerut == -1)
    {
        printf("Data perut pasien kosong!\n");
        printf("Kemungkinan besar kamu belum minum obat apapun.\n");
        return;
    }

    // Ambil semua obat yang ada di perut pasien
    Obat urutanDiminum[MaxEl];
    int jumlahDiminum = 0;

    Stack stackSementara;
    CreateEmpty(&stackSementara);

    while (!IsEmpty(DaPerutPasien->data[idxPerut].Perut))
    {
        Obat temp;
        Pop(&(DaPerutPasien->data[idxPerut].Perut), &temp);
        Push(&stackSementara, temp);
    }

    while (!IsEmpty(stackSementara))
    {
        Obat temp;
        Pop(&stackSementara, &temp);
        Push(&(DaPerutPasien->data[idxPerut].Perut), temp);
        urutanDiminum[jumlahDiminum] = temp;
        jumlahDiminum++;
    }

    // Urutan obat berdasarkan penyakit pasien
    Obat urutanBenar[MaxEl];
    int jumlahUrutanBenar = 0;
    GetUrutanObatByPenyakitFromMap(da->data[idxPasien].RiwayatPenyakit, mapObatPenyakit, mapObat, dataPenyakit, urutanBenar, &jumlahUrutanBenar);

    // Jika pasien tidak punya penyakit (tidak perlu minum obat)
    if (jumlahUrutanBenar == 0)
    {
        if (jumlahDiminum == 0)
        {
            printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n");
            // Reset data pada CurrentUser dan pada dataAkun utama
            copyString(CurrentUser->RiwayatPenyakit, "");
            CurrentUser->SuhuTubuh = -1;
            CurrentUser->TekananDarahSistolik = -1;
            CurrentUser->TekananDarahDiastolik = -1;
            CurrentUser->DetakJantung = -1;
            CurrentUser->SaturasiOksigen = -1;
            CurrentUser->KadarGulaDarah = -1;
            CurrentUser->BeratBadan = -1;
            CurrentUser->TinggiBadan = -1;
            CurrentUser->KadarKolesterol = -1;
            CurrentUser->Trombosit = -1;
            CurrentUser->inventoryObat.jumlah = 0;

            // Reset juga pada dataAkun utama
            da->data[idxPasien].SuhuTubuh = -1;
            da->data[idxPasien].TekananDarahSistolik = -1;
            da->data[idxPasien].TekananDarahDiastolik = -1;
            da->data[idxPasien].DetakJantung = -1;
            da->data[idxPasien].SaturasiOksigen = -1;
            da->data[idxPasien].KadarGulaDarah = -1;
            da->data[idxPasien].BeratBadan = -1;
            da->data[idxPasien].TinggiBadan = -1;
            da->data[idxPasien].KadarKolesterol = -1;
            da->data[idxPasien].Trombosit = -1;
            da->data[idxPasien].inventoryObat.jumlah = 0;
            copyString(da->data[idxPasien].RiwayatPenyakit, "");

            // Hapus pasien dari ruangan/antrian
            for (int i = 0; i < hospital->panjang; i++)
            {
                for (int j = 0; j < hospital->lebar; j++)
                {
                    Ruangan *ruang = &hospital->grid[i][j];
                    // Hapus dari ruangan
                    for (int k = 0; k < ruang->jumlahPasien; k++)
                    {
                        if (ruang->pasien[k].Id == CurrentUser->Id)
                        {
                            for (int l = k; l < ruang->jumlahPasien - 1; l++)
                            {
                                ruang->pasien[l] = ruang->pasien[l + 1];
                            }
                            ruang->jumlahPasien--;
                            break;
                        }
                    }
                    // Hapus dari antrian
                    for (int k = 0; k < ruang->antrian.length; k++)
                    {
                        if (ruang->antrian.pasien[k]->Id == CurrentUser->Id)
                        {
                            for (int l = k; l < ruang->antrian.length - 1; l++)
                            {
                                ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                            }
                            ruang->antrian.length--;
                            break;
                        }
                    }
                    // Setelah penghapusan, isi slot kosong dengan pasien dari antrian (FIFO)
                    while (ruang->jumlahPasien < hospital->kapasitasRuang && ruang->antrian.length > 0)
                    {
                        // Ambil pasien terdepan dari antrian
                        Akun *nextPasien = ruang->antrian.pasien[0];
                        // Geser antrian ke kiri
                        for (int l = 0; l < ruang->antrian.length - 1; l++)
                        {
                            ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                        }
                        ruang->antrian.length--;
                        // Masukkan ke ruangan
                        ruang->pasien[ruang->jumlahPasien++] = *nextPasien;
                    }
                }
            }
            return;
        }
        else
        {
            printf("Anda meminum obat yang seharusnya tidak diminum!\n");
            printf("\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
            return;
        }
    }

    if (jumlahDiminum < jumlahUrutanBenar)
    {
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }

    // Cek apakah ada obat yang diminum tidak sesuai urutanBenar (obat berlebih)
    boolean adaObatBerlebih = false;
    for (int i = 0; i < jumlahDiminum; i++)
    {
        boolean found = false;
        for (int j = 0; j < jumlahUrutanBenar; j++)
        {
            if (urutanDiminum[i].id == urutanBenar[j].id)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            adaObatBerlebih = true;
            break;
        }
    }
    if (adaObatBerlebih)
    {
        printf("Anda meminum obat yang seharusnya tidak diminum!\n");
        printf("\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
        return;
    }

    // Cek urutan minum
    boolean urutanBenarFlag = true;
    for (int i = 0; i < jumlahUrutanBenar; i++)
    {
        int idxStack = jumlahDiminum - jumlahUrutanBenar + i;
        if (idxStack < 0 || urutanDiminum[idxStack].id != urutanBenar[i].id)
        {
            urutanBenarFlag = false;
            break;
        }
    }

    if (!urutanBenarFlag)
    {
        printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i < jumlahUrutanBenar; i++)
        {
            printf("%s", urutanBenar[i].nama);
            if (i < jumlahUrutanBenar - 1)
                printf(" -> ");
        }
        printf("\n\nUrutan obat yang kamu minum:\n");
        for (int i = 0; i < jumlahUrutanBenar; i++)
        {
            int idxStack = jumlahDiminum - jumlahUrutanBenar + i;
            if (idxStack >= 0 && idxStack < jumlahDiminum)
                printf("%s", urutanDiminum[idxStack].nama);
            else
                printf("-");
            if (i < jumlahUrutanBenar - 1)
                printf(" -> ");
        }
        printf("\n\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
        return;
    }

    // Semua valid, reset data pasien
    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n");

    // Reset data akun pasien: hanya id, username, password, role yang dipertahankan
    copyString(CurrentUser->RiwayatPenyakit, "");
    CurrentUser->SuhuTubuh = -1;
    CurrentUser->TekananDarahSistolik = -1;
    CurrentUser->TekananDarahDiastolik = -1;
    CurrentUser->DetakJantung = -1;
    CurrentUser->SaturasiOksigen = -1;
    CurrentUser->KadarGulaDarah = -1;
    CurrentUser->BeratBadan = -1;
    CurrentUser->TinggiBadan = -1;
    CurrentUser->KadarKolesterol = -1;
    CurrentUser->Trombosit = -1;
    CurrentUser->inventoryObat.jumlah = 0;

    da->data[idxPasien].SuhuTubuh = -1;
    da->data[idxPasien].TekananDarahSistolik = -1;
    da->data[idxPasien].TekananDarahDiastolik = -1;
    da->data[idxPasien].DetakJantung = -1;
    da->data[idxPasien].SaturasiOksigen = -1;
    da->data[idxPasien].KadarGulaDarah = -1;
    da->data[idxPasien].BeratBadan = -1;
    da->data[idxPasien].TinggiBadan = -1;
    da->data[idxPasien].KadarKolesterol = -1;
    da->data[idxPasien].Trombosit = -1;
    da->data[idxPasien].inventoryObat.jumlah = 0;
    copyString(da->data[idxPasien].RiwayatPenyakit, "");

    // Reset data perut pasien (hapus stack perut dan entry perut pasien)
    int idxPerutHapus = -1;
    for (int i = 0; i < DaPerutPasien->jumlah; i++)
    {
        if (DaPerutPasien->data[i].IdPasien == CurrentUser->Id)
        {
            idxPerutHapus = i;
            break;
        }
    }
    if (idxPerutHapus != -1)
    {
        // Hapus stack perut
        CreateEmpty(&(DaPerutPasien->data[idxPerutHapus].Perut));
        // Hapus entry perut pasien dari array
        for (int j = idxPerutHapus; j < DaPerutPasien->jumlah - 1; j++)
        {
            DaPerutPasien->data[j] = DaPerutPasien->data[j + 1];
        }
        DaPerutPasien->jumlah--;
    }

    // Hapus pasien dari ruangan/antrian
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            Ruangan *ruang = &hospital->grid[i][j];
            // Hapus dari ruangan
            for (int k = 0; k < ruang->jumlahPasien; k++)
            {
                if (ruang->pasien[k].Id == CurrentUser->Id)
                {
                    for (int l = k; l < ruang->jumlahPasien - 1; l++)
                    {
                        ruang->pasien[l] = ruang->pasien[l + 1];
                    }
                    ruang->jumlahPasien--;
                    break;
                }
            }
            // Hapus dari antrian
            for (int k = 0; k < ruang->antrian.length; k++)
            {
                if (ruang->antrian.pasien[k]->Id == CurrentUser->Id)
                {
                    for (int l = k; l < ruang->antrian.length - 1; l++)
                    {
                        ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                    }
                    ruang->antrian.length--;
                    break;
                }
            }
            // Setelah penghapusan, isi slot kosong dengan pasien dari antrian (FIFO)
            while (ruang->jumlahPasien < hospital->kapasitasRuang && ruang->antrian.length > 0)
            {
                // Ambil pasien terdepan dari antrian
                Akun *nextPasien = ruang->antrian.pasien[0];
                // Geser antrian ke kiri
                for (int l = 0; l < ruang->antrian.length - 1; l++)
                {
                    ruang->antrian.pasien[l] = ruang->antrian.pasien[l + 1];
                }
                ruang->antrian.length--;
                // Masukkan ke ruangan
                ruang->pasien[ruang->jumlahPasien++] = *nextPasien;
            }
        }
    }
}

void GetUrutanObatByPenyakitFromMap(char *namaPenyakit, MapObatPenyakit *mapObatPenyakit, MapObat *mapObat, dataPenyakit *dataPenyakit, Obat *urutanObat, int *jumlahUrutan)
{
    ObatPenyakit obatSementara[MaxEl];
    int jumlahSementara = 0;

    // Cari ID penyakit berdasarkan namaPenyakit
    int idPenyakitPasien = -1;
    for (int i = 0; i < dataPenyakit->jumlah; i++)
    {
        if (strcmp(dataPenyakit->data[i].NamaPenyakit, namaPenyakit) == 0)
        {
            idPenyakitPasien = dataPenyakit->data[i].Id;
            break;
        }
    }

    // Jika penyakit tidak ditemukan, set jumlahUrutan ke 0 dan return
    if (idPenyakitPasien == -1)
    {
        *jumlahUrutan = 0;
        return;
    }

    // Ambil semua obat yang berhubungan dengan penyakit tersebut dari mapObatPenyakit
    for (int i = 0; i < mapObatPenyakit->capacity; i++)
    {
        if (mapObatPenyakit->data[i].occupied)
        {
            ObatPenyakit *relasi = mapObatPenyakit->data[i].value;

            if (relasi->penyakit.Id == idPenyakitPasien)
            {
                Obat *obatLengkap = mapGetObat(mapObat, relasi->obat.id);
                if (obatLengkap != NULL)
                {
                    obatSementara[jumlahSementara].obat = *obatLengkap;
                    obatSementara[jumlahSementara].penyakit = relasi->penyakit;
                    obatSementara[jumlahSementara].urutan_minum = relasi->urutan_minum;
                    jumlahSementara++;
                }
            }
        }
    }

    // Urutkan obatSementara berdasarkan urutan_minum
    for (int i = 0; i < jumlahSementara - 1; i++)
    {
        for (int j = 0; j < jumlahSementara - i - 1; j++)
        {
            if (obatSementara[j].urutan_minum > obatSementara[j + 1].urutan_minum)
            {
                ObatPenyakit temp = obatSementara[j];
                obatSementara[j] = obatSementara[j + 1];
                obatSementara[j + 1] = temp;
            }
        }
    }

    // Masukkan hasil ke urutanObat
    *jumlahUrutan = jumlahSementara;
    for (int i = 0; i < jumlahSementara; i++)
    {
        urutanObat[i] = obatSementara[i].obat;
    }
}