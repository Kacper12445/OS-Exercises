#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include<sys/wait.h>

#include<fcntl.h>





int main(int argc, char* argv[])
{	

	
	if(argc == 1)  // gdy podamy jedynie 1 argument w wywolaniu (w tym przypadku jedynie ./a.out)
	{
		fprintf(stderr, "Wprowadz format w taki sposob: /a.out nazwa_pliku.txt\n");
		exit(1);
	}
	else if(argc > 2)	//jeśli wprowadzimy więcej niż jeden plik (wiecej niz 2 argumenty)
	{
		fprintf(stderr, "Za duza ilosc argumentow\n");
		exit(2);
	}
	
	FILE *plik;
	int fd[2];	//dwuelementowa tablica desktryptorów [0] - czytanie , [1] - pisanie
	pid_t pid;	// ID procesu
	
	char bufor_in[256];		//bufor wejsciowy
	char bufor_out[256];	//bufor wyjsciowy
	

	if((plik = fopen(argv[1], "r")) == NULL)	//Gdy nie uda się otworzyc pliku fopen zwraca NULLm "r" - tylko czytanie, argv[1] - nazwa pliku
	{
		perror("Blad otwarcia pliku");
		exit(-1);
	}
	/*
		czytanie danych z plik, znak^/0 oznacz czytanie do momentu napotkania /0 czyli końca 
		bufor_in - w nim są zapisywane dane
		
	*/
	else
	{
		fscanf(plik, "%[^/0]", bufor_in);		 
		fclose(plik);						// zamykamy otwarty funkcja fopen plik
	}
	
	pipe(fd);	//tworznie potoku
	if(pipe(fd) == -1)
	{	
		fprintf(stderr, "Blad, nie udalo sie utworzyc potoku\n");
		exit(-2);
	}
	

	pid = fork(); //tworzenie procesu, proces macierzysty dostanie id dziecka a dziecko dostaje 0
	if(pid == -1)
	{
		fprintf(stderr, "Blad, nie udalo sie utworzyc procesu potomnego\n");
		exit(-3);		

	}
	else if(pid > 0)	//rodzic
	{
		close(fd[0]);    //zamykamy czytanie
		write(fd[1], bufor_in, strlen(bufor_in)+1);  //fd[1] desktryptor piszacy, bufor_in - tam zapisujemy, trzeci argument to ilosc znaków do zapisania
		close(fd[1]);	//zamykamy pisanie

	}
	else 	//pid == 0 dziecko
	{
		close(fd[1]);	//zamykamy pisanie
		read(fd[0], bufor_out, strlen(bufor_in));	//czytamy z drugiego bufora tyle znaków ile podaje trzeci argument
		printf("#%s#\n", bufor_out);
		close(fd[0]);	//zamykamy czytanie
	}

	return 0;
}










