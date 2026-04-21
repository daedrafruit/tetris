#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "data.h"

#define WORLD_WIDTH 12
#define WORLD_HEIGHT 22
int world[WORLD_HEIGHT][WORLD_WIDTH];

typedef struct {
  int id;
  int x, y, rotation;
} piece; 

piece p = {
  1, //id
  3, //x
  16, //y
  0, //rotation 
};


int piece_value_at(int x, int y) {
  Vector2i new_coords = {y,x};
  for (int i = 0; i < 4; i++) {
    Vector2i coords = shapes[p.id][p.rotation][i];
    if (coords.x == new_coords.x && coords.y == new_coords.y) return 1;
  }
  return 0;
}

char colors[2] = { ".#" };
void draw_world() {
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

void initialize_world() {
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

bool can_move(int x_offset, int y_offset) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (!piece_value_at(i, j))
        continue;

      int x_rel = j + x_offset;
      int y_rel = i + y_offset;

      bool within_piece = (x_rel < 4) && (y_rel < 4);

      if (within_piece && piece_value_at(x_rel, y_rel))
        continue;

      if (world[p.y + y_rel][p.x + x_rel] > 0)
        return false;
    }
  }
  return true;
}

bool draw_piece() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece_value_at(i, j))
        world[p.y + i][p.x + j] = 1;
    }
  }
  return false;
}

bool clear_piece() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece_value_at(i, j))
        world[p.y + i][p.x + j] = 0;
    }
  }
  return false;
}

bool move_piece(int x_offset, int y_offset) {
  if (can_move(x_offset, y_offset)) {
    clear_piece();
    p.x += x_offset;
    p.y += y_offset;
    draw_piece();
    return true;
  }
  else 
    return false;
}


int main() {
  double delta;
  double time_ms = get_time_ms();
  double accumulator = 0;

  initialize_world();
  draw_world();

  srand(time(NULL));
  p.id = rand() % 7;

  while (1) {

    double now = get_time_ms();
    delta = now - time_ms;
    accumulator += delta;
    time_ms = now;

    if (accumulator >= 1000) {
      move_piece(0, 1);
      draw_world();
      accumulator = 0;
    }
  }
}

