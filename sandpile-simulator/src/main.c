#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 15

void sleep_ms(long ms)
{
  struct timespec ts;
  ts.tv_sec=ms/1000;
  ts.tv_nsec=(ms%1000)*1000000L;

  nanosleep(&ts, NULL);
}



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

void add_grain(int row, int col)
{
  if (row < 0 || row >= GRID_SIZE){
    return;
  }
  if (col < 0 || col >= GRID_SIZE){
    return;
  }
  grid[row][col]++;
}

int has_unstable(void)
{
  int i, j;

  for(i=0; i<GRID_SIZE; i++){
    for(j=0; j<GRID_SIZE; j++){
      if (grid[i][j]>=4){
        return 1;
      }
    }
  }
  return 0;
}

void topple_cell(int row, int col)
{
  if (grid[row][col]<4) {
    return;
  }
  grid[row][col] -= 4;
  if (row > 0){
    grid[row-1][col]++;
  }
  if (row < GRID_SIZE-1){
    grid[row+1][col]++;
  }
  if (col > 0){
    grid[row][col-1]++;
  }
  if (col < GRID_SIZE-1){
    grid[row][col+1]++;
  }
}

void relax(void)
{
  int i, j;
  while(has_unstable()){
    for (i=0; i<GRID_SIZE; i++){
      for (j=0; j<GRID_SIZE; j++){
        if (grid[i][j] >= 4){
          topple_cell(i,j);
        }
      }
    }
  }
}


int relax_step(void)
{
    int i, j;

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] >= 4) {
                topple_cell(i, j);
                return 1;
            }
        }
    }

    return 0;
}




void add_random_grain(void)
{
  int row;
  int col;
  row = rand() % GRID_SIZE;
  col = rand() % GRID_SIZE;

  add_grain(row,col);
}

void simulate_step(void)
{
    add_random_grain();
    relax();
}

int main(void)
{
  srand(time(NULL));

  init_grid();
  
  printf("\033[2J"); // clean
  printf("\033[H"); // move cursor 
  
  while (1){
    add_random_grain();
    while(relax_step()){
    printf("\033[H"); // move cursor 
    print_grid();
    sleep_ms(50);
    }
    printf("\033[H");
    print_grid();
    sleep_ms(10);
  }
  return 0;
}

