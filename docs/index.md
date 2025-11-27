# Dokumen Desain Game: [Nama Proyek]

## 1. Gambaran Umum
**Konsep:** [Jelaskan ide utama permainan dalam satu kalimat. Contoh: "Sebuah game platformer 2D di mana pemain mengontrol kucing yang mencari jalan pulang."]
**Tujuan:** [Jelaskan tujuan akhir pemain. Contoh: "Mencapai akhir level tanpa kehabisan nyawa."]

## 2. MVP (Minimum Viable Product)
Bagian ini mendefinisikan versi paling sederhana dari game yang bisa dimainkan.

### Alur Permainan Inti (Core Loop)
1.  **Mulai:** [Bagaimana permainan dimulai?]
2.  **Aksi:** [Apa yang dilakukan pemain secara berulang? (Lari, Lompat, Tembak)]
3.  **Umpan Balik:** [Bagaimana game merespons aksi tersebut? (Musuh hancur, Skor naik)]
4.  **Kondisi Akhir:** [Kapan permainan dianggap selesai atau gagal?]

### Persyaratan MVP
*Daftar fitur wajib agar game bisa dimainkan:*
-   [ ]  [Fitur Utama 1: misal, Input Pemain]
-   [ ]  [Fitur Utama 2: misal, Logika Musuh Sederhana]
-   [ ]  [Fitur Utama 3: misal, Sistem Skor]
-   [ ]  [Fitur Utama 4: misal, Tampilan Visual Dasar]

## 3. Fitur Lengkap

### 3.1 Mekanisme Permainan (Gameplay)
*   **Kontrol Pemain:** [Jelaskan detail kontrol. Tombol apa melakukan apa?]
*   **Musuh/AI:** [Jelaskan tipe musuh dan bagaimana mereka berperilaku.]
*   **Desain Level:** [Jelaskan struktur level. Apakah acak atau didesain manual?]
*   **Sistem Progresi:** [Apakah ada level up, unlock item, atau high score?]

### 3.2 Antarmuka Pengguna (UI)
*   **Menu:** [Daftar layar menu yang dibutuhkan (Main Menu, Pause, Settings).]
*   **HUD (Heads-Up Display):** [Informasi apa yang selalu terlihat di layar saat bermain? (Nyawa, Skor, Waktu).]

### 3.3 Audio
*   **Musik:** [Jenis musik latar yang dibutuhkan.]
*   **SFX:** [Daftar efek suara penting (Langkah kaki, Ledakan, UI click).]

## 4. Arsitektur Teknis

### 4.1 Tech Stack
*   **Bahasa:** C++
*   **Library/Framework:** [Sebutkan library yang dipakai (SDL2, Raylib, SFML, atau murni Console).]
*   **Tools:** [Compiler, IDE, atau tools lain yang digunakan.]

### 4.2 Struktur Kelas (Rencana)
*   `[NamaKelas]`: [Deskripsi tanggung jawab kelas ini.]
*   `[NamaKelas]`: [Deskripsi tanggung jawab kelas ini.]
*   `[NamaKelas]`: [Deskripsi tanggung jawab kelas ini.]

## 5. Peta Jalan (Roadmap)
*Urutan pengerjaan fitur dari yang terpenting.*
1.  [ ] [Langkah 1: Setup Proyek]
2.  [ ] [Langkah 2: Implementasi Core Loop]
3.  [ ] [Langkah 3: Implementasi Fitur Tambahan]
4.  [ ] [Langkah 4: Polishing & Bugfix]