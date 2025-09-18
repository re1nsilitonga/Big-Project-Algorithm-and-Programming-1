#include "load.h"
#include "denah.h"
#include "map.h"
#include "user.h"
#include "queue.h"
#include "obat.h"
#include "penyakit.h"
#include "listdin.h"
#include "dataperut.h"
#include "daftarcheckup.h"
#include <stdio.h>

void readData(FILE *file, char *dest, int maxLen)
{
    int i = 0;
    char c = fgetc(file);

    // Jika langsung delimiter atau newline atau EOF, berarti field kosong
    if (c == ';' || c == '\n' || c == EOF)
    {
        dest[i] = '\0';
        if (c == '\n' || c == EOF)
        {
            ungetc(c, file);
        }
        return;
    }

    // Kalau bukan kosong, kita baca isi field
    while (c != EOF && c != ';' && c != '\n' && i < maxLen - 1)
    {
        dest[i++] = c;
        c = fgetc(file);
    }
    dest[i] = '\0';

    if (c == '\n' || c == EOF)
    {
        ungetc(c, file);
    }
}

void readDataPenyakit(const char *line, char *dest, int maxLen, int *pos)
{
    int i = 0;
    while (line[*pos] != ';' && line[*pos] != '\0' && line[*pos] != '\n' && i < maxLen - 1)
    {
        dest[i++] = line[(*pos)++];
    }
    dest[i] = '\0';
    if (line[*pos] == ';')
    {
        (*pos)++;
    }
}

void read_config(const char *filename, Denah *hospital, MapAkun *map, dataObat *data_obat, MapObat *map_obat, DataPerutPasien *dataPerut, DoctorQueueMap *doctorQueues)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Gagal membuka file %s\n", filename);
        exit(1);
    }

    char line[256];
    int line_number = 0;
    int ruangan_count = 0;
    int kapasitasAntrian = 0;
    int jumlah_pasien_inventory = -2;
    int baris_inventory_diproses = 0;
    int jumlah_pasien_perut = -2;
    int baris_perut_diproses = 0;

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';
        line_number++;

        if (line_number == 1)
        {
            int i = 0;
            hospital->panjang = atoi(&line[i]);
            while (line[i] != ' ')
                i++;
            hospital->lebar = atoi(&line[i + 1]);
            createGrid(hospital->panjang, hospital->lebar, &hospital->grid);
        }
        else if (line_number == 2)
        {
            int i = 0;
            hospital->kapasitasRuang = atoi(&line[i]);
            while (line[i] != ' ' && line[i] != '\0')
                i++;

            if (line[i] != '\0')
            {
                kapasitasAntrian = atoi(&line[i + 1]);
            }
        }
        else if (line_number >= 3 && line_number < 3 + hospital->panjang * hospital->lebar)
        {
            int idx = ruangan_count++;
            int i = idx / hospital->lebar;
            int j = idx % hospital->lebar;
            Ruangan *ruang = &hospital->grid[i][j];
            ruang->dokter = NULL;
            ruang->jumlahPasien = 0;
            snprintf(ruang->kode, sizeof(ruang->kode), "%c%d", 'A' + i, j + 1);

            createQueue(&ruang->antrian);
            ruang->antrian.kapasitas = kapasitasAntrian;
            hospital->kapasitasAntrian = kapasitasAntrian;

            int pos = 0;
            int doctor_id = atoi(&line[pos]);
            if (doctor_id != 0)
            {
                ruang->dokter = mapGetAkun(map, doctor_id);
                if (ruang->dokter == NULL)
                {
                    continue;
                }
            }
            while (line[pos] != ' ' && line[pos] != '\0')
                pos++;
            if (line[pos] == '\0')
                continue;
            pos++;

            createListAkun(&ruang->pasien, hospital->kapasitasRuang);
            int jumlahPasien = 0;
            int kapasitasPasien = hospital->kapasitasRuang;

            while (line[pos] != '\0' && jumlahPasien < hospital->kapasitasRuang)
            {
                while (line[pos] == ' ')
                    pos++;
                if (line[pos] == '\0')
                    break;
                int pasien_id = atoi(&line[pos]);
                if (pasien_id != 0)
                {
                    Akun *pasien = mapGetAkun(map, pasien_id);
                    if (pasien != NULL)
                    {
                        insertLastListAkun(&ruang->pasien, *pasien, &jumlahPasien, &kapasitasPasien);
                        if (ruang->dokter != NULL && pasien != NULL && doctorQueues != NULL)
                        {
                            LinkedListQueue *doctorQueue = mapGetLinkedListQueue(&(doctorQueues->doctorQueues), ruang->dokter->Id);
                            if (doctorQueue == NULL)
                            {
                                doctorQueue = malloc(sizeof(LinkedListQueue));
                                createLinkedListQueue(doctorQueue);
                                insertMapLinkedListQueue(&(doctorQueues->doctorQueues), ruang->dokter->Id, doctorQueue);
                            }
                            enqueueLinkedListQueue(doctorQueue, pasien);
                        }
                    }
                }
                while (line[pos] != ' ' && line[pos] != '\0')
                    pos++;
            }
            ruang->jumlahPasien = jumlahPasien;

            while (line[pos] != '\0')
            {
                while (line[pos] == ' ')
                    pos++;
                if (line[pos] == '\0')
                    break;
                int pasien_id = atoi(&line[pos]);
                if (pasien_id != 0)
                {
                    Akun *pasien = mapGetAkun(map, pasien_id);
                    if (pasien != NULL)
                    {
                        enqueue(&ruang->antrian, pasien);
                        if (ruang->dokter != NULL && doctorQueues != NULL)
                        {
                            LinkedListQueue *doctorQueue = mapGetLinkedListQueue(&(doctorQueues->doctorQueues), ruang->dokter->Id);
                            if (doctorQueue == NULL)
                            {
                                doctorQueue = malloc(sizeof(LinkedListQueue));
                                createLinkedListQueue(doctorQueue);
                                insertMapLinkedListQueue(&(doctorQueues->doctorQueues), ruang->dokter->Id, doctorQueue);
                            }
                            enqueueLinkedListQueue(doctorQueue, pasien);
                        }
                    }
                }
                while (line[pos] != ' ' && line[pos] != '\0')
                    pos++;
            }
        }
        else if (jumlah_pasien_inventory == -2)
        {
            jumlah_pasien_inventory = atoi(line);
            if (jumlah_pasien_inventory == 0)
            {
                jumlah_pasien_perut = -2; /* biar langsung ke perut */
            }
        }
        else if (baris_inventory_diproses < jumlah_pasien_inventory)
        {
            int pos = 0;

            int pasien_id = atoi(&line[pos]);
            while (line[pos] != ' ' && line[pos] != '\0')
                pos++;
            while (line[pos] == ' ')
                pos++;

            Akun *pasien = mapGetAkun(map, pasien_id);
            if (pasien == NULL)
            {
                baris_inventory_diproses++;
                continue;
            }

            createTableObat(&pasien->inventoryObat, 5);

            while (line[pos] != '\0')
            {
                while (line[pos] == ' ')
                    pos++;
                if (line[pos] == '\0')
                    break;

                int obat_id = atoi(&line[pos]);
                Obat *obat = mapGetObat(map_obat, obat_id);
                if (obat != NULL)
                {
                    insertLastObat(&pasien->inventoryObat, *obat);
                }
                while (line[pos] != ' ' && line[pos] != '\0')
                    pos++;
            }

            baris_inventory_diproses++;
        }
        else if (jumlah_pasien_inventory != -2 && baris_inventory_diproses == jumlah_pasien_inventory && jumlah_pasien_perut == -2)
        {
            jumlah_pasien_perut = atoi(line);
            if (jumlah_pasien_perut == 0)
            {
                continue; // tidak ada perut
            }
            dataPerut->kapasitas = jumlah_pasien_perut;
            dataPerut->jumlah = 0;
            dataPerut->data = malloc(jumlah_pasien_perut * sizeof(PerutPasien));
        }
        else if (jumlah_pasien_perut > 0 && baris_perut_diproses < jumlah_pasien_perut)
        {
            int pos = 0;
            int pasien_id = atoi(&line[pos]);
            while (line[pos] != ' ' && line[pos] != '\0')
                pos++;
            while (line[pos] == ' ')
                pos++;

            PerutPasien *entry = &dataPerut->data[dataPerut->jumlah];
            entry->IdPasien = pasien_id;
            CreateEmpty(&entry->Perut);

            int list_obat_id[20];
            int count = 0;

            while (line[pos] != '\0')
            {
                while (line[pos] == ' ')
                    pos++;
                if (line[pos] == '\0')
                    break;

                int obat_id = 0;
                while (line[pos] >= '0' && line[pos] <= '9')
                {
                    obat_id = obat_id * 10 + (line[pos++] - '0');
                }

                if (count < 20)
                {
                    list_obat_id[count++] = obat_id;
                }

                while (line[pos] == ' ')
                    pos++;
            }

            // Push dari belakang ke depan (count-1 ke 0)
            // Sehingga stack: yang paling kiri di file (2) jadi top (obat terakhir diminum)
            for (int i = count - 1; i >= 0; i--)
            {
                Obat obat;
                int found = 0;
                for (int j = 0; j < data_obat->jumlah; j++)
                {
                    if (data_obat->data[j].id == list_obat_id[i])
                    {
                        obat = data_obat->data[j];
                        found = 1;
                        break;
                    }
                }
                if (found)
                {
                    Push(&entry->Perut, obat);
                }
            }

            dataPerut->jumlah++;
            baris_perut_diproses++;
        }
    }
    fclose(file);
}

boolean loadData(
    dataAkun *da,
    const char *folder,
    MapAkun *mapAkun,
    Denah *hospital,
    dataPenyakit *daPenyakit,
    MapPenyakit *mapPenyakit,
    dataObat *daObat,
    MapObat *mapObat,
    dataObatPenyakit *daObatPenyakit,
    MapObatPenyakit *mapObatPenyakit,
    DataPerutPasien *dataPerutPasien,
    DoctorQueueMap *doctorQueues)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/user.csv", folder);

    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Gagal membuka file");
        return false;
    }

    char temp[256];
    fgets(temp, sizeof(temp), file); // Skip header

    while (1)
    {
        if (da->jumlah == da->kapasitas)
        {
            da->kapasitas *= 2;
            da->data = realloc(da->data, da->kapasitas * sizeof(Akun));
            if (!da->data)
            {
                perror("Gagal realokasi memori");
                exit(EXIT_FAILURE);
            }
        }

        Akun akun;
        initAkun(&akun);
        char buffer[100];

        readData(file, buffer, sizeof(buffer));
        if (feof(file))
            break;
        akun.Id = atoi(buffer);

        readData(file, akun.Username, sizeof(akun.Username));
        readData(file, akun.Password, sizeof(akun.Password));
        readData(file, akun.Role, sizeof(akun.Role));
        readData(file, akun.RiwayatPenyakit, sizeof(akun.RiwayatPenyakit));

        readData(file, buffer, sizeof(buffer));
        akun.SuhuTubuh = buffer[0] ? atof(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.TekananDarahSistolik = buffer[0] ? atoi(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.TekananDarahDiastolik = buffer[0] ? atoi(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.DetakJantung = buffer[0] ? atoi(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.SaturasiOksigen = buffer[0] ? atof(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.KadarGulaDarah = buffer[0] ? atoi(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.BeratBadan = buffer[0] ? atof(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.TinggiBadan = buffer[0] ? atof(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.KadarKolesterol = buffer[0] ? atoi(buffer) : -1;

        readData(file, buffer, sizeof(buffer));
        akun.Trombosit = buffer[0] ? atoi(buffer) : -1;

        da->data[da->jumlah++] = akun;
        insertMapAkun(mapAkun, akun.Id, &da->data[da->jumlah - 1]);

        int c = fgetc(file);
        if (c == EOF)
            break;

        if (c != '\n')
            ungetc(c, file);
    }

    fclose(file);

    if (loadDataObat(daObat, folder, mapObat) == false)
    {
        return false;
    }

    if (!loadHospitalData(hospital, folder, da, mapAkun, daObat, mapObat, dataPerutPasien, doctorQueues))
    {
        return false;
    }

    if (!loadDataPenyakit(daPenyakit, folder, mapPenyakit))
    {
        return false;
    }

    if (loadDataObatPenyakit(daObatPenyakit, folder, mapObatPenyakit) == false)
    {
        return false;
    }

    return true;
}

boolean loadHospitalData(Denah *hospital, const char *folder, dataAkun *da, MapAkun *map, dataObat *data_obat, MapObat *map_obat, DataPerutPasien *dataPerut, DoctorQueueMap *doctorQueues)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/config.txt", folder);

    read_config(path, hospital, map, data_obat, map_obat, dataPerut, doctorQueues);
    return true;
}

boolean loadDataPenyakit(dataPenyakit *daPenyakit, const char *folder, MapPenyakit *map)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/penyakit.csv", folder);

    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Gagal membuka file penyakit.csv");
        return false;
    }

    char line[512];
    fgets(line, sizeof(line), file); // Skip header

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
            continue;

        if (daPenyakit->jumlah == daPenyakit->kapasitas)
        {
            daPenyakit->kapasitas *= 2;
            daPenyakit->data = realloc(daPenyakit->data, daPenyakit->kapasitas * sizeof(Penyakit));
            if (!daPenyakit->data)
            {
                perror("Gagal realokasi memori penyakit");
                exit(EXIT_FAILURE);
            }
        }

        int pos = 0;
        char buf[100];
        Penyakit penyakit = {0};

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        if (buf[0] == '\0')
        {
            continue;
        }
        penyakit.Id = atoi(buf);

        readDataPenyakit(line, penyakit.NamaPenyakit, sizeof(penyakit.NamaPenyakit), &pos);

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.SuhuTubuhMin = buf[0] ? atof(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.SuhuTubuhMax = buf[0] ? atof(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TekananDarahSistolikMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TekananDarahSistolikMax = buf[0] ? atoi(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TekananDarahDiastolikMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TekananDarahDiastolikMax = buf[0] ? atoi(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.DetakJantungMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.DetakJantungMax = buf[0] ? atoi(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.SaturasiOksigenMin = buf[0] ? atof(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.SaturasiOksigenMax = buf[0] ? atof(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.KadarGulaDarahMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.KadarGulaDarahMax = buf[0] ? atoi(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.BeratBadanMin = buf[0] ? atof(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.BeratBadanMax = buf[0] ? atof(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TinggiBadanMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TinggiBadanMax = buf[0] ? atoi(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.KadarKolesterolMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.KadarKolesterolMax = buf[0] ? atoi(buf) : -1;

        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TrombositMin = buf[0] ? atoi(buf) : -1;
        readDataPenyakit(line, buf, sizeof(buf), &pos);
        penyakit.TrombositMax = buf[0] ? atoi(buf) : -1;

        daPenyakit->data[daPenyakit->jumlah++] = penyakit;
        insertMapPenyakit(map, penyakit.Id, &daPenyakit->data[daPenyakit->jumlah - 1]);
    }

    fclose(file);
    return true;
}

boolean loadDataObat(dataObat *daObat, const char *folder, MapObat *mapObat)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/obat.csv", folder);

    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Gagal membuka file obat.csv");
        return false;
    }

    char line[256];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
            continue;

        if (daObat->jumlah == daObat->kapasitas)
        {
            daObat->kapasitas *= 2;
            daObat->data = realloc(daObat->data, daObat->kapasitas * sizeof(Obat));
            if (!daObat->data)
            {
                perror("Gagal realokasi memori obat");
                exit(EXIT_FAILURE);
            }
        }

        int pos = 0;
        char buf[100];
        Obat obat = {0};

        int i = 0;
        while (line[pos] != ';' && line[pos] != '\0' && line[pos] != '\n' && i < 99)
            buf[i++] = line[pos++];
        buf[i] = '\0';
        obat.id = atoi(buf);

        if (line[pos] == ';')
            pos++;

        i = 0;
        while (line[pos] != ';' && line[pos] != '\0' && line[pos] != '\n' && line[pos] != '\r' && i < 63)
            obat.nama[i++] = line[pos++];

        daObat->data[daObat->jumlah++] = obat;
        insertMapObat(mapObat, obat.id, &daObat->data[daObat->jumlah - 1]);
    }

    fclose(file);
    return true;
}

boolean loadDataObatPenyakit(dataObatPenyakit *daObatPenyakit, const char *folder, MapObatPenyakit *mapObatPenyakit)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/obat_penyakit.csv", folder);

    FILE *file = fopen(path, "r");
    if (!file)
    {
        perror("Gagal membuka file obat_penyakit.csv");
        return false;
    }

    char line[256];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file))
    {
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
            continue;

        if (daObatPenyakit->jumlah == daObatPenyakit->kapasitas)
        {
            daObatPenyakit->kapasitas *= 2;
            daObatPenyakit->data = realloc(daObatPenyakit->data, daObatPenyakit->kapasitas * sizeof(ObatPenyakit));
            if (!daObatPenyakit->data)
            {
                perror("Gagal realokasi memori obat-penyakit");
                exit(EXIT_FAILURE);
            }
        }

        int pos = 0;
        char buf[100];
        ObatPenyakit op = {0};

        int i = 0;
        while (line[pos] != ';' && line[pos] != '\0' && line[pos] != '\n' && i < 99)
            buf[i++] = line[pos++];
        buf[i] = '\0';
        op.obat.id = atoi(buf);

        if (line[pos] == ';')
            pos++;

        i = 0;
        while (line[pos] != ';' && line[pos] != '\0' && line[pos] != '\n' && i < 99)
            buf[i++] = line[pos++];
        buf[i] = '\0';
        op.penyakit.Id = atoi(buf);

        if (line[pos] == ';')
            pos++;

        i = 0;
        while (line[pos] != ';' && line[pos] != '\0' && line[pos] != '\n' && i < 99)
            buf[i++] = line[pos++];
        buf[i] = '\0';
        op.urutan_minum = atoi(buf);

        daObatPenyakit->data[daObatPenyakit->jumlah++] = op;
        int key = op.obat.id * 1000 + op.penyakit.Id;
        insertMapObatPenyakit(mapObatPenyakit, key, &daObatPenyakit->data[daObatPenyakit->jumlah - 1]);
    }

    fclose(file);
    return true;
}