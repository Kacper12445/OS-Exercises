#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 


#define BUF_SIZE 256


int main()
{	
//dwuelementowa tablica desktryptorów [0] - czytanie , [1] - pisanie
	int fd[2];
	pid_t pid;
	int in_fd;
	int n;
	
	char buf[BUF_SIZE];
	char fname[32];
	
	pipe(fd);
	if(pipe(fd) == -1)
	{	
		fprintf(stderr, "Blad, nie udalo sie utworzyc potoku");
		return 1;
	}
	

	pid = fork();
	if(pid == -1)
	{
		fprintf(stderr, "Blad, nie udalo sie utworzyc procesu");
		return -3;		

	}
	
	//parent
	else if(pid > 0)
	{
		close(fd[0]);
		scanf("%s", fname);

		if((in_fd = open(fname, O_RDONLY)) < 0)
		{
			fprintf(stderr, "Nie udało się utworzyć\n");
			return 2;
		}
		while((n = read(in_fd, &buf, BUF_SIZE)) > 0)
		{
			if(write(fd[1], &buf, BUF_SIZE))
			{
				fprintf(stderr, "Nie udało się napisać w potoku\n");
				return 3;	
			}
		}
		close(in_fd);
	}
	else //child
	{
		close(fd[1]);
		close(0);
		dup(fd[0]);
		close(fd[0]);
		execlp("dislpay", "dislpay", "-", NULL);
	}

	return 0;
}
