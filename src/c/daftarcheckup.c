#include "pasien.h"
#include "daftarcheckup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern dataAkun tabelAkun;

extern int stringEquals(const char *a, const char *b);
extern void copyString(char *dest, const char *src);
extern float parse_float(char *s);
extern int parse_int(char *s);

// Fungsi untuk mengembalikan akun dokter berdasarkan ID
Akun *findDoctorById(int idDokter, dataAkun *da)
{
    int i;
    for (i = 0; i < da->jumlah; i++)
    {
        if (stringEquals(da->data[i].Role, "dokter") && da->data[i].Id == idDokter)
        {
            return &(da->data[i]);
        }
    }
    return NULL;
}

// Fungsi untuk membaca input string dari pengguna secara manual
void readLineManual(char *buffer, int maxLen)
{
    int i = 0;
    int c;
    while (i < maxLen - 1)
    {
        c = getchar();
        if (c == '\n' || c == EOF)
        {
            break;
        }
        buffer[i] = (char)c;
        i++;
    }
    buffer[i] = '\0';
    if (c != '\n' && c != EOF)
    {
        while (getchar() != '\n' && getchar() != EOF)
            ;
    }
}

// Fungsi untuk membaca input float dari pengguna secara manual
float readFloatInputManual()
{
    char buffer[50];
    readLineManual(buffer, sizeof(buffer));
    return parse_float(buffer);
}

// Fungsi untuk membaca input integer dari pengguna secara manual
int readIntegerInputManual()
{
    char buffer[20];
    readLineManual(buffer, sizeof(buffer));
    return parse_int(buffer);
}

// Fungsi untuk memeriksa apakah pasien sudah berada di ruangan manapun
boolean isPatientInAnyRoom(Akun *pasien, Denah *hospital)
{
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            Ruangan *ruang = &hospital->grid[i][j];
            for (int k = 0; k < ruang->jumlahPasien; k++)
            {
                if (ruang->pasien[k].Id == pasien->Id)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Fungsi untuk memeriksa apakah pasien sudah terdaftar dalam antrian check-up
boolean isPatientAlreadyInQueue(Akun *pasien, DoctorQueueMap *dqm)
{
    int i;
    for (i = 0; i < dqm->doctorQueues.capacity; i++)
    {
        if (dqm->doctorQueues.data[i].occupied)
        {
            LinkedListQueue *queueForDoctor = (LinkedListQueue *)dqm->doctorQueues.data[i].value;
            if (queueForDoctor != NULL)
            {
                NodeQueue *current = queueForDoctor->head;
                while (current != NULL)
                {
                    if (current->pasien->Id == pasien->Id)
                    {
                        return true;
                    }
                    current = current->next;
                }
            }
        }
    }
    return false;
}

// Fungsi untuk membuat DoctorQueueMap
void createDoctorQueueMap(DoctorQueueMap *dqm)
{
    createMapLinkedListQueue(&(dqm->doctorQueues));
}

// Fungsi untuk melakukan check-up registration
void checkUpRegistration(Akun *pasien, DoctorQueueMap *dqm, Denah *hospital)
{
    // Validasi apakah role pengguna adalah pasien dan belum berada di ruangan manapun dan belum terdaftar dalam antrian check-up
    if (!stringEquals(pasien->Role, "pasien"))
    {
        printf("Akses ditolak! Fitur ini hanya untuk pasien.\n");
        return;
    }
    if (isPatientInAnyRoom(pasien, hospital))
    {
        printf("Anda sudah berada di ruangan! Tidak dapat mendaftar check-up lagi.\n");
        return;
    }
    if (isPatientAlreadyInQueue(pasien, dqm))
    {
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }


    // Inisialisasi data check-up pasien
    printf("Silakan masukkan data check-up Anda:\n");
    do
    {
        printf("Suhu Tubuh (Celcius): ");
        pasien->SuhuTubuh = readFloatInputManual();
        if (pasien->SuhuTubuh <= 0)
        {
            printf("Suhu tubuh harus berupa angka positif!\n");
        }
    } while (pasien->SuhuTubuh <= 0);

    // Parse semua atribut pasien yang diperlukan
    do
    {
        printf("Tekanan Darah (sistol/diastol, contoh 120 80): ");
        char td_buffer[20];
        readLineManual(td_buffer, sizeof(td_buffer));
        int i = 0;
        char sistol_str[10];
        char diastol_str[10];
        int j = 0;

        for (i = 0; td_buffer[i] != ' ' && td_buffer[i] != '\0' && j < 9; i++)
        {
            sistol_str[j++] = td_buffer[i];
        }
        sistol_str[j] = '\0';
        pasien->TekananDarahSistolik = parse_int(sistol_str);

        j = 0;
        if (td_buffer[i] == ' ')
        {
            i++;
        }
        for (; td_buffer[i] != '\0' && j < 9; i++)
        {
            diastol_str[j++] = td_buffer[i];
        }
        diastol_str[j] = '\0';
        pasien->TekananDarahDiastolik = parse_int(diastol_str);

        if (pasien->TekananDarahSistolik <= 0 || pasien->TekananDarahDiastolik <= 0)
        {
            printf("Tekanan darah harus berupa angka positif!\n");
        }
    } while (pasien->TekananDarahSistolik <= 0 || pasien->TekananDarahDiastolik <= 0);

    do
    {
        printf("Detak Jantung (bpm): ");
        pasien->DetakJantung = readIntegerInputManual();
        if (pasien->DetakJantung <= 0)
        {
            printf("Detak jantung harus berupa angka positif!\n");
        }
    } while (pasien->DetakJantung <= 0);

    do
    {
        printf("Saturasi Oksigen (%%): ");
        pasien->SaturasiOksigen = readFloatInputManual();
        if (pasien->SaturasiOksigen <= 0 || pasien->SaturasiOksigen > 100)
        {
            printf("Saturasi oksigen harus antara 0 dan 100!\n");
        }
    } while (pasien->SaturasiOksigen <= 0 || pasien->SaturasiOksigen > 100);

    do
    {
        printf("Kadar Gula Darah (mg/dL): ");
        pasien->KadarGulaDarah = readIntegerInputManual();
        if (pasien->KadarGulaDarah <= 0)
        {
            printf("Kadar gula darah harus berupa angka positif!\n");
        }
    } while (pasien->KadarGulaDarah <= 0);

    do
    {
        printf("Berat Badan (kg): ");
        pasien->BeratBadan = readFloatInputManual();
        if (pasien->BeratBadan <= 0)
        {
            printf("Berat badan harus berupa angka positif!\n");
        }
    } while (pasien->BeratBadan <= 0);

    do
    {
        printf("Tinggi Badan (cm): ");
        pasien->TinggiBadan = readIntegerInputManual();
        if (pasien->TinggiBadan <= 0)
        {
            printf("Tinggi badan harus berupa angka positif!\n");
        }
    } while (pasien->TinggiBadan <= 0);

    do
    {
        printf("Kadar Kolestrol (mg/dL): ");
        pasien->KadarKolesterol = readIntegerInputManual();
        if (pasien->KadarKolesterol <= 0)
        {
            printf("Kadar kolesterol harus berupa angka positif!\n");
        }
    } while (pasien->KadarKolesterol <= 0);

    do
    {
        printf("Trombosit (ribu/µL): ");
        pasien->Trombosit = readIntegerInputManual();
        if (pasien->Trombosit <= 0)
        {
            printf("Trombosit harus berupa angka positif!\n");
        }
    } while (pasien->Trombosit <= 0);
    printf("\nBerikut adalah daftar dokter yang tersedia:\n");

    boolean foundDoctor = false;
    Akun *availableDoctors[100];
    int doctor_count = 0;
    int doctor_queue_capacity[100]; // simpan kapasitas antrian ruangan dokter
    int doctor_queue_length[100];   // simpan panjang antrian saat ini
    char doctor_room_code[100][12]; // simpan kode ruangan dokter

    // Menelusuri seluruh ruangan untuk mencari dokter yang tersedia
    for (int r = 0; r < hospital->panjang; r++)
    {
        for (int c = 0; c < hospital->lebar; c++)
        {
            Ruangan *ruang = &hospital->grid[r][c];
            if (ruang->dokter != NULL)
            {
                Akun *dokter = ruang->dokter;
                int kapasitas_antrian = hospital->kapasitasAntrian;

                if (kapasitas_antrian <= 0)
                    continue;

                bool alreadyListed = false;
                for (int i = 0; i < doctor_count; i++)
                {
                    if (availableDoctors[i]->Id == dokter->Id)
                    {
                        alreadyListed = true;
                        break;
                    }
                }

                if (!alreadyListed)
                {
                    availableDoctors[doctor_count] = dokter;
                    doctor_queue_capacity[doctor_count] = kapasitas_antrian;
                    copyString(doctor_room_code[doctor_count], ruang->kode);

                    // Jumlah antrian = jumlah pasien di antrian ruangan
                    int queue_length = ruang->antrian.length;
                    doctor_queue_length[doctor_count] = queue_length;

                    char spec_temp[50] = "Umum";
                    char capDokterUsername[50];
                    strcpy(capDokterUsername, dokter->Username);
                    capitalizeCommand(capDokterUsername);

                    if (queue_length >= kapasitas_antrian)
                    {
                        printf("%d. Dr. %s - Spesialisasi %s - Ruangan %s (Antrian: %d orang (penuh))\n",
                               doctor_count + 1,
                               capDokterUsername,
                               spec_temp,
                               ruang->kode,
                               queue_length);
                    }
                    else
                    {
                        printf("%d. Dr. %s - Spesialisasi %s - Ruangan %s (Antrian: %d orang)\n",
                               doctor_count + 1,
                               capDokterUsername,
                               spec_temp,
                               ruang->kode,
                               queue_length);
                    }
                    doctor_count++;
                    foundDoctor = true;
                }
            }
        }
    }

    // Jika tidak ada dokter yang tersedia, tampilkan pesan
    if (!foundDoctor)
    {
        printf("Tidak ada dokter yang tersedia saat ini.\n");
        return;
    }

    // Berikan pilihan kepada pasien untuk memilih dokter
    int choice;
    do
    {
        printf("\nPilih dokter (1-%d): ", doctor_count);
        choice = readIntegerInputManual();
        if (choice < 1 || choice > doctor_count)
        {
            printf("Pilihan dokter tidak valid!\n");
        }
        else if (doctor_queue_length[choice - 1] >= doctor_queue_capacity[choice - 1])
        {
            printf("Antrian pada dokter %s di ruangan %s sudah penuh! Silakan pilih dokter lain.\n",
                   availableDoctors[choice - 1]->Username, doctor_room_code[choice - 1]);
            choice = -1; // ulangi input
        }
    } while (choice < 1 || choice > doctor_count);

    Akun *selectedDoctor = availableDoctors[choice - 1];
    int max_kapasitas_antrian = doctor_queue_capacity[choice - 1];
    char room_final[12];
    copyString(room_final, doctor_room_code[choice - 1]);

    // Cari ruangan dokter terpilih
    Ruangan *selectedRoom = NULL;
    for (int r = 0; r < hospital->panjang && !selectedRoom; r++)
    {
        for (int c = 0; c < hospital->lebar && !selectedRoom; c++)
        {
            Ruangan *ruang = &hospital->grid[r][c];
            if (ruang->dokter != NULL && ruang->dokter->Id == selectedDoctor->Id)
            {
                selectedRoom = ruang;
            }
        }
    }

    if (selectedRoom == NULL)
    {
        printf("Ruangan dokter tidak ditemukan.\n");
        return;
    }

    // Jika ruangan belum penuh, pasien langsung masuk ruangan
    if (selectedRoom->jumlahPasien < hospital->kapasitasRuang)
    {
        // Masukkan ke ruangan
        if (selectedRoom->pasien == NULL)
        {
            createListAkun(&selectedRoom->pasien, hospital->kapasitasRuang);
        }
        int jumlahPasien = selectedRoom->jumlahPasien;
        int kapasitasPasien = hospital->kapasitasRuang;
        insertLastListAkun(&selectedRoom->pasien, *pasien, &jumlahPasien, &kapasitasPasien);
        selectedRoom->jumlahPasien = jumlahPasien;

        printf("\nPendaftaran check-up berhasil!\n");
        char capDokterUsername[50];
        strcpy(capDokterUsername, selectedDoctor->Username);
        capitalizeCommand(capDokterUsername);
        printf("Anda dipersilahkan masuk ke ruangan Dr. %s di ruangan %s.\n", capDokterUsername, room_final);
        printf("Silakan menunggu untuk didiagnosis oleh dokter.\n");
    }
    else
    {
        // Jika ruangan penuh, masuk ke antrian
        LinkedListQueue *doctorQueue = (LinkedListQueue *)mapGetLinkedListQueue(&(dqm->doctorQueues), selectedDoctor->Id);
        if (doctorQueue == NULL)
        {
            doctorQueue = (LinkedListQueue *)malloc(sizeof(LinkedListQueue));
            if (doctorQueue == NULL)
            {
                fprintf(stderr, "Gagal alokasi memori untuk antrian dokter.\n");
                return;
            }
            createLinkedListQueue(doctorQueue);
            insertMapLinkedListQueue(&(dqm->doctorQueues), selectedDoctor->Id, doctorQueue);
        }
        enqueueLinkedListQueue(doctorQueue, pasien);

        // Tambahkan pasien ke antrian ruangan
        int pos = selectedRoom->antrian.length;
        if (pos < selectedRoom->antrian.kapasitas)
        {
            selectedRoom->antrian.pasien[pos] = pasien;
            selectedRoom->antrian.length++;
        }
        else
        {
            printf("Antrian pada ruangan %s sudah penuh!\n", selectedRoom->kode);
        }

        printf("\nPendaftaran check-up berhasil!\n");
        char capDokterUsername[50];
        strcpy(capDokterUsername, selectedDoctor->Username);
        capitalizeCommand(capDokterUsername);
        printf("Anda terdaftar pada antrian Dr. %s di ruangan %s.\n", capDokterUsername, room_final);
        printf("Posisi antrian Anda: %d\n", doctorQueue->length);
    }
}

// Fungsi untuk menampilkan antrian check-up pasien
void displayPatientQueue(Akun *CurrentUser, DoctorQueueMap *dqm)
{
    // Validasi apakah role pengguna adalah pasien
    if (!stringEquals(CurrentUser->Role, "pasien"))
    {
        printf("Akses ditolak! Fitur ini hanya untuk pasien.\n");
        return;
    }

    printf("--- Antrian Anda ---\n");
    boolean foundInQueue = false;

    // Menelusuri seluruh antrian dokter untuk mencari pasien
    int i;
    for (i = 0; i < dqm->doctorQueues.capacity; i++)
    {
        if (dqm->doctorQueues.data[i].occupied)
        {
            LinkedListQueue *queueForDoctor = (LinkedListQueue *)dqm->doctorQueues.data[i].value;
            if (queueForDoctor != NULL)
            {
                NodeQueue *current = queueForDoctor->head;
                int position = 1;
                while (current != NULL)
                {
                    if (current->pasien->Id == CurrentUser->Id)
                    {
                        Akun *doctor = findDoctorById(dqm->doctorQueues.data[i].key, &tabelAkun);
                        if (doctor != NULL)
                        {
                            char capDokterUsername[50];
                            strcpy(capDokterUsername, doctor->Username);
                            capitalizeCommand(capDokterUsername);
                            char capPasienUsername[50];
                            strcpy(capPasienUsername, CurrentUser->Username);
                            capitalizeCommand(capPasienUsername);
                            printf("Anda (%s) berada di antrian Dokter %s (ID: %d) pada posisi ke-%d.\n", capPasienUsername, capDokterUsername, doctor->Id, position);
                        }
                        else
                        {
                            char capPasienUsername[50];
                            strcpy(capPasienUsername, CurrentUser->Username);
                            capitalizeCommand(capPasienUsername);
                            printf("Anda (%s) berada di antrian dokter (ID: %d) pada posisi ke-%d.\n", capPasienUsername, dqm->doctorQueues.data[i].key, position);
                        }
                        foundInQueue = true;
                        break;
                    }
                    current = current->next;
                    position++;
                }
            }
        }
        if (foundInQueue)
        {
            break;
        }
    }

    // Jika tidak ditemukan dalam antrian, tampilkan pesan
    if (!foundInQueue)
    {
        printf("Anda tidak sedang dalam antrian check-up manapun.\n");
    }
    printf("--------------------\n");
}

// Fungsi untuk membebaskan memori yang digunakan oleh DoctorQueueMap
void freeDoctorQueueMap(DoctorQueueMap *dqm)
{
    int i;
    for (i = 0; i < dqm->doctorQueues.capacity; i++)
    {
        if (dqm->doctorQueues.data[i].occupied)
        {
            LinkedListQueue *queue = (LinkedListQueue *)dqm->doctorQueues.data[i].value;
            if (queue != NULL)
            {
                freeLinkedListQueue(queue);
                free(queue);
            }
        }
    }
    freeMapLinkedListQueue(&(dqm->doctorQueues));
}