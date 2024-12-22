#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* SIGINT (Ctrl+C) 用のシグナルハンドラ */
void sigint_handler(int signum) {
    printf("SIGINT (Ctrl+C) caught\n");
    exit(1);
}

/* SIGTERM 用のシグナルハンドラ */
void sigterm_handler(int signum) {
    printf("SIGTERM caught\n");
    exit(1);
}

/* SIGHUP 用のシグナルハンドラ */
void sighup_handler(int signum) {
    printf("SIGHUP caught\n");
}

int main(void) {
    struct sigaction sa_int, sa_term, sa_hup;

    /* SIGINT のシグナルハンドラを登録 */
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    /* SIGTERM のシグナルハンドラを登録 */
    sigemptyset(&sa_term.sa_mask);
    sa_term.sa_handler = sigterm_handler;
    sa_term.sa_flags = 0;
    sigaction(SIGTERM, &sa_term, NULL);

    /* SIGHUP のシグナルハンドラを登録 */
    sigemptyset(&sa_hup.sa_mask);
    sa_hup.sa_handler = sighup_handler;
    sa_hup.sa_flags = 0;
    sigaction(SIGHUP, &sa_hup, NULL);

    /* 無限ループでシグナルを待つ */
    while (1) {
        sleep(1);  // CPU負荷を減らすために1秒待機
    }

    return 0;
}

