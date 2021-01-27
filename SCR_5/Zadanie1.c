#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){

    while(1)
    {
        char fileName[64];
        printf("Podaj nazwe pliku: \n");
        scanf("%s", fileName);
        char *plik = fileName;
        /*
        Funkcja open słuzy do otwierania pliku.
        plik - sciezka do pliku/plik
        0_RDWR - opcje otwarcia
        */
        int fd = open(plik, O_RDWR);
        
        if(fd < 0)
        {
            printf("\n\"%s \" Nie udalo sie otworzyc\n", plik);
            exit(1);
        }
    /*
    Funkcja fstat() sluzy do pobierania statusu pliku.
    Przekazuje takie informacje jak typ pliku,wlasciciel pliku,prawa dostepu,rozmiar pliku,czas dostepu do pliku.
    Dzialanie tej funkcji sprowadza sie jedynie do przepisania do bufora. 
    fd - deskryptor pliku
    filestat - dane o pliku 
    */
        struct stat fileStat;
        int err = fstat(fd, &fileStat);
        if(err < 0)
        {
            printf("\n\"%s \" Nie udalo sie otworzyc\n", plik);
            exit(2);
        }

    /*
    Funkcja ftruncate powoduje ustawienie długości pliku 
    fd - plik  wskazany przez desktryptor
    filestat.st_size - długość w bajtach jaką chcemy ustawic dla danego pliku
    */
        ftruncate(fd, fileStat.st_size);

    /*
    Funkcja mmap mapuje plik w pamięci
    mmap(x1, x2, x3, x4, x5, x6)
    x1 - adres pod którym ma być zmapowana pamięć. Jesli NULL to jadro systemu samo wybiera adres
    x2 - wielkosc do mapowania
    x3 - Sposob w ochrony pamięci: 
                                -  PROT_EXEC - Strony mogą być wykonane
                                -  PROT_READ - Strony mogą być odczytywane
                                -  PROTE_WRITE - Strony mogą być zapisywane
                                -  PROT_NONE - Strony nie mogą być dostępne
    x4 - określa rodzaj mapowanego pliku i czy modyfikacje dla zmapowanej kopii są prywatne
    Przykłady:
    MAP_FIXED - Nie wybieranie innego adresu niż podany
    MAP_Shared - Współdzielenie mapowania ze wszystkimi innymi procesami mapującymi obiekt.
        Zapisywanie   danych  w  danym  obszarze  będzie  równoważne  z zapisywaniem 
        do pliku. Plik może w rzeczywistości nie zostać zaktualizowany  aż 
        do wywołania msync.
    MAP_PRIVATE -  Prywatne mapowanie typu kopiowanie podczas zapisu. 
    x5 - deskrpotor plików do zmapowania (przy MAP_ANYMOUS ten argument jest ingorowany)
    x6 - offset w pliku. Liczba określająca miejsce od którego chcemy rozpoczac odwzorowywanie
     Jeśli pamięć ma być dzielona to offset musi być wielokrotnością rozmiaru strony.
    */
        char *ptr = mmap(NULL,fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd,0);
        if(ptr == MAP_FAILED)
        {
            printf("Mapping Failed\n");
            exit(3);
        }
        close(fd);

        /*
        Funkcja write  sluzy do pisania do pliku. Zwraca liczbe zapisanych bajtow
        1 - deskryptor jako stdout
        ptr - wskaznik do danych do zapisania
        filestat.st_size - ilosc bajtow do zapisania
        */
        printf("Dlugosc pobranego pliku: %ld \n", fileStat.st_size);
        ssize_t n = write(1, ptr, fileStat.st_size);
        if(n != fileStat.st_size)
        {
            printf("Write failed");
        }

    //Usuwanie mapowania
        err = munmap(ptr, fileStat.st_size);

        if(err != 0)
        {
            printf("UnMapping Failed\n");
            return 1;
        }
    }
    return 0;
}