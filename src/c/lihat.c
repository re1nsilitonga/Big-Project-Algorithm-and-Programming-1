#include "lihat.h"
#include "auth.h"

dataAkun Filter(dataAkun da, char *filter)
{
    dataAkun daFilter;
    createTableAkun(&daFilter, 1000);

    // Jika ingin pasien saja
    if (strcmp(filter, "pasien") == 0)
    {
        for (int i = 0; i < da.jumlah; i++)
        {
            if (strcmp(da.data[i].Role, "pasien") == 0)
            {
                insertLastAkun(&daFilter, da.data[i]);
            }
        }
    }

    // Jika ingin dokter saja
    if (strcmp(filter, "dokter") == 0)
    {
        for (int i = 0; i < da.jumlah; i++)
        {
            if (strcmp(da.data[i].Role, "dokter") == 0)
            {
                insertLastAkun(&daFilter, da.data[i]);
            }
        }
    }

    return daFilter;
}

// Fungsi menyalin data akun berdasarkan ID urutan menaik (tanpa manager)
dataAkun SortAscID(dataAkun da)
{
    dataAkun daRes;
    createTableAkun(&daRes, 1000);

    // Salin data yang bukan manager
    for (int i = 0; i < da.jumlah; i++)
    {
        if (strcmp(da.data[i].Role, "manager") != 0)
        {
            insertLastAkun(&daRes, da.data[i]);
        }
    }

    // Insertion sort berdasarkan ID (menaik)
    for (int i = 1; i < daRes.jumlah; i++)
    {
        Akun key = daRes.data[i];
        int j = i - 1;

        while (j >= 0 && daRes.data[j].Id > key.Id)
        {
            daRes.data[j + 1] = daRes.data[j];
            j--;
        }
        daRes.data[j + 1] = key;
    }

    return daRes;
}

// Fungsi menyalin data akun berdasarkan ID urutan menurun (tanpa manager)
dataAkun SortDscID(dataAkun da)
{
    dataAkun daRes;
    createTableAkun(&daRes, 1000);

    // Salin data yang bukan manager
    for (int i = 0; i < da.jumlah; i++)
    {
        if (strcmp(da.data[i].Role, "manager") != 0)
        {
            insertLastAkun(&daRes, da.data[i]);
        }
    }

    // Insertion sort berdasarkan ID (menurun)
    for (int i = 1; i < daRes.jumlah; i++)
    {
        Akun key = daRes.data[i];
        int j = i - 1;

        while (j >= 0 && daRes.data[j].Id < key.Id)
        {
            daRes.data[j + 1] = daRes.data[j];
            j--;
        }
        daRes.data[j + 1] = key;
    }

    return daRes;
}

// Fungsi mengurutkan data berdasarkan username urutan menaik (tanpa manager)
dataAkun SortAscUN(dataAkun da)
{
    dataAkun daRes;
    createTableAkun(&daRes, 1000);

    // Salin semua data kecuali manager
    for (int i = 0; i < da.jumlah; i++)
    {
        if (strcmp(da.data[i].Role, "manager") != 0)
        {
            insertLastAkun(&daRes, da.data[i]);
        }
    }

    // Bubble sort berdasarkan Username (a-z)
    for (int i = 0; i < daRes.jumlah - 1; i++)
    {
        for (int j = daRes.jumlah - 1; j >= i + 1; j--)
        {
            char name1[100], name2[100];
            strcpy(name1, daRes.data[j].Username);
            strcpy(name2, daRes.data[j - 1].Username);
            toLowerString(name1);
            toLowerString(name2);
            if (strcmp(name1, name2) < 0)
            {
                Akun temp = daRes.data[j];
                daRes.data[j] = daRes.data[j - 1];
                daRes.data[j - 1] = temp;
            }
        }
    }

    return daRes;
}

// Fungsi mengurutkan data berdasarkan username urutan menurun (tanpa manager)
dataAkun SortDscUN(dataAkun da)
{
    dataAkun daRes;
    createTableAkun(&daRes, 1000);

    // Salin semua data kecuali manager
    for (int i = 0; i < da.jumlah; i++)
    {
        if (strcmp(da.data[i].Role, "manager") != 0)
        {
            insertLastAkun(&daRes, da.data[i]);
        }
    }

    // Bubble sort berdasarkan Username (z-a)
    for (int i = 0; i < daRes.jumlah - 1; i++)
    {
        for (int j = daRes.jumlah - 1; j >= i + 1; j--)
        {
            char name1[100], name2[100];
            strcpy(name1, daRes.data[j].Username);
            strcpy(name2, daRes.data[j - 1].Username);
            toLowerString(name1);
            toLowerString(name2);
            if (strcmp(name1, name2) > 0)
            {
                Akun temp = daRes.data[j];
                daRes.data[j] = daRes.data[j - 1];
                daRes.data[j - 1] = temp;
            }
        }
    }

    return daRes;
}

void TampilkanDataUser(dataAkun daRes, char *urutan, char *klasifikasi)
{
    if (daRes.jumlah == 0)
    {
        printf("Tidak ada data user yang ditemukan.\n");
    }
    else
    {
        printf("Menampilkan semua pengguna dengan %s terurut %s...\n", klasifikasi, urutan);
        printf(" ID  | %-12s | %-8s | %-20s\n", "Nama", "Role", "Penyakit");
        printf("-----------------------------------------------------\n");

        for (int i = 0; i < daRes.jumlah; i++)
        {
            Akun akun = daRes.data[i];
            // Jika role adalah dokter, penyakit di-set sebagai "-"
            char *penyakit = strcmp(akun.Role, "dokter") == 0 ? "-" : akun.RiwayatPenyakit;
            char capUsername[50];
            strcpy(capUsername, akun.Username);
            capitalizeCommand(capUsername);
            printf("%4d | %-12s | %-8s | %-20s\n", akun.Id, capUsername, akun.Role, penyakit);
        }
    }
}

void TampilkanDataPasien(dataAkun daRes, char *urutan, char *klasifikasi)
{
    if (daRes.jumlah == 0)
    {
        printf("Tidak ada data pasien yang ditemukan.\n");
    }
    else
    {
        printf("Menampilkan pasien dengan %s terurut %s...\n", klasifikasi, urutan);
        printf(" ID  | %-12s | %-20s\n", "Nama", "Penyakit");
        printf("------------------------------------------\n");

        for (int i = 0; i < daRes.jumlah; i++)
        {
            Akun akun = daRes.data[i];
            char capUsername[50];
            strcpy(capUsername, akun.Username);
            capitalizeCommand(capUsername);
            printf("%4d | %-12s | %-20s\n", akun.Id, capUsername, akun.RiwayatPenyakit);
        }
    }
}

void TampilkanDataDokter(dataAkun daRes, char *urutan, char *klasifikasi)
{
    if (daRes.jumlah == 0)
    {
        printf("Tidak ada data dokter yang ditemukan.\n");
    }
    else
    {
        printf("Menampilkan dokter dengan %s terurut %s...\n", klasifikasi, urutan);
        printf(" ID  | %-12s\n", "Nama");
        printf("-------------------\n");

        for (int i = 0; i < daRes.jumlah; i++)
        {
            Akun akun = daRes.data[i];
            char capUsername[50];
            strcpy(capUsername, akun.Username);
            capitalizeCommand(capUsername);
            printf("%4d | %-12s\n", akun.Id, capUsername);
        }
    }
}

void LihatUser(dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    dataAkun daPrint;
    char urutan[50];
    char klasifikasi[50];

    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    // Jika manager maka keluar MENU
    int pilihan_1, pilihan_2;
    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Username\n");
    printf(">>> Pilihan: ");
    for (;;)
    {
        scanf("%d", &pilihan_1);
        flushInput();
        if (pilihan_1 == 1 || pilihan_1 == 2)
            break;
        else
            printf("Pilihan tidak valid!\n");
    }

    // Urutkan berdasarkan ID
    if (pilihan_1 == 1)
    {
        printf("Urutan sort?\n");
        printf("1. ASC (Urutkan naik)\n");
        printf("2. DSC (Urutkan turun)\n");
        printf(">>> Pilihan: ");
        for (;;)
        {
            scanf("%d", &pilihan_2);
            flushInput();
            if (pilihan_2 == 1 || pilihan_2 == 2)
                break;
            else
                printf("Pilihan tidak valid!\n");
        }
        // Urutkan ASC
        if (pilihan_2 == 1)
        {
            daPrint = SortAscID(*da);
            strcpy(urutan, "ascending");
            strcpy(klasifikasi, "ID");
        }
        // Urutkan DSC
        else if (pilihan_2 == 2)
        {
            daPrint = SortDscID(*da);
            strcpy(urutan, "descending");
            strcpy(klasifikasi, "ID");
        }
    }

    // Urutkan berdasarkan Username
    else if (pilihan_1 == 2)
    {
        printf("Urutan sort?\n");
        printf("1. ASC (A-Z)\n");
        printf("2. DSC (Z-A)\n");
        printf(">>> Pilihan: ");
        for (;;)
        {
            scanf("%d", &pilihan_2);
            flushInput();
            if (pilihan_2 == 1 || pilihan_2 == 2)
                break;
            else
                printf("Pilihan tidak valid!\n");
        }
        // Urutkan ASC
        if (pilihan_2 == 1)
        {
            daPrint = SortAscUN(*da);
            strcpy(urutan, "ascending");
            strcpy(klasifikasi, "username");
        }
        // Urutkan DSC
        else if (pilihan_2 == 2)
        {
            daPrint = SortDscUN(*da);
            strcpy(urutan, "descending");
            strcpy(klasifikasi, "username");
        }
    }

    // Print
    TampilkanDataUser(daPrint, urutan, klasifikasi);
}

void LihatPasien(dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    dataAkun daPrint, daFilter;
    char filter[50];
    char urutan[50];
    char klasifikasi[50];

    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    // Set filter untuk role pasien saja
    strcpy(filter, "pasien");
    // Salin data akun ke data akun filter pasien saja
    daFilter = Filter(*da, filter);

    // Jika manager maka keluar MENU
    int pilihan_1, pilihan_2;
    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Username\n");
    printf(">>> Pilihan: ");
    for (;;)
    {
        scanf("%d", &pilihan_1);
        flushInput();
        if (pilihan_1 == 1 || pilihan_1 == 2)
            break;
        else
            printf("Pilihan tidak valid!\n");
    }

    // Urutkan berdasarkan ID
    if (pilihan_1 == 1)
    {
        printf("Urutan sort?\n");
        printf("1. ASC (Urutkan naik)\n");
        printf("2. DSC (Urutkan turun)\n");
        printf(">>> Pilihan: ");
        for (;;)
        {
            scanf("%d", &pilihan_2);
            flushInput();
            if (pilihan_2 == 1 || pilihan_2 == 2)
                break;
            else
                printf("Pilihan tidak valid!\n");
        }
        // Urutkan ASC
        if (pilihan_2 == 1)
        {
            daPrint = SortAscID(daFilter);
            strcpy(urutan, "ascending");
            strcpy(klasifikasi, "ID");
        }
        // Urutkan DSC
        else if (pilihan_2 == 2)
        {
            daPrint = SortDscID(daFilter);
            strcpy(urutan, "descending");
            strcpy(klasifikasi, "ID");
        }
    }

    // Urutkan berdasarkan Username
    else if (pilihan_1 == 2)
    {
        printf("Urutan sort?\n");
        printf("1. ASC (A-Z)\n");
        printf("2. DSC (Z-A)\n");
        printf(">>> Pilihan: ");
        for (;;)
        {
            scanf("%d", &pilihan_2);
            flushInput();
            if (pilihan_2 == 1 || pilihan_2 == 2)
                break;
            else
                printf("Pilihan tidak valid!\n");
        }
        // Urutkan ASC
        if (pilihan_2 == 1)
        {
            daPrint = SortAscUN(daFilter);
            strcpy(urutan, "ascending");
            strcpy(klasifikasi, "username");
        }
        // Urutkan DSC
        else if (pilihan_2 == 2)
        {
            daPrint = SortDscUN(daFilter);
            strcpy(urutan, "descending");
            strcpy(klasifikasi, "username");
        }
    }

    // Print
    TampilkanDataPasien(daPrint, urutan, klasifikasi);
}

void LihatDokter(dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    dataAkun daPrint, daFilter;
    char filter[50];
    char urutan[50];
    char klasifikasi[50];

    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silahkan log in terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }
    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    // Set filter untuk role pasien saja
    strcpy(filter, "dokter");
    // Salin data akun ke data akun filter pasien saja
    daFilter = Filter(*da, filter);

    // Jika manager maka keluar MENU
    int pilihan_1, pilihan_2;
    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n");
    printf("2. Username\n");
    printf(">>> Pilihan: ");
    for (;;)
    {
        scanf("%d", &pilihan_1);
        flushInput();
        if (pilihan_1 == 1 || pilihan_1 == 2)
            break;
        else
            printf("Pilihan tidak valid!\n");
    }

    // Urutkan berdasarkan ID
    if (pilihan_1 == 1)
    {
        printf("Urutan sort?\n");
        printf("1. ASC (Urutkan naik)\n");
        printf("2. DSC (Urutkan turun)\n");
        printf(">>> Pilihan: ");
        for (;;)
        {
            scanf("%d", &pilihan_2);
            flushInput();
            if (pilihan_2 == 1 || pilihan_2 == 2)
                break;
            else
                printf("Pilihan tidak valid!\n");
        }
        // Urutkan ASC
        if (pilihan_2 == 1)
        {
            daPrint = SortAscID(daFilter);
            strcpy(urutan, "ascending");
            strcpy(klasifikasi, "ID");
        }
        // Urutkan DSC
        else if (pilihan_2 == 2)
        {
            daPrint = SortDscID(daFilter);
            strcpy(urutan, "descending");
            strcpy(klasifikasi, "ID");
        }
    }

    // Urutkan berdasarkan Username
    else if (pilihan_1 == 2)
    {
        printf("Urutan sort?\n");
        printf("1. ASC (A-Z)\n");
        printf("2. DSC (Z-A)\n");
        printf(">>> Pilihan: ");
        for (;;)
        {
            scanf("%d", &pilihan_2);
            flushInput();
            if (pilihan_2 == 1 || pilihan_2 == 2)
                break;
            else
                printf("Pilihan tidak valid!\n");
        }
        // Urutkan ASC
        if (pilihan_2 == 1)
        {
            daPrint = SortAscUN(daFilter);
            strcpy(urutan, "ascending");
            strcpy(klasifikasi, "username");
        }
        // Urutkan DSC
        else if (pilihan_2 == 2)
        {
            daPrint = SortDscUN(daFilter);
            strcpy(urutan, "descending");
            strcpy(klasifikasi, "username");
        }
    }

    // Print
    TampilkanDataDokter(daPrint, urutan, klasifikasi);
}
