# IF1210-Tubes-01-Kelompok M

🏥 Sistem Informasi Rumah Sakit
Program ini dikembangkan oleh kelompok M dari kelas K01 IF1210 Algoritma & Pemrograman 1 2025 dengan rincian anggota:
| Nama                           | NIM      |
| ------------------------------ | -------- |
| Jonathan Kris Wicaksono        | 13524023 |
| Mikhael Andrian Y.             | 13524051 |
| Alya Nur Rahmah                | 13524081 |
| Vara Azzara Ramli P.           | 13524091 |
| Reinsen Silitonga              | 13524093 |
| Helena Kristela S.             | 13524109 |

📖 Deskripsi Proyek
Sistem Informasi Rumah Sakit ini dirancang untuk mendukung operasional rumah sakit dengan menyediakan fitur-fitur utama bagi tiga peran pengguna: Manajer, Dokter, dan Pasien. Setiap peran memiliki akses ke fitur-fitur yang sesuai dengan kebutuhan mereka untuk memastikan kelancaran proses administrasi dan pelayanan medis.

⚙️ Fitur Utama
🔐 Autentikasi & Manajemen Akun
Login: Dilakukan oleh seluruh pengguna untuk mengakses fitur yang tersedia.

Register: Hanya untuk pasien baru yang ingin mendaftar.

Logout: Keluar dari sistem.

Update Password: Mengubah kata sandi akun.

🧭 Navigasi & Bantuan
Menu & Help: Menampilkan daftar fitur yang tersedia dan panduan pengguna.

🏥 Manajemen Rumah Sakit
Denah Rumah Sakit: Menampilkan denah ruangan di rumah sakit serta detail dari ruangan.

Lihat Data Pengguna: Menampilkan data pengguna terdaftar (hanya untuk manajer).

Cari Data Pengguna: Pencarian data pengguna berdasarkan ID atau nama (hanya untuk manajer).

Lihat Ruangan Tidak Kosong: Menampilkan rincian seluruh ruangan yang tidak kosong (hanya untuk manajer).

Tambah Dokter: Penambahan dokter baru dan melakukan assign ke ruangan (hanya untuk manajer).

Ubah Denah: Memanipulasi ukuran denah rumah sakit

🩺 Fitur Dokter
Diagnosis: Pengecekan penyakit pasien (hanya untuk dokter).

Ngobatin: Pemberian obat pada pasien (hanya untuk dokter).

🧑‍⚕️ Fitur Pasien
Validasi Pulang: Validasi apakah pasien sudah siap untuk pulang (hanya untuk pasien).

Daftar Check-Up: Mendaftar untuk pemeriksaan (hanya untuk pasien).

Status Antrian: Menampilkan status antrian (hanya untuk pasien yang sudah melakukan pendaftaran).

Skip Antrian: Membuat seorang pasien menjadi antrian terdepan

Cancel Antrian: Keluar dari antrian

Minum Obat: Meminum obat (hanya untuk pasien).

Minum Penawar: Meminum penawar (hanya untuk pasien).

💾 Manajemen Data
Load: Memuat data dari file eksternal.

Save: Menyimpan data ke file eksternal.

Exit: Keluar dari program.

🧱 Struktur Data & Implementasi ADT
Proyek ini menggunakan berbagai Abstract Data Types (ADT) untuk mengelola data secara efisien dan modular:

ADT List: Digunakan untuk menyimpan data pengguna, ruangan, dan lainnya yang bersifat dinamis.

ADT Set: Untuk memastikan keunikan data seperti username.

ADT Map: Mengaitkan key dengan value, seperti ID dengan data pengguna.

ADT Queue: Mengelola antrian pasien secara FIFO.

ADT Stack: Mengelola data yang bersifat LIFO, seperti urutan obat yang diminum.

ADT Matrix: Merepresentasikan denah rumah sakit dalam bentuk grid 2D.

ADT Linked List: Struktur dasar untuk queue dan pengelolaan data dinamis lainnya.

ADT Sederhana: Tipe bentukan seperti Akun, Penyakit, Obat, dan Ruangan.

Setiap fitur dalam sistem ini diimplementasikan dengan kombinasi ADT yang sesuai untuk memastikan efisiensi dan modularitas kode.

🛠️ Cara Menjalankan Program
1. Pastikan Anda memiliki compiler C (seperti GCC) terinstal.

2. Klon repositori ini ke terminal (disarankan WSL)

3. Masuk ke direktori proyek:
cd if1210-tubes-2025-k01-m/src

4. Kompilasi program di terminal:
make

5. Jalankan program:
./main
