#include <ncurses/curses.h>
#include <vector>
#include <string>

// Peta labirin sederhana (bisa kamu ubah sendiri)
std::vector<std::string> mazeMap = {
    "############################",
    "#S     #              #   #",
    "# ### ####### ####### # # #",
    "#   #       #       #   # #",
    "### ####### # ##### ##### #",
    "#   #     # #     #     # #",
    "# # # ### # ##### ### # # #",
    "# #   #   #     #   # #   #",
    "# ##### ######### # # #####",
    "#     #           #       G",
    "############################"
};

int main() {
    // Inisialisasi ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

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

    // Stamina player
    int maxSteps = 60;
    int currentSteps = 0;

    // Offset untuk menggambar maze di layar
    const int DRAW_OFFSET_Y = 10;
    const int DRAW_OFFSET_X = 10;

    bool isGameRunning = true;
    bool isPlayerWin = false;

    while (isGameRunning) {
        clear();

        // Gambar maze
        for (int row = 0; row < (int)mazeMap.size(); ++row) {
            mvprintw(row + DRAW_OFFSET_Y, DRAW_OFFSET_X, "%s", mazeMap[row].c_str());
        }

        // Gambar player '@' di posisi saat ini
        mvaddch(playerPosY + DRAW_OFFSET_Y, playerPosX + DRAW_OFFSET_X, '@');

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
        mvprintw(0, 0, "Selamat! Kamu berhasil keluar dari labirin!");
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
    return 0;
}
