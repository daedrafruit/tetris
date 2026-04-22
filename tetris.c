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
  5, //y
  0, //rotation 
};


bool piece_value_at(int x, int y) {
  Vector2i new_coords = {x,y};
  const Vector2i *coords = shapes[p.id][p.rotation];

  for (int i = 0; i < 4; i++) {
    Vector2i c = *(coords + i);
    if (c.x == new_coords.x && c.y == new_coords.y) return true;
  }
  return false;
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
      if (!piece_value_at(j, i))
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

bool place_piece() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece_value_at(j, i))
        world[p.y + i][p.x + j] = 1;
    }
  }
  return false;
}

bool clear_piece() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (piece_value_at(j, i))
        world[p.y + i][p.x + j] = 0;
    }
  }
  return false;
}

bool move_piece(int x_offset, int y_offset) {
  if (can_move(x_offset, y_offset)) {
    p.x += x_offset;
    p.y += y_offset;
    return true;
  }
  else 
    return false;
}


bool rotate_piece_counter() {
  int temp = p.rotation;
  if (p.rotation <= 0) {
    p.rotation = 3;
    return true;
  }
  p.rotation += 1;
  if (!can_move(0,0)) {
    p.rotation = temp;
    return false;
  }
  return true;
}

bool rotate_piece_clockwise() {
  int temp = p.rotation;
  if (p.rotation >= 3) {
    p.rotation = 0;
    return true;
  }
  p.rotation += 1;
  if (!can_move(0,0)) {
    p.rotation = temp;
    return false;
  }
  return true;
}


int main() {
  double delta;
  double time_ms = get_time_ms();
  double accumulator = 0;
  int timestep = 100;

  initialize_world();
  draw_world();

  srand(time(NULL));
  p.id = 6;

  while (1) {

    double now = get_time_ms();
    delta = now - time_ms;
    accumulator += delta;
    time_ms = now;

    if (accumulator >= timestep) {
      if (!can_move(0, 1)) {
        p.id = rand() % 7;
        p.rotation = 0;
        p.x = 3;
        p.y = 5;
      }
      else {
        clear_piece();
        move_piece(0, 1);
      }

      place_piece();
      draw_world();
      accumulator = 0;
    }
  }
}

