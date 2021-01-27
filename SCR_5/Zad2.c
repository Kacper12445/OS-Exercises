#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#define BUF_SIZE 1024

int main()
{
   char fileName[64];
   int fd;
   int fileSize;
   struct stat fileStat;
   pid_t ch_PID;
   char buff[BUF_SIZE];
   char *ptr;   
   int zm_czyt;

   ch_PID = fork();
   if(ch_PID < 0)
   {
      printf("Nie udalo sie utworzyc procesu \n");
      exit(-1);
   }

   else if(ch_PID > 0)
   {
      while(1)
      {
         printf("Podaj nazwe pliku: \n");
         scanf("%s", fileName);
         printf("Wczytano");

         fd = open(fileName, O_RDWR);
         if(fd < 0)
         {
            printf("Nie udalo otworzyc sie pliku");
            exit(1);
         }
         
         fstat(fd, &fileStat);
         
         if(fstat(fd, &fileStat) < 0)
         {
            printf("\n\"%s \" Nie udalo sie otworzyc\n", fileName);
            exit(2);
         }
         fileSize = fileStat.st_size;
         printf("Dlugosc pobranego pliku: %d \n", fileSize);

         ftruncate(fd, fileSize);

         ptr = mmap(0, fileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
         if(ptr == MAP_FAILED)
         {
            printf("Mapping Failed\n");
            return 1;
         }

            if(write(fd, buff, zm_czyt) != fileSize) 
            {
               fprintf(stderr, "Nie udało się stworzyć potoku\n");
               return 3;
            }
            
         msync(ptr, fileSize, MS_SYNC);
         close(fd);
         munmap(ptr, fileSize);
         
      }

   }

   else if(ch_PID == 0)
   {
      execlp("display","dislpay","-update","1","-",NULL);
      exit(0);

   }


   return 0;
}