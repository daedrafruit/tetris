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
  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      printf("%c ", colors[world[y][x]]);
    }
    printf("\n");
  }
}

void initialize_world() {
  int rows = WORLD_HEIGHT;
  int cols = WORLD_WIDTH;

  for (int y = 0; y < rows; y++) {
    for (int x = 0; x < cols; x++) {
      if (y == 0 || y == 21 || x == 0 || x == 11)
        world[y][x] = 1;
      else 
        world[y][x] = 0;
    }
  }
}

bool can_move(int x_offset, int y_offset) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (!piece_value_at(x, y))
        continue;

      int x_rel = x + x_offset;
      int y_rel = y + y_offset;

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
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (piece_value_at(x, y))
        world[p.y + y][p.x + x] = 1;
    }
  }
  return false;
}

bool clear_piece() {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (piece_value_at(x, y))
        world[p.y + y][p.x + x] = 0;
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

void new_piece() {
  p.id = rand() % 7;
  p.rotation = 0;
  p.x = 4;
  p.y = 2;
}


int main() {
  double delta;
  double time_ms = get_time_ms();
  double accumulator = 0;
  int timestep = 300;

  srand(time(NULL));

  new_piece();
  initialize_world();
  draw_world();

  while (1) {

    double now = get_time_ms();
    delta = now - time_ms;
    accumulator += delta;
    time_ms = now;

    if (accumulator >= timestep) {
      if (!can_move(0, 1)) {
        new_piece();
      }
      else {
        clear_piece();
        if (rand() % 10 > 6) rotate_piece_clockwise();
        move_piece(0, 1);
      }

      place_piece();
      draw_world();
      accumulator = 0;
    }
  }
}

