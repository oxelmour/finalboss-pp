#include <ncurses/curses.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

// Map baru yang lebih besar (Ukuran: 19 Baris x 60 Kolom)
std::vector<std::string> mazeMap = {
    "############################################################",
    "#S      #             #           #              #         #",
    "####### # ########### # ######### # ############ # ####### #",
    "#       # #           # #       # # #            # #     # #",
    "# ####### # ######### # ##### # # # # ########## # # ### # #",
    "# #       # #       # #     # # #   # #          # # #   # #",
    "# # ####### ####### # ##### # # ##### # ######## # # # ### #",
    "# #               # #     # # #       #        # # # #     #",
    "# ############### # ##### # # ####### ######## # # # ##### #",
    "#               # #     # # #       #        # # # #     # #",
    "####### ####### # ##### # # # ##### ######## # # # ##### # #",
    "#       #       #       #   #     #          # # #     # # #",
    "# ####### ####################### ############ # ##### # # #",
    "# #       #                     #              #     # # # #",
    "# # ####### ################### ############## ##### # # # #",
    "# #         #                 #                #     # # # #",
    "# ########### ############### ################## ##### # # #",
    "#             #                                        #   G",
    "############################################################"
};

// fungsi untuk delay ncurses dalam milidetik
void delay_ms(int ms){
    napms(ms);
}

void tampilkanLoadingPage() {
    int rows, cols;

    // dapatkan ukuran layar dan fill ke variabel rows dan cols
    getmaxyx(stdscr, rows, cols);

    const char* title1 = " __  __ _____ _  _______ _____    _  _______ _____   _____ ";
    const char* title2 = "|  \\/  |_   _| |/ /_   _|  __ \\  | |/ /_   _|  __ \\ / ____|";
    const char* title3 = "| \\  / | | | | ' /  | | | |__) | | ' /  | | | |  | | (___  ";
    const char* title4 = "| |\\/| | | | |  <   | | |  _  /  |  <   | | | |  | |\\___ \\ ";
    const char* title5 = "| |  | |_| |_| . \\ _| |_| | \\ \\  | . \\ _| |_| |__| |____) |";
    const char* title6 = "|_|  |_|_____|_|\\_\\_____|_|  \\_\\ |_|\\_\\_____|_____/|_____/ ";

    int judul_start_baris = (rows / 2) - 6;
    int panjang_visual_judul = 63;
    int judul_start_kolom = (cols - panjang_visual_judul) / 2;

    if (judul_start_kolom < 0) judul_start_kolom = 0;
    if (judul_start_baris < 0) judul_start_baris = 0;

    // aktifkan warna dan cetak judul
    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(judul_start_baris, judul_start_kolom, "%s", title1);
    mvprintw(judul_start_baris + 1, judul_start_kolom, "%s", title2);
    mvprintw(judul_start_baris + 2, judul_start_kolom, "%s", title3);
    mvprintw(judul_start_baris + 3, judul_start_kolom, "%s", title4);
    mvprintw(judul_start_baris + 4, judul_start_kolom, "%s", title5);
    mvprintw(judul_start_baris + 5, judul_start_kolom, "%s", title6);
    attroff(A_BOLD | COLOR_PAIR(1));
    // matikan warna

    // buat loading bar
    int bar_width = 40;
    int bar_start_kolom = (cols - bar_width) / 2;
    int bar_start_baris = judul_start_baris + 8;

    // loop animasi loading dari 0% sampai 100%
    for (int i = 0; i <= 100; i++) {
        
        mvprintw(bar_start_baris - 1, (cols - 12) / 2, "Loading... %d%%", i);

        // border bar
        mvprintw(bar_start_baris, bar_start_kolom - 1, "[");
        mvprintw(bar_start_baris, bar_start_kolom + bar_width, "]");

        // isi bar
        attron(COLOR_PAIR(2));
        for (int j = 0; j < bar_width; j++) {
            if (j < (i * bar_width) / 100) {
                mvprintw(bar_start_baris, bar_start_kolom + j, "=");
            } else {
                mvprintw(bar_start_baris, bar_start_kolom + j, " ");
            }
        }
        attroff(COLOR_PAIR(2));
        refresh();
        delay_ms(50);


        if (i < 30) delay_ms(100);       
        else if (i < 70) delay_ms(100);  
        else if (i < 90) delay_ms(100);
        else if (i < 98) delay_ms(100);
        else {
            delay_ms(100);
            mvprintw((rows / 2) + 20, (cols / 2) - 7, "Note : Finalizing"); 
        }; 
    }

    delay_ms(500);
    clear();
}

void playgame() {
        // Posisi awal (Start) dan tujuan (Goal)
    int startPosY = 0, startPosX = 0;
    int goalPosY = 0, goalPosX = 0;

    // Cari posisi 'S' dan 'G' di dalam maze
    for (int row = 0; row < (int)mazeMap.size(); ++row) {
        for (int col = 0; col < (int)mazeMap[row].size(); ++col) {
            if (mazeMap[row][col] == 'S') {
                startPosY = row;
                startPosX = col;
            } else if (mazeMap[row][col] == 'G') {
                goalPosY = row;
                goalPosX = col;
            }
        }
    }

    // Posisi player saat ini
    int playerPosY = startPosY;
    int playerPosX = startPosX;

    // Stamina player (DITAMBAH karena map lebih besar)
    int maxSteps = 200; 
    int currentSteps = 0;

    // Offset untuk menggambar maze di layar (DIBUAT DINAMIS AGAR CENTER)
    int scrRows, scrCols;
    getmaxyx(stdscr, scrRows, scrCols);
    
    // Hitung posisi tengah
    int DRAW_OFFSET_Y = (scrRows - mazeMap.size()) / 2;
    int DRAW_OFFSET_X = (scrCols - mazeMap[0].size()) / 2;

    // Pastikan tidak negatif (jika layar terlalu kecil)
    if (DRAW_OFFSET_Y < 0) DRAW_OFFSET_Y = 0;

    bool isGameRunning = true;
    bool isPlayerWin = false;

    while (isGameRunning) {
        clear();

        // Gambar maze
        for (int row = 0; row < (int)mazeMap.size(); ++row) {
            mvprintw(row + DRAW_OFFSET_Y, DRAW_OFFSET_X, "%s", mazeMap[row].c_str());
        }

        // Gambar player '@' di posisi saat ini
        mvaddch(playerPosY + DRAW_OFFSET_Y, playerPosX + DRAW_OFFSET_X, '|');

        // Tampilkan instruksi
        mvprintw((int)mazeMap.size() + DRAW_OFFSET_Y + 1, DRAW_OFFSET_X, 
                "Gunakan panah untuk bergerak. Tekan 'q' atau 'Q' untuk keluar.");

        // Tampilin sisa langkah
        mvprintw((int)mazeMap.size() + DRAW_OFFSET_Y + 2, DRAW_OFFSET_X, 
                "Sisa Langkah: %d/%d", (maxSteps-currentSteps), maxSteps);
        refresh();

        // Baca input dari keyboard
        int keyPressed = getch();

        if (keyPressed == 'q' || keyPressed == 'Q') {
            isGameRunning = false;
            break;
        }

        // Hitung posisi baru berdasarkan input
        int nextPosY = playerPosY;
        int nextPosX = playerPosX;

        switch (keyPressed) {
            case KEY_UP:
                nextPosY--;
                break;
            case KEY_DOWN:
                nextPosY++;
                break;
            case KEY_LEFT:
                nextPosX--;
                break;
            case KEY_RIGHT:
                nextPosX++;
                break;
            default:
                break;
        }

        // Validasi posisi baru (dalam batas maze dan bukan dinding)
        bool isInsideBounds = (nextPosY >= 0 && nextPosY < (int)mazeMap.size() &&
                               nextPosX >= 0 && nextPosX < (int)mazeMap[0].size());

        if (isInsideBounds) {
            // Cek apakah target cell adalah dinding
            char targetCell = mazeMap[nextPosY][nextPosX];
            // " " != "#" berarti bisa dilalui dan bernilai true
            bool isWalkable = (targetCell != '#');

            if (isWalkable) {
                playerPosY = nextPosY;
                playerPosX = nextPosX;
                //ngurangin stamina
                currentSteps++;
            } 
            if (targetCell=='#'){ //berartikan player nabrak tembok
                playerPosY=startPosY;
                playerPosX=startPosX;
                mvprintw(0,0, "Aduyy nabrak! Balik ke Start geh.");
                currentSteps++;
            } else {
                playerPosX=nextPosX;
                playerPosY=nextPosY;
            }

            // Cek apakah player mencapai goal
            bool hasReachedGoal = (playerPosY == goalPosY && playerPosX == goalPosX);
            if (hasReachedGoal) {
                isPlayerWin = true;
                isGameRunning = false;
            } else if (currentSteps>=maxSteps){
                isPlayerWin=false;
                isGameRunning=false;
            }
        }
    }

    // Tampilkan pesan akhir
    clear();
    if (isPlayerWin) {
        mvprintw(00, 0, "Selamat! Kamu berhasil keluar dari labirin!");
    } else {
        if (currentSteps>=maxSteps){
            mvprintw(0,0, "Cape ya? Kamu dah kehabisan tenaga tuh.");
        } else{
        mvprintw(0, 0, "Next time main lagi yaa..");
        }
    }
    mvprintw(2, 0, "Tekan tombol apa saja untuk keluar...");
    
    refresh();
    getch();
    endwin();
}

int main() {
    // setup Ncurses
    initscr();
    noecho();
    curs_set(0);
    start_color();

    // Mengaktifkan pembacaan tombol keypad (panah, F1, dll)
    keypad(stdscr, TRUE);

    init_pair(1, COLOR_CYAN, COLOR_BLACK); 
    init_pair(2, COLOR_GREEN,COLOR_BLUE);

    int row, col;
    getmaxyx(stdscr, row, col); 

    tampilkanLoadingPage();

    mvprintw((row / 2), (col - 38) / 2, "Loading Selesai. Masuk ke Menu Level...");
    refresh();

    delay_ms(1500);

    playgame();


    return 0;
}