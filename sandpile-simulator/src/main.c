#include <stdio.h>

#define GRID_SIZE 15

int grid[GRID_SIZE][GRID_SIZE];

void init_grid(void)
{
  int i, j;

  for(i=0; i<GRID_SIZE; i++){
    for (j=0; j<GRID_SIZE; j++){
      grid[i][j] = 0;
    }
  }
}

void print_grid(void)
{
  int i, j;

  for(i=0; i<GRID_SIZE; i++){
    for (j=0; j<GRID_SIZE; j++){
      printf("%d ", grid[i][j]);
    }
    printf("\n");
  }
}

int main(void)
{
  init_grid();
  print_grid();
  return 0;
}

