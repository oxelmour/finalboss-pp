# Dokumen Desain Game: The Maze

## 1. Gambaran Umum
**Konsep:** 
Sebuah Game Berbasis TUI atau disebut juga Terminal Text UI dimana pemain harus menyelesaikan sebuah tantangan berupa labirin

**Tujuan:** Jika ingin menyelesaikan Game ini maka harus menyelesaikan labirin terlebih dahulu :)

## 2. MVP (Minimum Variable Product)
Bagian ini mendefinisikan versi paling sederhana dari game yang bisa dimainkan.

### Alur Permainan Inti (Core Loop)
1.  **Mulai:** permainan di mulai dari start area
2.  **Aksi:** mencari jalan menggunakan arrow key atau menggunakan [W,A,S,D] untuk menggerakkan player ke atas ,bawah,kiri ,dan kanan
3.  **Kondisi Akhir:** permainan di anggap selesai jika player berhasil menyelesaikan labirin

### Persyaratan MVP
*Daftar fitur wajib agar game bisa dimainkan:*
-   [ ] **Inisialisasi Ncurses:** Inisialisasi screen, raw mode, keypad, dan noecho.
-   [ ] **Membuat Map:** Representasi labirin (Array 2D / Vector) dengan dinding (`#`) dan jalan (` `).
-   [ ] **Menampilkan Player:** Menampilkan karakter pemain (misal: `@`) di posisi awal.
-   [ ] **Movement & Collision:** Logika gerak (WASD/Arrow) yang mengecek dinding sebelum update posisi.
-   [ ] **Exit Logic:** Deteksi jika pemain mencapai titik finish (misal: `X`) dan menampilkan pesan menang.


