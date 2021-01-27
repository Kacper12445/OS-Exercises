#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *Hello(void *arg) {
    long ID;
    ID = (long)pthread_self();
    
    printf("Hello SCR. Written by threadh ID: %ld\n", ID);

    pthread_exit(NULL);

    printf("Not shown\n");
}

int main(int argc, char* argv[]) {
    int n = 3;
    pthread_t Threads[n];
    int result;
    /*
    int pthread_create(x1, x2, x3, x4)
    x1 - wskażnik do wątku
    x2 - parametry wątku
    x3 - wskaźnik na funkcję wykonywaną przez wątek, funkcja musi przyjmować 1 argument typu void * i 
    zwracać wynik typu void *
    x4 - argument przekazywany funkcji x3
     
    Zwraca 0 gdy wykonuje się poprawnie
    */
   for(long i = 0; i < n; i++)
   {
        result = pthread_create(&Threads[n], NULL, Hello, (void *) i);
        
        if(result != 0)
        {
            perror("Could not create thread.");
            
        }
   }

    pthread_exit(NULL);
    return 0;
}