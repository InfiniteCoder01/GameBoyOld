#include "pokemon.hpp"

namespace asteroids {
const uint8_t PROGMEM asteroid[] = {
  0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x4a, 0x69, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x4a, 0x69, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0x4a, 0x69, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f,
};

const uint8_t PROGMEM tank[] = {
  0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xe6, 0x1b, 0xe6, 0x1b, 0xe6, 0x1b, 0xe6, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xe6, 0x1b, 0xe6, 0x1b, 0xe6, 0x1b, 0xe6, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x09, 0xc3, 0x09, 0xc3, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0xf8, 0x1f, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xe6, 0x1b, 0xe6, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x09, 0xc3, 0x09, 0xc3, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x09, 0xc3, 0x09, 0xc3, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x09, 0xc3, 0x09, 0xc3, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x09, 0xc3, 0x09, 0xc3, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0xf8, 0x1f, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x1b, 0xc6, 0x1b, 0xc6, 0x1b, 0xc6, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x25, 0x89, 0x25, 0x89, 0x25, 0x89,
};

const uint8_t PROGMEM activePortal[] = {
  0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x4a, 0xdf, 0x4a, 0xdf, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x31, 0xf6, 0x31, 0xf6, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x29, 0x70, 0x29, 0x70, 0x29, 0x70, 0x29, 0x70, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x29, 0x70, 0x19, 0x0b, 0x19, 0x0b, 0x19, 0x0b, 0x19, 0x0b, 0x29, 0x70, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x29, 0x70, 0x19, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x19, 0x0b, 0x29, 0x70, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x29, 0x70, 0x19, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x19, 0x0b, 0x29, 0x70, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x29, 0x70, 0x19, 0x0b, 0x19, 0x0b, 0x19, 0x0b, 0x19, 0x0b, 0x29, 0x70, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x29, 0x70, 0x29, 0x70, 0x29, 0x70, 0x29, 0x70, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x31, 0xf6, 0x31, 0xf6, 0x31, 0xf6, 0x31, 0xf6, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x4a, 0xdf, 0x4a, 0xdf, 0x4a, 0xdf, 0x4a, 0xdf, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f,
};

const uint8_t PROGMEM inactivePortal[] = {
  0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0xc6, 0x18, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0x7b, 0xef, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f,
};

const int FIRE_TIMEOUT = 500, SPEED = 8, BULLET_SPEED = 7, ASTEROID_SPEED = 5, FIRE_TIMER = 300, MAX_BULLETS = 3;
int ASTEROID_TIMER, asteroidsKilled, portalX, portalY;
bool running, ingame, portal;
float x, dt;

/*               STRUCTURES               */

struct Asteroid {
  float x, y;

  Asteroid() {
    x = random(0, oled::width - 16);
    y = -16;
  }

  void update() {
    y += ASTEROID_SPEED * dt;
  }

  void draw() {
    oled::drawImage(x, y, 16, 16, asteroid, MAGENTA);
  }
};

struct Bullet {
  float x, y;

  Bullet() {}
  Bullet(float x, float y) : x(x), y(y) {}

  void update() {
    y -= BULLET_SPEED * dt;
  }

  void draw() {
    oled::fillRect(x - 1, y - 1, 3, 3, WHITE);
  }
};

LinkedList<Bullet> bullets;
LinkedList<Asteroid> asteroids;

bool allInPlace() {
  return mario::fire && water && cuby::earth && geometry::wind;
}

/*               MAIN LOOP               */

void init() {
  x = 56;
  ingame = running = true;
  bullets.clear();
  asteroids.clear();
  ASTEROID_TIMER = 2000;
  asteroidsKilled = 0;
  portal = false;
}

void update() {
  static uint32_t tBullet = millis(), tAsteroid = millis();
  if (buttonY.bReleased) ingame = running = false;
  x += joyX * SPEED * dt;
  x = constrain(x, 0, oled::width - 16);
  if (buttonX.bHeld && millis() - tBullet > FIRE_TIMER && bullets.size() < MAX_BULLETS) {
    tBullet = millis();
    bullets.add(Bullet(x + 8, 110));
  }
  for (int i = 0; i < bullets.size(); i++) {
    bullets[i].update();
    if (portal) {
      if (inRangeW(bullets[i].x, portalX, 16) && inRangeW(bullets[i].y, portalY, 16) && allInPlace()) {
        bullets.clear();
        asteroids.clear();
        ingame = running = false;
        audio::stop();
        pokemon::run();
        return;
      }
    }
    if (!inRange(bullets[i].y, 0, oled::height)) bullets.remove(i);
  }
  if (!portal) {
    if (millis() - tAsteroid > ASTEROID_TIMER) {
      tAsteroid = millis();
      asteroids.add(Asteroid());
    }
    for (int i = 0; i < asteroids.size(); i++) {
      asteroids[i].update();
      if (asteroids[i].y > 96 && x < asteroids[i].x + 16 && x + 16 > asteroids[i].x) {
        running = false;
      }
      if (asteroids[i].y > oled::height) {
        asteroids.remove(i);
        continue;
      }
      for (int j = 0; j < bullets.size(); j++) {
        if (inRangeW(bullets[j].x, asteroids[i].x, 16) && inRangeW(bullets[j].y, asteroids[i].y, 16)) {
          asteroidsKilled++;
          ASTEROID_TIMER *= 0.95;
          if (asteroidsKilled > 10) {
            portalX = asteroids[i].x;
            portalY = asteroids[i].y;
            portal = true;
          }
          asteroids.remove(i);
          bullets.remove(j);
          break;
        }
      }
    }
  }
}

void draw() {
  oled::clear();
  oled::drawImage(x, 112, 16, 16, tank, MAGENTA);
  if (portal) {
    if (allInPlace()) oled::drawImage(portalX, portalY, 18, 18, activePortal, MAGENTA);
    else oled::drawImage(portalX, portalY, 18, 18, inactivePortal, MAGENTA);
  } else {
    for (int i = 0; i < asteroids.size(); i++) asteroids[i].draw();
  }
  for (int i = 0; i < bullets.size(); i++) bullets[i].draw();
  oled::setCursor(0, 0);
  oled::println(format("Score: %d!", asteroidsKilled));
  drawFrame();
}


void run() {
  deltaTime();
  do {
    init();
    while (running) {
      if (!audio::playing) {
        audio::play("/Music/Asteroids.wav");
      }
      dt = deltaTime();
      updateController();
      update();
      draw();
    }
  } while (ingame);
  audio::stop();
}
}
