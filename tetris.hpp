namespace tetris {
struct Tetromino;
const char* song = "/Music/Tetris/Tetris.wav";
const uint8_t FIELD_WIDTH = 10, FIELD_HEIGHT = 20, BLOCK_SIZE = 5, FIELD_BORDER = 2, TETROMINOS_COUNT = 7, ZONE_RADIUS = 5;
const uint8_t FIELD_X = oled::width / 2 - FIELD_WIDTH * (BLOCK_SIZE + 1) / 2, FIELD_Y = 0;
const uint16_t BLOCK_TIME = 500, ZONE_TIME = 20000, COLOR1 = RED, COLOR2 = BLUE; // 0xb0ff, 0xfff4
const uint8_t effectBlock[] = { 0xf8, 0xc8, 0xa8, 0x98, 0xf8 };
uint8_t field[FIELD_HEIGHT][FIELD_WIDTH];
bool tetrisEffect = false;
float zoneCharge = 0, offsetVelocity = 0, textSize;
uint16_t blockTime;
uint32_t zone = 0;
String text = "";
int offset = 0;

const uint16_t palette[] = { 0xE940, 0xFC81, 0xF6C0, 0x7EA0, 0x0C5F, 0xA97E, 0xFC81 };
//                                                       I               L            J                O               S            T            Z
const uint16_t tetrominos[TETROMINOS_COUNT] = { 0b0010001000100010, 0b100111000, 0b001111000, 0b0000011001100000, 0b011110000, 0b010111000, 0b110011000 };
const uint8_t tetrominoSizes[TETROMINOS_COUNT] = { 4, 3, 3, 4, 3, 3, 3 };

void draw();
void restartGame();
void checkClearLines(uint8_t y, uint8_t height);

void drawBlock(int x, int y, uint8_t block) {
  if (block == 0) return;
  int x1 = x * (BLOCK_SIZE + 1) + FIELD_X, y1 = y * (BLOCK_SIZE + 1) + FIELD_Y + offset;
  if (tetrisEffect) {
    if (block == 100) {
      oled::fillRect(x1, y1, BLOCK_SIZE + 1, BLOCK_SIZE + 1, WHITE);
    } else {
      uint16_t color = oled::interpolateColor(COLOR1, COLOR2, x / 2.f / FIELD_WIDTH + y / 2.f / FIELD_HEIGHT);
      oled::drawBitmap(x1, y1, BLOCK_SIZE, BLOCK_SIZE, effectBlock, color, color);
    }
  } else {
    oled::fillRect(x1, y1, BLOCK_SIZE, BLOCK_SIZE, palette[block - 1]);
    oled::setPixel(x1, y1, WHITE);
    oled::setPixel(x1 + 1, y1 + 1, WHITE);
    oled::setPixel(x1 + 2, y1 + 1, WHITE);
    oled::setPixel(x1 + 1, y1 + 2, WHITE);
  }
}

void drawBlockEdges(int x, int y, uint8_t block, bool north, bool east, bool south, bool west) {
  if (block == 0) return;
  int blockXOnScreen = x * (BLOCK_SIZE + 1) + FIELD_X, blockYOnScreen = y * (BLOCK_SIZE + 1) + FIELD_Y + offset;
  uint16_t color = palette[block - 1];
  if (tetrisEffect) color = oled::interpolateColor(COLOR1, COLOR2, x / 2.f / FIELD_WIDTH + y / 2.f / FIELD_HEIGHT);
  if (north) oled::drawFastHLine(blockXOnScreen, blockYOnScreen, BLOCK_SIZE + 1, color);
  if (east) oled::drawFastVLine(blockXOnScreen + BLOCK_SIZE + 1, blockYOnScreen, BLOCK_SIZE + 1, color);
  if (south) oled::drawFastHLine(blockXOnScreen, blockYOnScreen + BLOCK_SIZE + 1, BLOCK_SIZE + 1, color);
  if (west) oled::drawFastVLine(blockXOnScreen, blockYOnScreen, BLOCK_SIZE + 1, color);
}

struct Tetromino {
  int x, y, rotation;
  uint8_t type;

  void randomize() {
    blockTime = max(blockTime - 10, 300);
    rotation = 0;
    x = FIELD_WIDTH / 2 - 2;
    y = 0;
    type = max(random(TETROMINOS_COUNT + 3) - 3, 0l);
    if (!fit()) {
      if (millis() < zone) {
        zone = millis();
        place();
        randomize();
      } else {
        restartGame();
      }
    }
  }

  void place() {
    for (int y1 = 0; y1 < tetrominoSizes[type]; y1++) {
      for (int x1 = 0; x1 < tetrominoSizes[type]; x1++) {
        if (blockAt(x1, y1)) {
          field[y + y1][x + x1] = type + 1;
        }
      }
    }
    checkClearLines(y, tetrominoSizes[type]);
  }

  void rotate() {
    rotation = (rotation + 1) % 4;
    if (!fit()) rotation--;
    if (rotation < 0) rotation += 4;
  }

  bool blockAt(uint8_t x1, uint8_t y1) {
    if (!inRange(x1, 0, tetrominoSizes[type] - 1) || !inRange(y1, 0, tetrominoSizes[type] - 1)) return false;
    if (rotation == 0) return bitRead(tetrominos[type], y1 * tetrominoSizes[type] + x1);
    else if (rotation == 1)return bitRead(tetrominos[type], x1 * tetrominoSizes[type] + (tetrominoSizes[type] - 1 - y1));
    else if (rotation == 2) return bitRead(tetrominos[type], (tetrominoSizes[type] - 1 - y1) * tetrominoSizes[type] + (tetrominoSizes[type] - 1 - x1));
    else return bitRead(tetrominos[type], (tetrominoSizes[type] - 1 - x1) * tetrominoSizes[type] + y1);
  }

  bool fit() {
    for (int y1 = 0; y1 < tetrominoSizes[type]; y1++) {
      for (int x1 = 0; x1 < tetrominoSizes[type]; x1++) {
        if (blockAt(x1, y1) && (y + y1 >= FIELD_HEIGHT || !inRange(x + x1, 0, FIELD_WIDTH - 1) || field[y + y1][x + x1] != 0)) return false;
      }
    }
    return true;
  }

  void update() {
    static uint32_t t = millis();
    if (buttonX.bPressed) rotate();
    if (bJoyMoved) {
      x += joyX;
      if (!fit()) x -= joyX;
      if (joyY > 0) {
        while (fit()) {
          y++;
        }
        y--;
        if (tetrisEffect) offsetVelocity = 5;
        place();
        randomize();
      }
    }
    if (millis() - t > blockTime && zone == 0 || millis() - t > blockTime / 4 && buttonY.bHeld) {
      t = millis();
      y++;
      if (!fit()) {
        y--;
        place();
        randomize();
      }
    }
  }

  void draw() {
    if (!fit()) return;
    for (int y1 = 0; y1 < tetrominoSizes[type]; y1++) {
      for (int x1 = 0; x1 < tetrominoSizes[type]; x1++) {
        drawBlock(x + x1, y + y1, blockAt(x1, y1) * (type + 1));
      }
    }
    drawGhost();
  }

  void drawGhost() {
    int x1 = x, y1 = y;
    while (fit()) {
      y++;
    }
    y--;
    swap(y, y1);
    for (int blockY = 0; blockY < tetrominoSizes[type]; blockY++) {
      for (int blockX = 0; blockX < tetrominoSizes[type]; blockX++) {
        drawBlockEdges(x1 + blockX, y1 + blockY, blockAt(blockX, blockY) * (type + 1), !blockAt(blockX, blockY - 1), !blockAt(blockX + 1, blockY),
                       !blockAt(blockX, blockY + 1), !blockAt(blockX - 1, blockY));
      }
    }
  }
};
Tetromino tetromino;

void checkClearLines(uint8_t y, uint8_t height) {
  bool* lines = new bool[height];
  int nLines = 0;
  for (int y1 = 0; y1 < height; y1++) {
    lines[y1] = true;
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (field[y + y1][x] == 0) {
        lines[y1] = false;
      }
    }
    if (lines[y1]) nLines++;
  }
  if (nLines == 0) return;
  if (millis() < zone) {
    for (int y1 = height - 1; y1 >= 0; y1--) {
      if (!lines[y1]) continue;
      for (int y2 = y + y1 + 1; y2 < FIELD_HEIGHT; y2++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
          field[y2 - 1][x] = field[y2][x];
        }
      }
      for (int x = 0; x < FIELD_WIDTH; x++) {
        field[FIELD_HEIGHT - 1][x] = 100;
      }
    }
  } else {
    if (tetrisEffect) {
      zoneCharge += 0.125 * nLines;
      for (int y1 = 0; y1 < height; y1++) {
        if (!lines[y1]) continue;
        for (int x = 0; x < FIELD_WIDTH; x++) {
          field[y + y1][FIELD_WIDTH - x - 1] = 100;
          field[y + y1][x] = 100;
        }
      }
      draw();
      delay(100);
      for (int y1 = 0; y1 < height; y1++) {
        if (!lines[y1]) continue;
        for (int x = 0; x < FIELD_WIDTH; x++) {
          field[y + y1][x] = 0;
        }
      }
    } else {
      for (int x = FIELD_WIDTH / 2; x < FIELD_WIDTH; x++) {
        for (int y1 = 0; y1 < height; y1++) {
          if (!lines[y1]) continue;
          field[y + y1][FIELD_WIDTH - x - 1] = 0;
          field[y + y1][x] = 0;
        }
        draw();
        delay(50);
      }
      if (nLines >= 3) tetrisEffect = true;
    }
    for (int y1 = 0; y1 < height; y1++) {
      if (!lines[y1]) continue;
      for (int y2 = y + y1 - 1; y2 >= 0; y2--) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
          field[y2 + 1][x] = field[y2][x];
          field[y2][x] = 0;
        }
      }
    }
  }
  delete[] lines;
}

void restartGame() {
  deltaTime();
  zone = 0;
  zoneCharge = 0;
  text = "";
  textSize = 5;
  blockTime = BLOCK_TIME;
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      field[y][x] = 0;
    }
  }
}

void draw() {
  oled::clear();
  oled::fillRect(FIELD_X - FIELD_BORDER, FIELD_Y + offset, FIELD_BORDER, FIELD_HEIGHT * (BLOCK_SIZE + 1), 0x3CB8);
  oled::fillRect(FIELD_X + FIELD_WIDTH * (BLOCK_SIZE + 1), FIELD_Y + offset, FIELD_BORDER, FIELD_HEIGHT * (BLOCK_SIZE + 1), 0x3CB8);
  oled::fillRect(FIELD_X - FIELD_BORDER, FIELD_Y + FIELD_HEIGHT * (BLOCK_SIZE + 1) + offset, FIELD_WIDTH * (BLOCK_SIZE + 1) + FIELD_BORDER * 2, FIELD_BORDER, 0x3CB8);
  for (int y = 0; y < FIELD_HEIGHT; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      drawBlock(x, y, field[y][x]);
    }
  }
  tetromino.draw();

  if (tetrisEffect) {
    float zoneMeter = float(zone - millis()) / ZONE_TIME;
    if (zone == 0) {
      zoneCharge = min(zoneCharge, 1.f);
      zoneMeter = zoneCharge;
    }
    zoneMeter *= 3.1415 * 2;
    int posX = (FIELD_X - FIELD_BORDER) / 2, posY = ZONE_RADIUS + 5;
    for (float x = 0; x < 3.1415 * 2; x += 1 / (3.1415 * 2 * (ZONE_RADIUS + 3))) {
      float dx = cos(x + 3.1415 * 1.5), dy = sin(x + 3.1415 * 1.5);
      if (x < zoneMeter) {
        oled::setPixel(round(dx * (ZONE_RADIUS + 1)) + posX, round(dy * (ZONE_RADIUS + 1)) + posY, CYAN);
        oled::setPixel(round(dx * (ZONE_RADIUS + 2)) + posX, round(dy * (ZONE_RADIUS + 2)) + posY, CYAN);
      }
      oled::setPixel(round(dx * ZONE_RADIUS) + posX, round(dy * ZONE_RADIUS) + posY, CYAN);
      oled::setPixel(round(dx * (ZONE_RADIUS + 3)) + posX, round(dy * (ZONE_RADIUS + 3)) + posY, CYAN);
    }
  }
  if (textSize < 5) {
    oled::setTextSize(min(textSize, 1.f));
    oled::wrap = false;
    gui::centerText(text);
    oled::setTextSize(1);
    oled::wrap = true;
  }
  drawFrame();
}

void run() {
  restartGame();
  tetromino.randomize();
  float dt;
  const char* _song;
  while (true) {
    if (!audio::playing || _song != song) {
      _song = song;
      audio::play(_song);
    }
    updateController();
    dt = deltaTime();
    tetromino.update();
    if (buttonY.bReleased) {
      if (zoneCharge > 0.9) {
        zone = millis() + ZONE_TIME;
        zoneCharge = 0;
      }
    }

    offset = constrain(offset + offsetVelocity * dt, 0, 5);
    offsetVelocity = constrain(offsetVelocity - 2 * dt, -5, 5);
    textSize = min(textSize + dt * 0.2f, 5.f);
    animator::update();

    if (tetrisEffect) {
      int top = 0;
      for (int y = FIELD_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
          if (field[y][x] == 0) {
            top = FIELD_HEIGHT - y - 1;
            break;
          }
        }
        if (top != 0) break;
      }
      if (top >= 10) {
        song = "/Music/Tetris/Tetris99_10.wav";
      } else if (zone != 0) {
        song = "/Music/Tetris/Tetris99_50.wav";
      } else {
        song = "/Music/Tetris/Tetris99.wav";
      }

      if (millis() > zone - 10 && zone != 0) {
        zone = 0;
        for (int y = FIELD_HEIGHT - top; y < FIELD_HEIGHT; y++) {
          for (int x = 0; x < FIELD_WIDTH; x++) field[y][x] = 0;
        }
        for (int y = FIELD_HEIGHT - top - 1; y >= 0; y--) {
          for (int x = 0; x < FIELD_WIDTH; x++) {
            field[y + top][x] = field[y][x];
            field[y][x] = 0;
          }
        }
        if (top >= 4) {
          textSize = 0.2;
          if (top >= 16) text = "DECAHEXATRIS";
          else if (top >= 12) text = "DODECATRIS";
          else if (top >= 8) text = "OCTORIS";
          else text = "TETRIS";
        }
      }
    }

    draw();
  }
}
}
