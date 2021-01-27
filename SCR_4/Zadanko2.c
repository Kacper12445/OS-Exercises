#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <stdlib.h>

#define BUF_SIZE 256


int main(int argc, char* argv[])
{	
	if(argc == 1)
	{
		fprintf(stderr, "Wprowadz format w taki sposob: /a.out nazwa_pliku. png/jpeg\n");
		exit(1);
	}
	else if(argc > 2)
	{
		fprintf(stderr, "Za duza ilosc argumentow\n");
		exit(2);
	}

//dwuelementowa tablica desktryptorów [0] - czytanie , [1] - pisanie
	int fd[2];
	pid_t pid;
	int zm_otw;
	int zm_czyt;
	
	char buf[BUF_SIZE];

	pipe(fd);
	if(pipe(fd) == -1)
	{	
		fprintf(stderr, "Blad, nie udalo sie utworzyc potoku");
		return 1;
	}

	pid = fork();	// tworzymy proces
	if(pid == -1)
	{
		fprintf(stderr, "Blad, nie udalo sie utworzyc procesu");
		return -3;		

	}
	
	//parent
	else if(pid > 0)
	{
		close(fd[0]);

		if((zm_otw = open(argv[1], O_RDONLY)) == -1) 
		{
		    fprintf(stderr, "Błąd otwierania pliku\n");
		    return 2;
		}
		
		while((zm_czyt = read(zm_otw, buf, BUF_SIZE)) > 0)   //czytamy dopóki read nie osiągnie wartosci 0 czyli końca
		{
		    if(write(fd[1], buf, zm_czyt) < 0) 
		    {
		        fprintf(stderr, "Nie udało się stworzyć potoku\n");
		        return 3;
		    }  
    	}
        close(zm_otw);

	}
	else if(pid == 0) //child
	{
		close(fd[1]);
		close(0);
		dup(fd[0]);			//tworzymy duplikat desktryptora
		close(fd[0]);
		execlp("display", "display", "-", NULL);	//uruchomienie procesu potomnego
		// pierwszy display to nazwa programu drugi to tablica argumentow uzytych do wywolania programu
		// tablicy tej nie uzywamy bo czytamy z potoku
	}

	return 0;
}
