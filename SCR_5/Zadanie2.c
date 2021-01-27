#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>


int main()
{
    struct stat fileStat;
    pid_t ch_PID;
    char fileName[64];
    int fd[2];              //fd[0] - plik
                            //fd[1] - plik do zapisywania zawartosci mapowania
    int *ptr = NULL;
    ssize_t fileSize;


    ch_PID = fork();        //tworzymy proces potomny

    if(ch_PID < 0)          //blad tworzenia procesu potomnego
    {
        printf("Nie udalo sie utworzyc procesu \n");
        exit(-1);
    }

    else if(ch_PID == 0)    //jesli dziecko
    {
        sleep(5);   //czekanie na wpisanie nazwy pliku.
        execlp("display","display","-update","1","-delay","2","plik",NULL);
    }

    else if(ch_PID > 0)     //jesli rodzic
    {
        while(1)
        {
            printf("Podaj nazwe pliku: \n");
            scanf("%s", fileName);

            //trzeci argument "0" - prawa dostepu
            fd[0] = open("plik", O_RDWR, 0);
            fd[1] = open(fileName, O_RDWR, 0);

            fstat(fd[1], &fileStat);
            ftruncate(fd[0], fileStat.st_size);

            ptr = mmap(NULL, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd[0], 0);

            if(ptr == MAP_FAILED)
            {
                printf("Mapping failed \n");
                return 1;
            }

            printf("Dlugosc pobranego pliku: %ld \n", fileStat.st_size);
            
            //int n = read(fd[1], ptr, fileStat.st_size);
            
            

            if(n != fileStat.st_size);
            {
                printf("Błąd w zapisywaniu\n");
                //return -2;
            }

                //Zamykanie deskryptorów
                close(fd[0]);
                close(fd[1]);

                /*
                Funkcja msync synchronizuje wawartość obszaru pamięci z obrazem pliku na dysku.
                Umieszcza zmiany z kopii do pliku ktory mapowalismy

                MS_SYNC - żądanie aktualizacji.
                ptr - adres na ktory mapowalismy
                */
                msync(ptr, fileStat.st_size, MS_SYNC);
                if(msync(ptr, fileStat.st_size, MS_SYNC) == 0)
                {
                    printf("Synchronizacja przebiegla pomyslnie \n");
                }
                else
                {
                    printf("Blad synchronizacji \n");
                    exit(-1);
                }
                int err = munmap(ptr, fileStat.st_size);

                if(err != 0)
                {
                    printf("UnMapping Failed\n");
                    return 1;
                }

        }
    }
    return 0;
}