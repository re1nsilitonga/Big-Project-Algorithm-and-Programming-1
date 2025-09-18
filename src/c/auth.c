#include "auth.h"

// Menghapus karakter newline di akhir string input.
void stripNewline(char *input)
{
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }
}

// Mengabaikan karakter '\n' pada input buffer.
void flushInput()
{
    while (getchar() != '\n' && !feof(stdin))
        ;
}

/*
 * login
 * -----
 * Melakukan proses login user dengan validasi username dan password.
 * Jika berhasil, data user aktif akan diisi.
 */
void login(dataAkun *da, Akun *CurrentUser, boolean *isLogin)
{
    // Sudah login atau belum
    if (*isLogin)
    {
        printf("Tidak bisa login karena anda sudah login!\n");
        return;
    }
    // Menerima input pengguna berupa string dari username dan password
    char inputUsername[50], inputPassword[50];
    boolean usernameFound = false;

    printf("=== Login ===\n");
    printf("Username: ");
    scanf("%s", inputUsername);
    stripNewline(inputUsername);
    printf("Password: ");
    scanf("%s", inputPassword);
    while (getchar() != '\n' && !feof(stdin))
        ;

    // Menelusuri secara traversal array da.data
    for (int i = 0; i < da->jumlah; i++)
    {
        // validasi input username terhadap username terdaftar
        if (strcmp(da->data[i].Username, inputUsername) == 0)
        {
            usernameFound = true;
            // Jika sername sesuai maka lanjut validasi password
            if (strcmp(da->data[i].Password, inputPassword) == 0)
            {
                *isLogin = 1;
                *CurrentUser =
                    da->data[i];
                char capUsername[50];
                strcpy(capUsername, CurrentUser->Username);
                capitalizeCommand(capUsername);
                printf("Login berhasil! Halo, %s (%s)!\n",
                       capUsername, CurrentUser->Role);
                return;
            }
            else
            {
                char capUsername[50];
                strcpy(capUsername, da->data[i].Username);
                capitalizeCommand(capUsername);
                // Jika password tidak sesuai maka berikan pesan kesalahan
                printf("Password salah untuk pengguna %s!\n",
                       capUsername);
                return;
            }
        }
    }
    // Jika user tidak ditemukan berikan pesan
    if (!usernameFound)
    {
        printf("Username tidak ditemukan!\n");
    }
}

/*
 * logout
 * ----__
 * Melakukan proses logout user aktif.
 */
void logout(Akun *CurrentUser, boolean *isLogin)
{
    // Validasi apakah pengguna sudah log in
    if (*isLogin == false)
    {
        printf("Anda belom login!\n");
        return;
    }
    // Pengguna sudah log in maka proses logout dan set CurrentUser ke akun kosong
    memset(CurrentUser, 0, sizeof(Akun));

    *isLogin = false;

    printf("Logout berhasil! Sampai jumpa!\n");
}

/*
 * registerAccount
 * --------------
 * Menambahkan akun baru ke data akun dan map akun.
 */
void registerAccount(dataAkun *da, MapAkun *akunMap, Akun *akun)
{
    insertLastAkun(da, *akun);
    insertMapAkun(akunMap, akun->Id, akun);
}

// Fungsi mengubah char kapital menjadi char kecil
char toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + ('a' - 'A');
    }
    return c;
}

// Prosedur mengubah string yang mengandung char kapital menjadi char kecil
void toLowerString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = toLower(str[i]);
    }
}

// Fungsi cek apakah suatu string mengandung angka
int containsNumber(const char *str)
{
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
            return 1;
    }
    return 0;
}

/*
 * regist
 * ----__
 * Melakukan proses registrasi akun baru untuk pasien.
 */
void regist(dataAkun *da, MapAkun *akunMap, boolean isLogin)
{
    // Jika pengguna sudah login maka tidak bisa register
    if (isLogin)
    {
        printf("Anda tidak bisa melakukan registrasi karena sudah login! Silahkan log out terlebih dahulu.\n");
        return;
    }
    // Pengguna belum login maka membaca input pengguna
    char username[100], password[100];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    flushInput();

    // Inisialisasi set
    Set st;
    createSet(&st, 100);
    // Username dari array load dataAkun di copy ke dalam set
    for (int i = 0; i < da->jumlah; i++)
    {
        char lower[100];
        strcpy(lower, da->data[i].Username);
        toLowerString(lower);  // Case insensitive (menjadi huruf kecil semua)
        insertSet(&st, lower); // Ditambahkan ke set apabila username bersifat unik sehingga tidak ada yang sama
    }

    // Apabila mengandung angka maka tidak bisa register
    if (containsNumber(username))
    {
        printf("Username tidak boleh mengandung angka! Silahkan coba yang lain.\n");
        freeSet(&st);
        return;
    }

    char usernameLower[100];
    strcpy(usernameLower, username);
    toLowerString(usernameLower); // Input pengguna diubah menjadi huruf kecil semua

    // Validasi apabila di dalam set sudah ada username yang sama dengan input pengguna
    if (containsSet(&st, usernameLower)) // Jika ada yang sama
    {
        printf("Registrasi gagal! Username %s sudah digunakan. Silakan coba yang lain.\n", username);
        freeSet(&st);
        return;
    }

    // Jika belum ada tambahkan ke array dataAkun
    Akun akunBaru;
    initAkun(&akunBaru);
    int maxId = 0;
    for (int i = 0; i < da->jumlah; i++)
    {
        if (da->data[i].Id > maxId)
        {
            maxId = da->data[i].Id;
        }
    }
    akunBaru.Id = maxId + 1;
    strcpy(akunBaru.Username, username);
    strcpy(akunBaru.Password, password);
    strcpy(akunBaru.Role, "pasien");
    registerAccount(da, akunMap, &akunBaru);
    printf("Registrasi berhasil! Pasien ");
    char capUsername[100];
    strcpy(capUsername, username);
    capitalizeCommand(capUsername);
    printf("%s telah ditambahkan.\n", capUsername);
    freeSet(&st);
}

/*
 * TambahDokter
 * ------------
 * Menambahkan akun dokter baru (hanya dapat diakses oleh manager).
 */
void TambahDokter(dataAkun *da, MapAkun *akunMap, Akun *CurrentUser, boolean isLogin)
{
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
    // Jika manager maka membaca input pengguna
    char username[100], password[100];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    flushInput();

    // Inisialisasi set
    Set st;
    createSet(&st, 100);
    // Username dari array load dataAkun di copy ke dalam set
    for (int i = 0; i < da->jumlah; i++)
    {
        char lower[100];
        strcpy(lower, da->data[i].Username);
        toLowerString(lower);  // Case insensitive (menjadi huruf kecil semua)
        insertSet(&st, lower); // Ditambahkan ke set apabila username bersifat unik sehingga tidak ada yang sama
    }

    // Apabila mengandung angka maka tidak bisa register
    if (containsNumber(username))
    {
        printf("Username tidak boleh mengandung angka! Silahkan coba yang lain.\n");
        freeSet(&st);
        return;
    }

    char usernameLower[100];
    strcpy(usernameLower, username);
    toLowerString(usernameLower); // Input pengguna diubah menjadi huruf kecil semua

    // Validasi apabila di dalam set sudah ada username yang sama dengan input pengguna
    if (containsSet(&st, usernameLower)) // Jika ada yang sama
    {
        printf("Registrasi gagal! Username %s sudah digunakan. Silakan coba yang lain.\n", username);
        freeSet(&st);
        return;
    }

    // Jika belum ada tambahkan ke array dataAkun
    Akun akunBaru;
    initAkun(&akunBaru);
    int maxId = 0;
    for (int i = 0; i < da->jumlah; i++)
    {
        if (da->data[i].Id > maxId)
        {
            maxId = da->data[i].Id;
        }
    }
    akunBaru.Id = maxId + 1;
    strcpy(akunBaru.Username, username);
    strcpy(akunBaru.Password, password);
    strcpy(akunBaru.Role, "dokter");
    registerAccount(da, akunMap, &akunBaru);
    printf("Registrasi berhasil! Dokter ");
    char capUsername2[100];
    strcpy(capUsername2, username);
    capitalizeCommand(capUsername2);
    printf("%s telah ditambahkan.\n", capUsername2);
    freeSet(&st);
}

void AssignDokter(Denah *hospital, dataAkun *da, Akun *CurrentUser, boolean isLogin)
{
    // Jika pengguna belum login maka tidak bisa akses
    if (!(isLogin))
    {
        printf("Silakan login terlebih dahulu untuk mengakses menu ini.\n");
        return;
    }

    // Jika pengguna sudah log in maka perlu validasi role
    if (strcmp(CurrentUser->Role, "manager") != 0)
    { // Bukan manager
        printf("Menu ini hanya dapat diakses oleh manager!\n");
        return;
    }

    // Jika manager maka membaca input pengguna
    char username[100], ruangan[100];
    int ID;
    printf("Username: ");
    scanf("%s", username);
    printf("Ruangan: ");
    scanf("%s", ruangan);
    flushInput();

    // Validasi bahwa username terdaftar di dataAkun dan role dokter
    boolean isDokterValid = false;
    for (int i = 0; i < da->jumlah; i++)
    {
        if (strcmp(da->data[i].Username, username) == 0 && strcmp(da->data[i].Role, "dokter") == 0)
        {
            ID = da->data[i].Id;
            isDokterValid = true;
            break;
        }
    }
    if (!(isDokterValid))
    { // Tidak tepat maka pesan kesalahan
        printf("Username %s tidak ditemukan atau bukan dokter!\n", username);
        return;
    }

    // Konversi ruangan A1 -> indeks
    int baris = ruangan[0] - 'A';
    int kolom = atoi(&ruangan[1]) - 1;

    // Validasi apakah ruangan valid
    if (baris < 0 || baris >= hospital->panjang || kolom < 0 || kolom >= hospital->lebar)
    {
        printf("Ruangan %s tidak valid!\n", ruangan);
        return;
    }

    // Cek apakah dokter input sudah diassign ke ruangan lain
    char CurrentRuangan[12];
    boolean dokterSudahDiassign = false;
    // Menelusuri seluruh "ruangan" untuk mengecek dokter yang ada di ruangan
    for (int i = 0; i < hospital->panjang; i++)
    {
        for (int j = 0; j < hospital->lebar; j++)
        {
            if (hospital->grid[i][j].dokter != NULL && strcmp(hospital->grid[i][j].dokter->Username, username) == 0)
            {
                sprintf(CurrentRuangan, "%c%d", 'A' + i, j + 1);
                dokterSudahDiassign = true;
                break;
            }
        }
        if (dokterSudahDiassign)
            break;
    }

    // Cek apakah ruangan input sudah diisi dokter lain
    boolean ruanganSudahTerisi = ((hospital->grid[baris][kolom].dokter != NULL) && (strlen(hospital->grid[baris][kolom].dokter->Username) > 0)); // Ada dokter
    char *CurrentDokter = (hospital->grid[baris][kolom].dokter != NULL) ? hospital->grid[baris][kolom].dokter->Username : "(kosong)";

    if (dokterSudahDiassign && ruanganSudahTerisi) // Dokter input sudah diassign dan ruangan input sudah ada dokter lain
    {
        char capUsername[100], capCurrentDokter[100];
        strcpy(capUsername, username);
        strcpy(capCurrentDokter, CurrentDokter);
        capitalizeCommand(capUsername);
        capitalizeCommand(capCurrentDokter);
        printf("Dokter %s sudah menempati ruangan %s!\n", capUsername, CurrentRuangan);
        printf("Ruangan %s juga sudah ditempati dokter %s!\n", ruangan, capCurrentDokter);
    }
    else if (dokterSudahDiassign) // Dokter input sudah diassign tapi ruangan input kosong
    {
        char capUsername[100];
        strcpy(capUsername, username);
        capitalizeCommand(capUsername);
        printf("Dokter %s sudah diassign ke ruangan %s!\n", capUsername, CurrentRuangan);
    }
    else if (ruanganSudahTerisi) // Ruangan input terisi tapi dokter input belum diassign
    {
        char capCurrentDokter[100], capUsername[100];
        strcpy(capCurrentDokter, CurrentDokter);
        strcpy(capUsername, username);
        capitalizeCommand(capCurrentDokter);
        capitalizeCommand(capUsername);
        printf("Dokter %s sudah menempati ruangan %s!\n", capCurrentDokter, ruangan);
        printf("Silakan cari ruangan lain untuk dokter %s.\n", capUsername);
    }
    else // Ruangan input kosong dan dokter input belum diassign
    {
        if (hospital->grid[baris][kolom].dokter == NULL)
        {
            hospital->grid[baris][kolom].dokter = malloc(sizeof(Akun));
        }
        strcpy(hospital->grid[baris][kolom].dokter->Username, username);
        strcpy(hospital->grid[baris][kolom].dokter->Role, "dokter");
        hospital->grid[baris][kolom].dokter->Id = ID;
        char capUsername[100];
        strcpy(capUsername, username);
        capitalizeCommand(capUsername);
        printf("Dokter %s berhasil diassign ke ruangan %s!\n", capUsername, ruangan);
    }
}

/*
 * help
 * ----
 * Menampilkan daftar command yang dapat diakses user sesuai role.
 */
void help(Akun *akun, boolean *isLogin)
{
    // Validasi isLogin
    if (!*isLogin) // Belum login
    {
        printf("=========== HELP ===========\n\n");
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("REGISTER: Membuat akun baru\n");
    }
    else // Sudah login
    {
        printf("=========== HELP ===========\n\n");
        char capUsername[100];
        strcpy(capUsername, akun->Username);
        capitalizeCommand(capUsername);

        // Validasi role
        if (strcmp(akun->Role, "dokter") == 0) // Role dokter
        {
            printf("Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", capUsername);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LUPA_PASSWORD        : Untuk reset password akun\n");
            printf("LIHAT_DENAH          : Melihat denah rumah sakit\n");
            printf("LIHAT_RUANGAN <kode> : Melihat detail ruangan berdasarkan kode\n");
            printf("DIAGNOSIS            : Melakukan diagnosis pasien\n");
            printf("NGOBATIN             : Melakukan proses pengobatan pasien\n");
            printf("SAVE                 : Menyimpan data ke folder\n");
            printf("EXIT                 : Keluar dari aplikasi\n");
            printf("LOGOUT               : Keluar dari akun yang sedang digunakan\n");
        }
        else if (strcmp(akun->Role, "manager") == 0) // Role manager
        {
            printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan.\n", capUsername);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LUPA_PASSWORD                         : Untuk reset password akun\n");
            printf("LIHAT_DENAH                           : Melihat denah rumah sakit\n");
            printf("LIHAT_RUANGAN <kode>                  : Melihat detail ruangan berdasarkan kode\n");
            printf("UBAH_DENAH <rows> <cols>              : Mengubah ukuran denah rumah sakit\n");
            printf("PINDAH_DOKTER <kodeAsal> <kodeTujuan> : Memindahkan dokter antar ruangan\n");
            printf("TAMBAH_DOKTER                         : Menambahkan dokter baru\n");
            printf("ASSIGN_DOKTER                         : Menugaskan dokter ke ruangan\n");
            printf("LIHAT_SEMUA_ANTRIAN                   : Melihat antrian pasien\n");
            printf("LIHAT_USER                            : Melihat daftar akun user\n");
            printf("CARI_USER                             : Mencari akun user berdasarkan ID\n");
            printf("SAVE                                  : Menyimpan data ke folder\n");
            printf("EXIT                                  : Keluar dari aplikasi\n");
            printf("LOGOUT                                : Keluar dari akun yang sedang digunakan\n");
        }
        else // Role pasien
        {
            printf("Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", capUsername);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n");
            printf("LUPA_PASSWORD        : Untuk reset password akun\n");
            printf("LIHAT_DENAH          : Melihat denah rumah sakit\n");
            printf("LIHAT_RUANGAN <kode> : Melihat detail ruangan berdasarkan kode\n");
            printf("ANTRIAN              : Melihat status antrian Anda\n");
            printf("DAFTAR_CHECKUP       : Melakukan pendaftaran check-up\n");
            printf("MINUM_OBAT           : Meminum obat di inventory\n");
            printf("PENAWAR              : Mengeluarkan kembali obat di perut ke inventory\n");
            printf("PULANG_DOK           : Proses pulang pasien dari rumah sakit\n");
            printf("CANCEL_ANTRIAN       : Membatalkan antrian check-up\n");
            printf("SKIP_ANTRIAN         : Maju ke depan antrian check-up\n");
            printf("SAVE                 : Menyimpan data ke folder\n");
            printf("EXIT                 : Keluar dari aplikasi\n");
            printf("LOGOUT               : Keluar dari akun yang sedang digunakan\n");
        }
    }
    printf("\nFootnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}

/*
 * forgotPassword
 * --------------
 * Proses reset password dengan validasi kode unik.
 */
void forgotPassword(dataAkun *da, Akun *CurrentUser, boolean *isLogin)
{
    if (*isLogin)
    {
        printf("Anda tidak bisa melakukan ini karena sudah login! Silahkan log out terlebih dahulu.\n");
        return;
    }

    // Jika pengguna belum login maka membaca input pengguna
    char username[100], password[100], kodeUnik[200], kodeUnikInput[200];
    boolean usernameFound = false;

    // Membaca input pengguna
    printf("Username: ");
    scanf("%99s", username);
    flushInput();

    // Generate kode unik menggunakan Run-Length Encoding
    int len = strlen(username);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        int count = 1;
        while (i + 1 < len && username[i] == username[i + 1])
        {
            count++;
            i++;
        }
        if (count > 1)
        {
            index += sprintf(&kodeUnik[index], "%d", count);
        }
        kodeUnik[index++] = username[i];
    }
    kodeUnik[index] = '\0';

    // Cek apakah username sudah terdaftar
    for (int i = 0; i < da->jumlah; i++)
    {
        if (strcmp(da->data[i].Username, username) == 0)
        {
            usernameFound = true;
            break;
        }
    }

    // Jika belum terdaftar, tampilkan pesan usernamen tidak terdaftar
    if (!usernameFound)
    {
        printf("Username tidak terdaftar!\n");
        return;
    }

    // Membaca kode unik dari pengguna
    printf("Masukkan Kode Unik: ");
    scanf("%199s", kodeUnikInput);
    flushInput();

    // Verifikasi kode unik
    if (strcmp(kodeUnik, kodeUnikInput) != 0)
    {
        printf("Kode unik salah!\n");
        return;
    }

    // Cari username di dataAkun
    for (int i = 0; i < da->jumlah; i++)
    {
        if (strcmp(da->data[i].Username, username) == 0)
        {
            const char *roleDia;
            if (strcmp(da->data[i].Role, "dokter") == 0)
            {
                roleDia = "Dokter";
            }
            else if (strcmp(da->data[i].Role, "manager") == 0)
            {
                roleDia = "Manager";
            }
            else
            {
                roleDia = "Pasien";
            }

            char capUsername[100];
            strcpy(capUsername, da->data[i].Username);
            capitalizeCommand(capUsername);

            printf("\nHalo %s %s, silakan daftarkan ulang password anda!\n",
                   roleDia, capUsername);

            printf("Password Baru: ");
            scanf("%99s", password);
            flushInput();

            // Update password untuk akun yang ditemukan
            strcpy(da->data[i].Password, password);
            return;
        }
    }
}

