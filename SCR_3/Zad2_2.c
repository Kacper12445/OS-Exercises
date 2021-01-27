#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void handler(int signum)
{
        printf("\nZłapanie sygnału nr %d, zakończenie działania programu\n", signum);
        exit(0);
}

void handler_2(int signum)
{
        printf("\nZłapanie sygnału nr %d, kontynowanie wykonywania programu\n", signum);
}

void handler_3(int signum)
{
	for(int i = 0; i < 1000; i++)
	{
		signal(signum, SIG_IGN);
		printf("%d\n", i);
	}
	signal(signum, SIG_DFL);
	raise(signum);
	//printf("\nZłapanie sygnału nr %d, zakończenie działania programu\n", signum);
       // exit(0);
	
}

void handler_4(int signum)
{
	while(1)
		signal(signum, SIG_IGN);
}

	

int main()
{
        int i;
        signal(SIGALRM, handler_2);
	signal(SIGTERM, handler_2);
	signal(SIGUSR1, handler_2);
	signal(SIGUSR2, handler_2);
        while(1)
	{
                
		//printf("%d, %d\n", getpid(), i);
		sleep(10);
		i++;	
	}


        return 0;
}
