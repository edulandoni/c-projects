#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char *argv[])
{ 
  FILE *file1, *file2;
  int c1, c2;

  if (argc != 3){
    printf("Usage: %s <file1> <file2>\n", argv[0]);
    exit(-1);
  }

  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "r");

  if (file1 == NULL || file2 == NULL){
    exit(-1);
  }
  
  while (1){
    c1 = fgetc(file1);
    c2 = fgetc(file2);
    
    if (c1 == EOF && c2 == EOF) break;
    if (c1 == EOF || c2 == EOF) exit(-1);

    fputc((unsigned char)(c1^c2), stdout);
  }
  fclose(file1);
  fclose(file2);
  return 0;
}

