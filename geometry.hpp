#include "tetris.hpp"

namespace geometry {
using math3d::vec2f;
const float JUMP_FORCE = 18.0, GRAVITY_FORCE = 5.0, MOVE_STEP = 0.1;
bool started, alive, depth, hexagon, flipped, callbackActive, completed, wind;
int worldOffsetX, worldOffsetY, depthValue;
float dt;

const int LEVEL_WIDTH = 72, LEVEL_HEIGHT = 22, CAMERA_PADDING = 16, PLAYER_SIZE = 15, BLOCK_SIZE = 15, DEPTH = 5, SQ_SIZE = 7;

const uint8_t PROGMEM windImage[] = {
  0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x20, 0xf8, 0x1f, 0xad, 0x55, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x29, 0x65, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x4a, 0x49, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xff, 0xff, 0x21, 0x04, 0xd6, 0xba, 0xd6, 0xba, 0x21, 0x24, 0x94, 0xd3, 0x94, 0xd3, 0x18, 0xc3, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x10, 0x82, 0xf7, 0xbe, 0x00, 0x00, 0xf7, 0x9e, 0xff, 0xff, 0x08, 0x61, 0x6b, 0x8d, 0x84, 0x51, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x20, 0x08, 0x41, 0xff, 0xdf, 0xd6, 0x9a, 0x00, 0x00, 0x00, 0x00, 0xde, 0xdb, 0xd6, 0x9a, 0x00, 0x00, 0x29, 0x45, 0x00, 0x00, 0xf8, 0x1f, 0x08, 0x41, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xff, 0xdf, 0xd6, 0x9a, 0xd6, 0x9a, 0xd6, 0x9a, 0x00, 0x20, 0xd6, 0x9a, 0x00, 0x20, 0xd6, 0xba, 0x00, 0x00, 0x29, 0x45, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0x08, 0x41, 0x18, 0xe3, 0xd6, 0xba, 0xd6, 0xba, 0x00, 0x00, 0xd6, 0x9a, 0xd6, 0xba, 0xd6, 0xba, 0x00, 0x00, 0x8c, 0x72, 0x9d, 0x13, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xce, 0x59, 0x00, 0x00, 0xd6, 0xba, 0xd6, 0x9a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9c, 0xd3, 0xd6, 0xba, 0x9c, 0xf3, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x94, 0x92, 0x94, 0xb2, 0x94, 0xb2, 0x94, 0xb2, 0xd6, 0xda, 0x08, 0x41, 0x52, 0x8a, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x31, 0xa6, 0x31, 0x86, 0x39, 0xc7, 0xbd, 0xf7, 0x21, 0x44, 0x21, 0x44, 0x21, 0x44, 0x21, 0x44, 0x31, 0xa6, 0xb5, 0xb6, 0xce, 0x59, 0xf8, 0x1f, 0x29, 0x65, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xad, 0x55, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f,
};

const uint8_t PROGMEM level[LEVEL_WIDTH * LEVEL_HEIGHT] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 4, 0, 2, 2, 2, 2, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int playerModel[][6] = {
  { -50, -50, 0, 50, 50, 100},
  {10, -30, 0, 30, -10, 0},
  { -30, -30, 0, -10, -10, 0},
  { -30, 20, 0, 30, 35, 0},
};

int hexagonModel[][6] = {
  { -50, -90, 0, 50, 10, 100},
  {10, -70, 0, 30, -50, 0},
  { -30, -70, 0, -10, -50, 0},
  { -30, -20, 0, 30, -5, 0},
  { -100, 10, -50, 100, 50, 150},
};

uint8_t getBlock(uint8_t x, uint8_t y) {
  return pgm_read_byte(&level[x + y * LEVEL_WIDTH]);
}

bool isFull(uint8_t block) {
  return block == 1 || block == 2;
}

struct Player {
  float dx, dy, x, y, ySpeed;
  bool onGround;
  uint32_t t;

  Player() {
  }

  Player(uint16_t x1, uint16_t y1) {
    t = millis();
    dx = 1;
    dy = 0;
    x = x1;
    y = y1;
  }

  void drawRotated(float startX, float startY, float startZ, float endX, float endY, float endZ) {
    vec2f start = vec2f(startX, startY) * vec2f(dx, dy);
    vec2f end = vec2f(endX, endY) * vec2f(dx, dy);
    oled::drawLine(x + PLAYER_SIZE / 2 + start.x * PLAYER_SIZE / 100 + worldOffsetX - startZ * depthValue / 100, y + PLAYER_SIZE / 2 + start.y * PLAYER_SIZE / 100 + worldOffsetY - startZ * depthValue / 100,
                   x + PLAYER_SIZE / 2 + end.x * PLAYER_SIZE / 100 + worldOffsetX - endZ * depthValue / 100, y + PLAYER_SIZE / 2 + end.y * PLAYER_SIZE / 100 + worldOffsetY - endZ * depthValue / 100,
                   BLUE, 1);
  }

  void draw() {
    if (!started) {
      float time = (millis() - t) / 700.0;
      dx = sinf(time);
      dy = cosf(time);
    }
    vec2f newDelta = vec2f(dx, dy).normalized();
    dx = newDelta.x;
    dy = newDelta.y;
    if (hexagon) {
      for (int i = 0; i < sizeof(hexagonModel) / sizeof(hexagonModel[0]); i++) {
        int startX = hexagonModel[i][0], startY = hexagonModel[i][1], startZ = hexagonModel[i][2],
            endX = hexagonModel[i][3], endY = hexagonModel[i][4], endZ = hexagonModel[i][5];
        drawRotated(startX, startY, startZ, endX, startY, startZ);
        drawRotated(startX, startY, startZ, startX, endY, startZ);
        drawRotated(endX, startY, startZ, endX, endY, startZ);
        drawRotated(startX, endY, startZ, endX, endY, startZ);
        drawRotated(startX, startY, endZ, endX, startY, endZ);
        drawRotated(startX, startY, endZ, startX, endY, endZ);
        drawRotated(endX, startY, endZ, endX, endY, endZ);
        drawRotated(startX, endY, endZ, endX, endY, endZ);
        drawRotated(startX, startY, startZ, startX, startY, endZ);
        drawRotated(endX, startY, startZ, endX, startY, endZ);
        drawRotated(startX, endY, startZ, startX, endY, endZ);
        drawRotated(endX, endY, startZ, endX, endY, endZ);
      }
    } else {
      for (int i = 0; i < sizeof(playerModel) / sizeof(playerModel[0]); i++) {
        int startX = playerModel[i][0], startY = playerModel[i][1], startZ = playerModel[i][2],
            endX = playerModel[i][3], endY = playerModel[i][4], endZ = playerModel[i][5];
        drawRotated(startX, startY, startZ, endX, startY, startZ);
        drawRotated(startX, startY, startZ, startX, endY, startZ);
        drawRotated(endX, startY, startZ, endX, endY, startZ);
        drawRotated(startX, endY, startZ, endX, endY, startZ);
        drawRotated(startX, startY, endZ, endX, startY, endZ);
        drawRotated(startX, startY, endZ, startX, endY, endZ);
        drawRotated(endX, startY, endZ, endX, endY, endZ);
        drawRotated(startX, endY, endZ, endX, endY, endZ);
        drawRotated(startX, startY, startZ, startX, startY, endZ);
        drawRotated(endX, startY, startZ, endX, startY, endZ);
        drawRotated(startX, endY, startZ, startX, endY, endZ);
        drawRotated(endX, endY, startZ, endX, endY, endZ);
      }
    }
  }

  bool collides() {
    for (int x1 = (x + 1) / BLOCK_SIZE; x1 <= (x + PLAYER_SIZE - 1) / BLOCK_SIZE; x1++) {
      for (int y1 = (y + 1) / BLOCK_SIZE; y1 <= (y + PLAYER_SIZE - 1) / BLOCK_SIZE; y1++) {
        if (getBlock(x1, y1) == 1) {
          return true;
        } else if (getBlock(x1, y1) == 2) {
          alive = false;
        } else if (getBlock(x1, y1) == 3) {
          depth = true;
        } else if (getBlock(x1, y1) == 4) {
          hexagon = true;
        } else if (getBlock(x1, y1) == 5) {
          onGround = true;
        } else if (getBlock(x1, y1) == 6 && !callbackActive) {
          ySpeed *= -1;
          flipped = !flipped;
          callbackActive = true;
        } else if (getBlock(x1, y1) == 7) {
          hexagon = false;
        } else if (getBlock(x1, y1) == 9) {
          wind = completed = true;
          saveProfile();
        }
      }
    }
    return false;
  }

  void move() {
    onGround = false;
    for (float i = 0; i < abs(dx * dt); i += MOVE_STEP) {
      x += MOVE_STEP * sign(dx);
      if (collides()) {
        x -= MOVE_STEP * sign(dx);
        alive = false;
        break;
      }
    }
    for (float i = 0; i < abs(dy * dt); i += MOVE_STEP) {
      y += MOVE_STEP * sign(dy);
      if (collides()) {
        y -= MOVE_STEP * sign(dy);
        callbackActive = false;
        onGround = true;
        ySpeed = 0;
        dy = 0;
        break;
      }
    }
  }

  void update() {
    if (hexagon && buttonX.bHeld || onGround) {
      if (buttonX.bHeld) {
        ySpeed = -JUMP_FORCE;
      }
    } else {
      ySpeed += GRAVITY_FORCE * dt;
    }
    dx = started ? 7 : 0;
    dy = flipped ? -ySpeed : ySpeed;
    move();
    if (y < 0) {
      alive = false;
    }
    if (x > LEVEL_WIDTH * BLOCK_SIZE - PLAYER_SIZE) x = 0;
    worldOffsetX = oled::width / 2 - PLAYER_SIZE / 2 - x;
    if (y + worldOffsetY > oled::height - PLAYER_SIZE - CAMERA_PADDING) worldOffsetY = oled::height - y - PLAYER_SIZE - CAMERA_PADDING;
    if (y + worldOffsetY < CAMERA_PADDING) worldOffsetY = CAMERA_PADDING - y;
    if (worldOffsetX > -1) worldOffsetX = -1;
    if (worldOffsetY > -1) worldOffsetY = -1;
    if (worldOffsetX < LEVEL_WIDTH * -BLOCK_SIZE + oled::width) worldOffsetX = LEVEL_WIDTH * -BLOCK_SIZE + oled::width;
    if (worldOffsetY < LEVEL_HEIGHT * -BLOCK_SIZE + oled::height) worldOffsetY = LEVEL_HEIGHT * -BLOCK_SIZE + oled::height;
  }
};

Player player;

void draw() {
  oled::clear();
  player.draw();
  for (int x = worldOffsetX / -BLOCK_SIZE - 1; x < worldOffsetX / -BLOCK_SIZE + oled::width / BLOCK_SIZE + 2; x++) {
    for (int y = worldOffsetY / -BLOCK_SIZE - 1; y < worldOffsetY / -BLOCK_SIZE + oled::height / BLOCK_SIZE + 2; y++) {
      if (getBlock(x, y) == 1) {
        oled::fillRect(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY, BLOCK_SIZE, BLOCK_SIZE, 0x0008);
        oled::drawRect(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY, BLOCK_SIZE, BLOCK_SIZE, BLUE);
        if (depth) {
          if (x > 0 && !isFull(getBlock(x - 1, y))) { // Depth Left
            if (y > 0 && !isFull(getBlock(x - 1, y - 1))) {
              oled::drawFastVLine(x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY - depthValue, BLOCK_SIZE, BLUE);
              oled::drawLine(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY, x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY - depthValue, BLUE);
            } else {
              oled::drawFastVLine(x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY, BLOCK_SIZE - depthValue, BLUE);
            }
            oled::drawLine(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE, x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY - depthValue + BLOCK_SIZE, BLUE);
          }
          if (y > 0 && !isFull(getBlock(x, y - 1))) { // Depth Top
            if (x > 0 && !isFull(getBlock(x - 1, y - 1))) {
              oled::drawFastHLine(x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY - depthValue, BLOCK_SIZE, BLUE);
              oled::drawLine(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY, x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY - depthValue, BLUE);
            } else {
              oled::drawFastHLine(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY - depthValue, BLOCK_SIZE - depthValue, BLUE);
            }
            oled::drawLine(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE, y * BLOCK_SIZE + worldOffsetY, x * BLOCK_SIZE + worldOffsetX - depthValue + BLOCK_SIZE, y * BLOCK_SIZE + worldOffsetY - depthValue, BLUE);
          }
        }
      } else if (getBlock(x, y) == 2) {
        if (depth) {
          oled::drawLine(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY - depthValue / 2, BLUE);
          oled::drawLine(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY - depthValue / 2, BLUE);
          oled::drawLine(x * BLOCK_SIZE + worldOffsetX - depthValue, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE - depthValue, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY - depthValue / 2, BLUE);
        } else {
          oled::drawLine(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2, y * BLOCK_SIZE + worldOffsetY, BLUE);
          oled::drawLine(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2, y * BLOCK_SIZE + worldOffsetY, BLUE);
        }
      } else if (getBlock(x, y) == 3) {
        oled::drawLine(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY - depthValue / 2, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE - depthValue / 2, BLUE);
        oled::fillRect(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2 - 1, y * BLOCK_SIZE + worldOffsetY - depthValue / 2 - 1, 3, 3, BLUE);
      } else if (getBlock(x, y) == 4) {
        oled::drawLine(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY - depthValue / 2, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE - depthValue / 2, RED);
        oled::fillRect(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2 - 1, y * BLOCK_SIZE + worldOffsetY - depthValue / 2 - 1, 3, 3, RED);
      } else if (getBlock(x, y) == 5) {
        oled::fillRect(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2 - SQ_SIZE / 2, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE / 2 - depthValue / 2 - SQ_SIZE / 2, SQ_SIZE, SQ_SIZE, BLUE);
      } else if (getBlock(x, y) == 6) {
        oled::fillRect(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2 - SQ_SIZE / 2, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE / 2 - depthValue / 2 - SQ_SIZE / 2, SQ_SIZE, SQ_SIZE, RED);
      } else if (getBlock(x, y) == 7) {
        oled::drawLine(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY - depthValue / 2, x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2, y * BLOCK_SIZE + worldOffsetY + BLOCK_SIZE - depthValue / 2, GREEN);
        oled::fillRect(x * BLOCK_SIZE + worldOffsetX + BLOCK_SIZE / 2 - depthValue / 2 - 1, y * BLOCK_SIZE + worldOffsetY - depthValue / 2 - 1, 3, 3, GREEN);
      } else if (getBlock(x, y) == 9 && !wind) {
        oled::drawImage(x * BLOCK_SIZE + worldOffsetX, y * BLOCK_SIZE + worldOffsetY, 16, 16, windImage, MAGENTA);
      }
    }
  }
  gui::drawFPS();
  drawFrame();
}

void run(uint16_t x, uint16_t y) {
  completed = false;
  while (!completed) {
    depthValue = 0;
    started = depth = hexagon = flipped = callbackActive = false;
    player = Player(x, y);
    deltaTime();
    alive = true;
    while (alive && !completed) {
      updateController();
      if (buttonY.bReleased) return;
      dt = deltaTime();
      player.update();
      if (!started && player.onGround) {
        started = true;
      }
      if (depth == true && depthValue < DEPTH) {
        depthValue++;
      }
      draw();
    }
  }
}
}
