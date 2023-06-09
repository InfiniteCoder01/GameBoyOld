#include "geometry.hpp"

namespace cuby {
bool earth;
uint8_t cubyX, cubyY;
const uint8_t LEVEL_WIDTH = 8, LEVEL_HEIGHT = 8, LEVEL_COUNT = 5;
const uint8_t LEVEL_CHARS[LEVEL_COUNT][2] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}, {6, 6}};
const uint8_t PROGMEM bricks[] = {
  0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0x00, 0x00, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xe8, 0xe4, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0xa0, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM flag[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM cuby[] = {
  0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80, 0xff, 0x80,
};

const uint8_t PROGMEM earthImage[] = {
  0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x40, 0xff, 0xfe, 0x00, 0x40, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x20, 0x07, 0xe0, 0x0f, 0x81, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x07, 0xc0, 0x0d, 0x20, 0x07, 0xe0, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x20, 0x00, 0x00, 0xf7, 0xbe, 0x07, 0xe0, 0x0f, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x0d, 0x40, 0x00, 0x20, 0x00, 0x20, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0f, 0xc1, 0x07, 0xe0, 0x05, 0x40, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x05, 0x20, 0x08, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0x08, 0x00, 0xf7, 0xff, 0x07, 0xa0, 0x0f, 0xe1, 0x07, 0xc0, 0x07, 0xe0, 0x07, 0xe0, 0x10, 0x00, 0x07, 0xe0, 0x05, 0x80, 0x07, 0xe0, 0x05, 0x20, 0x08, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x08, 0x81, 0x07, 0xe0, 0x07, 0xe0, 0x05, 0x60, 0x07, 0xe0, 0x07, 0xa1, 0x08, 0x00, 0x05, 0xa0, 0x07, 0xe0, 0x0f, 0x62, 0x05, 0x20, 0x05, 0x20, 0x08, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0xe7, 0xdb, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x06, 0xc1, 0x00, 0xa0, 0x05, 0x60, 0x07, 0xe0, 0x0f, 0x40, 0x05, 0x20, 0x05, 0x20, 0x05, 0x20, 0x08, 0x00, 0xf8, 0x1f, 0x18, 0xc3, 0xf7, 0x9e, 0x07, 0xc0, 0x05, 0x80, 0x07, 0xe0, 0x08, 0x64, 0x1d, 0x23, 0x17, 0x83, 0x07, 0xc1, 0x05, 0x60, 0x05, 0x20, 0x05, 0x20, 0x05, 0x20, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x04, 0xe1, 0x07, 0xe0, 0x07, 0xc0, 0x05, 0x40, 0x05, 0x20, 0x05, 0x40, 0x0d, 0x80, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x07, 0xe0, 0x07, 0xe0, 0x00, 0x00, 0x04, 0xe1, 0x07, 0xe0, 0x05, 0x40, 0x05, 0x20, 0x05, 0x40, 0x07, 0xc0, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x21, 0x07, 0xe0, 0x00, 0x00, 0x04, 0xe1, 0x05, 0x20, 0x05, 0x20, 0x05, 0x20, 0x07, 0xe0, 0x00, 0x01, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x04, 0xe1, 0x05, 0x20, 0x05, 0x20, 0x07, 0xe0, 0x00, 0x60, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x04, 0xe1, 0x05, 0x20, 0x07, 0xe0, 0x08, 0x40, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f,
};

const char PROGMEM LEVELS[LEVEL_COUNT][LEVEL_HEIGHT][LEVEL_WIDTH + 1] = {
  {
    "########",
    "# #.#  #",
    "#   #  #",
    "# ### ##",
    "#  #   #",
    "#  #   #",
    "#     !#",
    "########"
  },
  {
    "########",
    "#  #  !#",
    "#  #   #",
    "#      #",
    "#  #   #",
    "#  #   #",
    "#      #",
    "########"
  },
  {
    "########",
    "#    # #",
    "#!     #",
    "#   #  #",
    "##     #",
    "#     ##",
    "#  #   #",
    "########"
  },
  {
    "########",
    "#  #   #",
    "#!     #",
    "#      #",
    "#      #",
    "#   ####",
    "# #    #",
    "########"
  },
  {
    "########",
    "#  #!!!#",
    "#      #",
    "#      #",
    "#      #",
    "#   ####",
    "#e#    #",
    "########"
  }
};

void drawLevel(uint8_t index) {
  for (uint8_t x = 0; x < LEVEL_WIDTH; x++) {
    for (uint8_t y = 0; y < LEVEL_HEIGHT; y++) {
      switch (pgm_read_byte(&LEVELS[index][y][x])) {
        case '#':
          oled::fastDrawImage(x * 16, y * 16, 16, 16, bricks);
          break;
        case '.':
          oled::fillRect(x * 16, y * 16, 16, 16, 0x0002);
          oled::setCursor(x * 16, y * 16);
          oled::print("GD");
          break;
        case 'e':
          if (!earth) oled::drawImage(x * 16, y * 16, 16, 16, earthImage, MAGENTA);
          break;
        case '!':
          oled::fastDrawImage(x * 16, y * 16, 16, 16, flag);
          break;
      }
    }
  }
}

void run() {
  for (uint8_t i = 0; i < LEVEL_COUNT; i++) {
    cubyX = LEVEL_CHARS[i][0];
    cubyY = LEVEL_CHARS[i][1];
    while (true) {
      updateController();
      if (buttonY.bReleased) {
        return;
      }
      drawFrame();
      uint8_t oldCubyX = cubyX, oldCubyY = cubyY;
      if (joyX != 0 || joyY != 0) {
        while (pgm_read_byte(&LEVELS[i][cubyY + joyY][cubyX + joyX]) != '#') {
          cubyX += joyX;
          cubyY += joyY;
        }
      }
      oled::clear();
      drawLevel(i);
      oled::fastDrawImage(cubyX * 16 + 4, cubyY * 16 + 4, 8, 8, cuby);
      drawFrame();
      if (pgm_read_byte(&LEVELS[i][cubyY][cubyX]) == '!') {
        break;
      } else if (pgm_read_byte(&LEVELS[i][cubyY][cubyX]) == '.') {
        oled::fillScreen(BLACK);
        oled::drawRect(cubyX * 16, cubyY * 16, geometry::PLAYER_SIZE, geometry::PLAYER_SIZE, BLUE);
        for (int i = 0; i <= oled::height - cubyY * 16 - 16; i += 3) {
          oled::update(max(cubyX * 16 - i, 0), max(cubyY * 16 - i, 0),
                       min(16 + i * 2, int(oled::width)), min(16 + i * 2, int(oled::height)));
          yield();
        }
        geometry::run(cubyX * 16, cubyY * 16);
        return;
      } else if (pgm_read_byte(&LEVELS[i][cubyY][cubyX]) == 'e') {
        oled::fillRect(cubyX * 16, cubyY * 16, 16, 16, BLACK);
        oled::fastDrawImage(cubyX * 16 + 4, cubyY * 16 + 4, 8, 8, cuby);
        oled::update(cubyX * 16, cubyY * 16, 16, 16);
        earth = true;
        saveProfile();
      }
    }
  }
  gui::centerText("You win!");
  drawFrame();
  delay(5000);
}
}
