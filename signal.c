#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int signum)
{

	puts("中断します");
	exit(1);
}

int main(void){

	signal(SIGINT, signal_handler);

	while(1){
	}

	return 0;
}
