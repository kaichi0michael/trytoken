#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum) {
    puts("SIGTERMを受信しました。中断します。");
    exit(0);
}

int main(void) {
    signal(SIGTERM, signal_handler);

    while (1) {
    }

    return 0;
}

