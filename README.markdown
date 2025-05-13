# MediTrack: Inventory & Expiry Analyzer

Selamat datang di **MediTrack**! Ini adalah program sederhana yang dirancang untuk membantu apotek atau tempat penyimpanan obat mengelola stok obat dengan lebih mudah. Program ini memungkinkan Anda menambahkan obat, melihat daftar obat, memeriksa obat yang akan segera kadaluwarsa, dan mengelola permintaan obat. Semuanya dilakukan melalui terminal/CLI dengan tampilan yang rapi dan mudah digunakan.

Proyek ini dibuat oleh tim kami sebagai bagian dari tugas atau proyek pembelajaran. Kami fokus membuat program yang berguna, sederhana, dan estetik, sehingga siapa saja bisa menggunakannya dengan nyaman.

## Apa Itu MediTrack?

MediTrack adalah alat manajemen inventori obat berbasis teks yang membantu:
- Menyimpan daftar obat beserta stok dan tanggal kadaluwarsa.
- Menemukan obat yang akan segera kadaluwarsa agar tidak terbuang sia-sia.
- Mengatur permintaan obat dari pengguna (misalnya, pasien atau petugas) secara teratur.
- Memberikan antarmuka pengguna yang bersih dan mudah dipahami.

Program ini menggunakan teknik pemrograman tingkat lanjut seperti daftar terkait (linked list), tumpukan minimum (min heap), dan antrian (queue) untuk mengelola data dengan efisien.

## Fitur Utama

MediTrack memiliki beberapa fitur utama yang dirancang untuk memudahkan pengguna:

1. **Tambah Obat**:
   - Anda bisa menambahkan obat baru ke dalam sistem dengan memasukkan nama, jumlah stok, dan tanggal kadaluwarsa.
2. **Lihat Semua Obat**:
   - Lihat daftar lengkap semua obat yang tersimpan, termasuk stok dan tanggal kadaluwarsa, dalam bentuk tabel yang rapi.
3. **Lihat Obat Terdekat Kadaluwarsa**:
   - Temukan obat yang akan segera kadaluwarsa untuk di prioritaskan penggunaannya.
4. **Tambah Permintaan Obat**:
   - Tambahkan permintaan obat oleh pengguna, misalnya jika ada yang membutuhkan obat tertentu dalam jumlah tertentu.
5. **Proses Permintaan Obat**:
   - Proses permintaan yang masuk dan kurangi stok obat secara otomatis.
6. **Keluar**:
   - Akhiri program dengan rapi dan bersihkan semua data sementara dari memori komputer.

**Fitur Tambahan**:
- **Efek Loading**: Saat program dimulai, ada animasi loading sederhana untuk memberikan kesan profesional.
- **Clear Screen**: Layar akan dibersihkan setiap kali Anda memilih menu atau melihat hasil, sehingga tampilan tetap rapi.
- **Desain Estetik**: Menu dan output menggunakan garis pembatas untuk membuatnya enak dilihat tanpa terlalu ramai.

## Struktur Proyek

Proyek ini terdiri dari dua file utama:
- **`meditrack.h`**: File header yang berisi definisi struktur data (seperti obat, antrian, dan tumpukan) serta daftar fungsi yang digunakan. Ini seperti "peta" atau "panduan" untuk program.
- **`meditrack.c`**: File utama yang berisi kode program lengkap, termasuk fungsi-fungsi untuk menjalankan fitur di atas.

Total ada **12 fungsi** dalam program ini, yang dibagi menjadi:
- 3 fungsi untuk tampilan dan pengalaman pengguna (`displayHeader`, `showLoading`, `clearScreen`).
- 3 fungsi untuk mengelola daftar obat (`addMedicine`, `showMedicines`, `updateStock`).
- 3 fungsi untuk melacak kadaluwarsa (`createHeap`, `addToHeap`, `getNearestExpiry`).
- 3 fungsi untuk mengelola permintaan (`createQueue`, `addRequest`, `processRequest`).

Kode ini ditulis dalam bahasa pemrograman **C** karena stabil, cepat, dan cocok untuk proyek seperti ini.

## Cara Instalasi

Untuk menjalankan MediTrack di komputer Anda, ikuti langkah-langkah berikut. Jangan khawatir, kami akan jelaskan dengan sangat detail!

### Prasyarat
- Anda membutuhkan **kompiler C** seperti GCC (GNU Compiler Collection). Jika belum punya, instal terlebih dahulu:
  - **Windows**: Unduh dan instal [MinGW](https://www.mingw-ws.org/) atau [MSYS2](https://www.msys2.org/).
  - **Linux**: Ketik perintah `sudo apt install gcc` di terminal (untuk Ubuntu/Debian) atau sesuaikan dengan distribusi Anda.
  - **Mac**: Instal melalui [Homebrew](https://brew.sh/) dengan perintah `brew install gcc`.
- Pastikan komputer Anda terhubung ke internet untuk mengunduh file jika diperlukan.

### Langkah-langkah Instalasi
1. **Unduh Kode**:
   - Kunjungi repositori GitHub kami di [https://github.com/Nixzouxu/MediTrack](https://github.com/Nixzouxu/MediTrack) (ganti dengan URL repositori Anda).
   - Klik tombol **Code** (hijau) lalu pilih **Download ZIP**. Ekstrak file ZIP ke folder pilihan Anda.
   - Atau, jika Anda tahu cara pakai Git, ketik perintah ini di terminal:
     ```bash
     git clone https://github.com/Nixzouxu/MediTrack.git
     ```
   - Pastikan ada dua file: `meditrack.c` dan `meditrack.h` di folder yang sama.

2. **Kompilasi Program**:
   - Buka terminal atau command prompt.
   - Navigasi ke folder tempat file berada, misalnya:
     ```bash
     cd path/ke/folder/MediTrack
     ```
   - Ketik perintah berikut untuk mengubah kode menjadi program yang bisa dijalankan:
     ```bash
     gcc -o meditrack meditrack.c
     ```
   - Jika tidak ada error (pesan merah), program berhasil dikompilasi. File bernama `meditrack` (atau `meditrack.exe` di Windows) akan dibuat.

3. **Jalankan Program**:
   - Ketik perintah berikut di terminal:
     - Windows: `meditrack.exe`
     - Linux/Mac: `./meditrack`
   - Program akan menampilkan animasi loading, lalu menu utama akan muncul. Selamat, Anda siap menggunakannya!

### Jika Ada Masalah
- Jika muncul error seperti "gcc not found", pastikan kompiler sudah terinstal (lihat prasyarat).
- Jika ada pesan error lain (misalnya, tentang pointer atau tipe data), periksa apakah file `meditrack.h` dan `meditrack.c` sesuai dengan versi terbaru di repositori. Hubungi kami jika perlu bantuan!

## Cara Penggunaan

Setelah program dijalankan, Anda akan melihat tampilan seperti ini:
```
========================================
  MediTrack: Inventory & Expiry Analyzer  
========================================

Pilih Menu:
1. Tambah Obat
2. Lihat Semua Obat
3. Lihat Obat Terdekat Kadaluwarsa
4. Tambah Permintaan Obat
5. Proses Permintaan Obat
6. Keluar

Masukkan pilihan: _
```

### Langkah demi Langkah
1. **Pilih Menu**:
   - Ketik angka 1 sampai 6 sesuai opsi yang Anda inginkan, lalu tekan Enter.
   - Layar akan dibersihkan otomatis untuk menampilkan informasi baru.

2. **Tambah Obat (Pilihan 1)**:
   - Masukkan nama obat (misalnya, "Paracetamol").
   - Masukkan jumlah stok (misalnya, "100").
   - Masukkan tanggal kadaluwarsa (misalnya, "2025-12-31" dalam format YYYY-MM-DD).
   - Tekan Enter setelah setiap input. Program akan konfirmasi bahwa obat berhasil ditambahkan, lalu tunggu dengan menekan Enter lagi untuk kembali ke menu.

3. **Lihat Semua Obat (Pilihan 2)**:
   - Program akan menampilkan tabel dengan kolom: Nama, Stok, dan Kadaluwarsa.
   - Tekan Enter untuk kembali ke menu.

4. **Lihat Obat Terdekat Kadaluwarsa (Pilihan 3)**:
   - Program akan menampilkan nama obat dan tanggal kadaluwarsa terdekat.
   - Jika tidak ada obat, akan muncul pesan "Tidak ada obat di inventori."
   - Tekan Enter untuk kembali.

5. **Tambah Permintaan Obat (Pilihan 4)**:
   - Masukkan nama obat yang diminta (misalnya, "Paracetamol").
   - Masukkan jumlah yang diminta (misalnya, "10").
   - Program akan konfirmasi bahwa permintaan ditambahkan, lalu tekan Enter untuk kembali.

6. **Proses Permintaan Obat (Pilihan 5)**:
   - Program akan mengambil permintaan pertama dan mengurangi stok obat yang sesuai.
   - Jika stok cukup, stok akan diperbarui. Jika tidak ada permintaan, akan muncul pesan.
   - Tekan Enter untuk kembali.

7. **Keluar (Pilihan 6)**:
   - Program akan menutup dengan pesan terima kasih dan membersihkan data sementara.

### Contoh Penggunaan
- Anda memilih opsi 1, lalu masukkan:
  - Nama: "Paracetamol"
  - Stok: "100"
  - Kadaluwarsa: "2025-12-31"
- Pesan: "Obat Paracetamol berhasil ditambahkan."
- Anda memilih opsi 2, lalu lihat:
  ```
  Daftar Inventori:
  ------------------------------------
  Nama            Stok    Kadaluwarsa
  ------------------------------------
  Paracetamol     100     2025-12-31
  ------------------------------------
  ```
- Anda memilih opsi 4, lalu masukkan:
  - Nama: "Paracetamol"
  - Jumlah: "10"
- Pesan: "Permintaan ditambahkan: Paracetamol, Jumlah: 10"
- Anda memilih opsi 5, lalu lihat:
  - Pesan: "Memproses permintaan: Paracetamol, Jumlah: 10"
  - Pesan: "Stok diperbarui: Paracetamol, Stok Baru: 90"

## Pembagian Tim

Muhammad Hafidz
Nayla Nabila Syahel
Syakila Naira
Muhammad Sulthan Shadiq

Terima kasih telah menggunakan MediTrack! Jika ada pertanyaan atau saran, silakan hubungi kami melalui GitHub atau email tim. Semoga sukses!