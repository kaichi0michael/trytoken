#include <sys/types.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int result[] = {-1, -1, -1, -1, -1};
int cnt = -1;

// SIGUSR1
void sigusr1_handler(int signum) {
    for (int i = 0; i < 5; i++) {
        result[i] = 50 + rand() % 50;  // 50～99
    }
    cnt = 4;
}

// SIGUSR2
void sigusr2_handler(int signum) {
    for (int i = 0; i < 5; i++) {
        result[i] = rand() % 50;  // 0～49
    }
    cnt = 4;

}

int main(void) {
    int k, row, col, pid;    
    char msg[256];


    // シグナルハンドラを設定
    struct sigaction sa1, sa2;

    sa1.sa_handler = sigusr1_handler;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;

    sa2.sa_handler = sigusr2_handler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;

    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);

    // Cursesの初期化
    initscr();
    getmaxyx(stdscr, row, col);
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);

    // 画面の初期設定
    bkgd(COLOR_PAIR(3));
    attron(COLOR_PAIR(1));
    for (int i = 0; i < col; i++) {
        mvaddstr(0, i, " ");
        mvaddstr(row-2, i, " ");
        mvaddstr(row-1, i, " ");
    }
    pid = getpid();
    sprintf(msg, " Curses C Dynamic Text Example (pid : %d)", pid);
    mvaddstr(0, 0, msg);
    mvaddstr(row-2, 0, " Key Commands: space - fix a parameter");
    mvaddstr(row-1, 0, " Key Commands: q     - to quit");
    attroff(COLOR_PAIR(1));
    mvaddstr(2, 5, "NOBUNAGA NO YABOU ZENKOKU BAN");
    refresh();

    // メインループ
    while (k != 'q') {  // 'q' キーが押されるまで繰り返し
        attroff(COLOR_PAIR(2));
        for (int i = 0; i < 5; i++) {
            switch(i) {
                case 0: mvprintw((4+i), 5, " KENKOU  %d : ", i); break;
                case 1: mvprintw((4+i), 5, " YASHIN  %d : ", i); break;
                case 2: mvprintw((4+i), 5, " UN      %d : ", i); break;
                case 3: mvprintw((4+i), 5, " MIRYOKU %d : ", i); break;
                case 4: mvprintw((4+i), 5, " IQ      %d : ", i); break;
                default: mvprintw((4+i), 5, " Sensor %d : ", i);
            }
        }
        attron(COLOR_PAIR(2));

        int v;
        // 結果の表示
        for (int i = 0; i < 5; i++) {
            if (result[i] != -1) {
                mvprintw((4+i), 20, "%d", result[i]);
            } else {
                v = rand() % 100;
                mvprintw((4+i), 20, "%d", v);
            }
        }

        // スペースキーで値を固定
        k = getch();
        if (k == ' ') {
            cnt++;
            if (cnt < 5) {
                result[cnt] = v;
            }
        }

        // 合計値の表示
        if (cnt == 4) {
            int s = 0;
            for(int i = 0; i < 5; i++) {
                if (result[i] != -1) {
            s += result[i];
        }
                // s += result[i];
            }
            mvprintw(11, 20, "GOUKEI %d", s);
        }

        // 合計値の表示
        // if (cnt == 4) {
        //     int s = 0;
        //     int validCount = 0; // 有効なカウントをトラック

        //     mvprintw(11, 20, "GOUKEI DEBUG:");
        //     for (int i = 0; i < 5; i++) {
        //         // resultの内容を表示
        //         mvprintw(12 + i, 20, "result[%d] = %d", i, result[i]);
        //         if (result[i] != -1) {
        //             s += result[i];
        //             validCount++;
        //             // 合計の途中経過を表示
        //             mvprintw(12 + i, 40, "Partial Sum: %d", s);
        //         }
        //     }

        //     // 有効な値が存在する場合にのみ合計を表示
        //     if (validCount > 0) {
        //         mvprintw(12 + 6, 20, "GOUKEI %d", s);
        //     } else {
        //         mvprintw(12 + 6, 20, "GOUKEI -");
        //     }
        // }
        

        // 値の初期化
        if (cnt == 5) {
            for(int i = 0; i < 5; i++) {
                result[i] = -1;
            }
            cnt = -1;
        }
    }
    

    endwin();
    exit(0);
}
