#include <stdio.h>
#include <string.h>

char * napis = "Witajcie moi mili ...";


int main(){
  unsigned int index =0;
  for (index; index < strlen(napis); index++)
  {
    printf("%c",napis[index]);
  }
  return 0;
}
