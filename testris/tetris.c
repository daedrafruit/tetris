#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time() {
  struct timeval time;
  gettimeofday(&time, NULL);
  double time_taken;
  time_taken = time.tv_sec * 1000 + time.tv_usec / 1000.0;
  return time_taken;
}


void draw_world(int rows, int cols, int world[rows][cols]) {
  system("clear");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (world[i][j] == 0)
        printf(".");
      else if (world[i][j] == 1)
        printf("#");
      else printf(".");
      printf(" ");
    }
    printf("\n");
  }
}

void initialize_world(int rows, int cols, int world[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == 0 || i == 21 || j == 0 || j == 11) {
        world[i][j] = 1;
      }
      else 
        world[i][j] = 0;
    }
  }
}

int main() {
  double delta;
  double time = get_time();
  double accumulator = 0;
  int rows = 22;
  int cols = 12;

  int sec = 0;
  int world[rows][cols];

  initialize_world(rows, cols, world);
  draw_world(rows, cols, world);

  while (1) {

    double now = get_time();
    delta = now - time;
    accumulator += delta;
    time = now;

    if (accumulator >= 1000) {
      draw_world(rows, cols, world);
      accumulator = 0;
    }
  }
}

