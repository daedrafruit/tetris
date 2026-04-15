#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#define WORLD_WIDTH 12
#define WORLD_HEIGHT 22

double get_time_ms() {
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
  int id;
  int x, y, rotation;
  int size, rotations;
} piece; 

int get_value_at(piece *p, int rotation, int x, int y) {
  int size = p->size;
  return *(p->data + (rotation * size * size) + (y * size) + x);
}

char colors[2] = { ".#" };
void draw_world(int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  int rows = WORLD_HEIGHT;
  int cols = WORLD_WIDTH;

  system("clear");
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%c ", colors[world[i][j]]);
    }
    printf("\n");
  }
}

void initialize_world(int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  int rows = WORLD_HEIGHT;
  int cols = WORLD_WIDTH;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == 0 || i == 21 || j == 0 || j == 11)
        world[i][j] = 1;
      else 
        world[i][j] = 0;
    }
  }
}

bool can_move(piece *p, int y_offset, int x_offset, int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      if (!get_value_at(p, 0, i, j))
        continue;

      int x_rel = j + x_offset;
      int y_rel = i + y_offset;

      bool within_piece = (x_rel < p->size) && (y_rel < p->size);

      if (within_piece && get_value_at(p, 0, y_rel, x_rel))
        continue;

      if (world[p->y + y_rel][p->x + x_rel] == 1)
        return false;
    }
  }
  return true;
}

bool draw_piece(piece *p, int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      if (get_value_at(p, p->rotation, i, j))
        world[p->y + i][p->x + j] = p->id;
    }
  }
  return false;
}

bool clear_piece(piece *p, int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  for (int i = 0; i < p->size; i++) {
    for (int j = 0; j < p->size; j++) {
      if (get_value_at(p, p->rotation, i, j))
        world[p->y + i][p->x + j] = 0;
    }
  }
  return false;
}

bool move_piece(piece *p, int x_offset, int y_offset, int world[WORLD_HEIGHT][WORLD_WIDTH]) {
  if (can_move(p, x_offset, y_offset, world)) {
    clear_piece(p, world);
    p->x += x_offset;
    p->y += y_offset;
    draw_piece(p, world);
    return true;
  }
  else 
    return false;
}

int main() {
  double delta;
  double time = get_time_ms();
  double accumulator = 0;

  int world[WORLD_HEIGHT][WORLD_WIDTH];

  piece p = {(int *)O, 1, 3, 4, 0, 4, 0};
  initialize_world(world);
  draw_world(world);

  while (1) {

    double now = get_time_ms();
    delta = now - time;
    accumulator += delta;
    time = now;

    if (accumulator >= 1000) {
      move_piece(&p, 0, 1, world);
      draw_world(world);
      accumulator = 0;
    }
  }
}

