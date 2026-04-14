#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#define WORLD_WIDTH 12
#define WORLD_HEIGHT 22

double get_time() {
  struct timeval time;
  gettimeofday(&time, NULL);
  double time_taken;
  time_taken = time.tv_sec * 1000 + time.tv_usec / 1000.0;
  return time_taken;
}



int O[1][4][4] = {
  {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}
};


int I[2][4][4] = {
  {{0,0,0,0}, {0,0,0,0}, {1,1,1,1}, {0,0,0,0}},
  {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}}
};

int J[4][3][3] = {
	{{0,0,0}, {1,1,1}, {0,0,1}},
	{{0,1,0}, {0,1,0}, {1,1,0}},
	{{1,0,0}, {1,1,1}, {0,0,0}},
	{{0,1,1}, {0,1,0}, {0,1,0}}
};

int L[4][3][3] = {
  {{0,0,0}, {1,1,1}, {1,0,0}},
  {{1,1,0}, {0,1,0}, {0,1,0}},
  {{0,0,1}, {1,1,1}, {0,0,0}},
  {{0,1,0}, {0,1,0}, {0,1,1}}
};

int S[2][3][3] = {
  {{0,0,0}, {0,1,1}, {1,1,0}},
  {{0,1,0}, {0,1,1}, {0,0,1}}
};

int Z[2][3][3] = {
  {{0,0,0}, {1,1,0}, {0,1,1}},
  {{0,0,1}, {0,1,1}, {0,1,0}}
};

int T[4][3][3] = {
  {{0,0,0}, {1,1,1}, {0,1,0}},
  {{0,1,0}, {1,1,0}, {0,1,0}},
  {{0,1,0}, {1,1,1}, {0,0,0}},
  {{0,1,0}, {0,1,1}, {0,1,0}}
};

typedef struct {
  int *data;
  int x, y;
  int size, rotations;
} piece; 

int get_value_at(piece p, int rotation, int x, int y) {
  return *(p.data + rotation * p.rotations + x * p.size + y);
}


void draw_world(int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  int rows = WORLD_HEIGHT;
  int cols = WORLD_WIDTH;

  char *colors[2] = { ".", "#" };
  system("clear");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%s ", colors[world[i][j]]);
    }
    printf("\n");
  }
}

void initialize_world(int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  int rows = WORLD_HEIGHT;
  int cols = WORLD_WIDTH;

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

bool draw_piece(piece p, int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  for (int i = 0; i < p.size; i++) {
    for (int j = 0; j < p.size; j++) {
      if (get_value_at(p, 0, i, j))
        world[p.x + i][p.y + j] = 1;
    }
  }
  return false;
}

int main() {
  double delta;
  double time = get_time();
  double accumulator = 0;

  int world[WORLD_HEIGHT][WORLD_WIDTH];

  piece p = {(int *)O, 0, 0, 4, 4};
  initialize_world(world);
  draw_world(world);

  while (1) {

    double now = get_time();
    delta = now - time;
    accumulator += delta;
    time = now;

    if (accumulator >= 1000) {
      draw_piece(p, world);
      draw_world(world);
      accumulator = 0;
    }
  }
}

