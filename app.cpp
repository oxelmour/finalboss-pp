#include <ncurses/curses.h>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

// fungsi untuk delay ncurses dalam milidetik
void delay_ms(int ms){
    napms(ms);
}

void tampilkanLoadingPage() {
    int rows, cols;

    // dapatkan ukuran layar dan fill ke variabel rows dan cols
    getmaxyx(stdscr, rows, cols);

    const char* title1 = " _______ _    _ ______   __  __          ____________ ";
    const char* title2 = "|__   __| |  | |  ____| |  \\/  |   /\\   |___  /  ____|";
    const char* title3 = "   | |  | |__| | |__    | \\  / |  /  \\     / /| |__   ";
    const char* title4 = "   | |  |  __  |  __|   | |\\/| | / /\\ \\   / / |  __|  ";
    const char* title5 = "   | |  | |  | | |____  | |  | |/ ____ \\ / /__| |____ ";
    const char* title6 = "   |_|  |_|  |_|______| |_|  |_/_/    \\_\\_____|______|";

    int judul_start_baris = (rows / 2) - 6;
    int panjang_visual_judul = 55;
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
        else if (i < 70) delay_ms(850);  
        else if (i < 90) delay_ms(650);
        else if (i < 98) delay_ms(2500);
        else {
            delay_ms(10000);
            mvprintw((rows / 2) + 20, (cols / 2) - 7, "Note : Finalizing"); 
        }; 
    }

    delay_ms(500);
    clear();
}

int main() {
    // setup Ncurses
    initscr();
    noecho();
    curs_set(0);
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK); 
    init_pair(2, COLOR_GREEN,COLOR_BLUE);

    int row, col;
    getmaxyx(stdscr, row, col); 

    tampilkanLoadingPage();

    mvprintw((row / 2), (col - 38) / 2, "Loading Selesai. Masuk ke Menu Level...");
    refresh();

    getch();
    endwin();

    return 0;
}