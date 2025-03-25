# Sim Perpus - Console

**Sim Perpus** adalah sebuah program berbasis teks untuk mengelola sistem perpustakaan sederhana, termasuk fitur manajemen buku, anggota, dan peminjaman. 
Aplikasi SIM Perpus ini sengaja dibuat sebagai bahan pembelajaran bagi siswa/mahasiswa yang sedang mengambil mata kuliah Algoritma dan Dasar pemrograman.
Dengan mengamati, meniru dan memodifikasi program ini, diharapkan kemampuan siswa/mahasiswa bisa meningkat pesat, khusunya dalam hal menguasai materi algoritma dan dasar pemrograman.

## Cara Instalasi

1. Pastikan Anda memiliki **GCC** dan **libnewt** terinstal.
   ```sh
   sudo apt install gcc libnewt-dev
   ```
2. Clone repository ini:
   ```sh
   git clone https://github.com/username/sim_perpus.git
   cd sim_perpus
   ```
3. Jalankan perintah **make** untuk membangun program:
   ```sh
   make
   ```
4. Jika berhasil, file **sim_perpus** akan dibuat.

## Cara Penggunaan

1. Jalankan program dengan perintah:
   ```sh
   ./sim_perpus
   ```
2. Pilih menu yang tersedia:
   - **Entry Buku**: Tambah atau perbarui data buku.
   - **Entry Anggota**: Tambah atau perbarui data anggota perpustakaan.
   - **Transaksi Pinjam**: Catat transaksi peminjaman buku.
   - **Transaksi Kembali**: Catat transaksi pengembalian buku.
3. Gunakan tombol navigasi untuk memilih dan mengedit data.

## Pembersihan
Jika ingin menghapus file hasil kompilasi:
```sh
make clean
```

## Kontribusi
Silakan buat pull request atau buka issue jika ingin berkontribusi dalam pengembangan aplikasi ini.

## Lisensi
Proyek ini menggunakan lisensi **MIT**.
