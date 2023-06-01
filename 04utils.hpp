using namespace math;
typedef void (*Function)();

String inputText(String title) {
  String charset = "abcdefghijklmnopqrstuvwxyz</";
  String text = "";
  int selected = 0;
  while (true) {
    updateController();
    if (bJoyMoved) {
      selected += joyX;
      if (selected < 0) selected = charset.length() - 1;
      if (selected >= charset.length()) selected = 0;
      if (buttonX.bReleased) {
        if (charset[selected] == '<') text.remove(text.length() - 1);
        else if (charset[selected] == '/') return text;
        else text += charset[selected];
      }
    }
    oled::clear();
    gui::centerText(title, 0);
    gui::centerText(text, oled::getCharHeight());
    gui::centerText(format(" %c > %c < %c ", charset[selected - 1], charset[selected], charset[selected + 1]));
    oled::update();
  }
  return "";
}

float deltaTime() {
  static uint32_t t;
  uint32_t delta = millis() - t;
  t = millis();
  return delta / 100.0;
}

uint8_t hexToInt(char c) {
  if (inRange(c, '0', '9')) {
    return c - '0';
  } else if (inRange(c, 'a', 'f')) {
    return c - 'a' + 10;
  } else if (inRange(c, 'A', 'F')) {
    return c - 'A' + 10;
  }
  return 0;
}

char intToHex(uint8_t i) {
  if (inRange(i, 0, 9)) {
    return i + '0';
  }
  return i - 10 + 'a';
}

uint8_t readHexByte(File& file) {
  return hexToInt(file.read()) << 4 | hexToInt(file.read());
}

uint16_t readHexWord(File& file) {
  return hexToInt(file.read()) << 12 | hexToInt(file.read()) << 8 | hexToInt(file.read()) << 4 | hexToInt(file.read());
}

void writeHexByte(File& file, uint8_t val) {
  file.write(intToHex(val >> 4));
  file.write(intToHex(val & 0xf));
}

void writeHexWord(File& file, uint16_t val) {
  file.write(intToHex(val >> 12));
  file.write(intToHex(val >> 8 & 0xf));
  file.write(intToHex(val >> 4 & 0xf));
  file.write(intToHex(val & 0xf));
}

LinkedList<uint8_t>* readBytes(String path) {
  LinkedList<uint8_t>* data = new LinkedList<uint8_t>;
  File file = SD.open(path, "r");
  while (file.available()) {
    //    data->add(file.read());
    data->add(readHexByte(file));
  }
  file.close();
  return data;
}

void saveBytes(String path, LinkedList<uint8_t>* data) {
  File file = SD.open(path, "w");
  for (int i = 0; i < data->size(); i++) {
    //    file.write(data->get(i));
    writeHexByte(file, data->get(i));
  }
  file.close();
  delete data;
}

void removeDir(String path) {
  if (!SD.exists(path)) return;
  File root = SD.open(path);
  LinkedList<String> filesToRemove;
  while (File entry = root.openNextFile()) {
    filesToRemove.add(path + '/' + entry.name());
    entry.close();
  }
  while (filesToRemove.size() > 0) {
    SD.remove(filesToRemove[0]);
    filesToRemove.remove(0);
  }
  SD.rmdir(path);
}

bool writeFinish = false;
void drawElements();

void drawFrame() {
  drawElements();

  while (!writeFinish) yield();
  oled::swapBuffers();
  writeFinish = false;
}

void outputTask(void* arg) {
  while (true) {
    vTaskDelay(1);
    audio::loop();
    while (writeFinish) vTaskDelay(1);
    oled::update();
    writeFinish = true;
    while (writeFinish) vTaskDelay(1);
  }
}

void wait(int ms) {
  uint32_t t = millis();
  while (millis() - t < ms) drawFrame();
}
