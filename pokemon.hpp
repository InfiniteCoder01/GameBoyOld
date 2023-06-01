#include "pokemonScript.hpp"
#include "pokemonStruct.hpp"

namespace pokemon {
const String names[CHARACTERS_COUNT] = { "Player", "Mom", "May" };
int menuPointer = 0;
uint32_t tTextStart;
String text;
bool running;
LinkedList<Pair<String, Function>*> menu;
LinkedList<Pair<int, Object*>*> transferableObjects;
LinkedList<int> transferedObjects;

/*             FUNCTION DEFENITION             */
void addText(String _text) {
  text = _text;
  tTextStart = millis();
  lockPlayerControls = true;
}

bool hasText() {
  return text.length() > 0;
}

void addToMenu(String item, Function callback) {
  menu.add(new Pair<String, Function>(item, callback));
  lockPlayerControls = true;
}

void closeMenu() {
  while (menu.size() > 0) {
    delete menu[0];
    menu.remove(0);
  }
  lockPlayerControls = false;
  menuPointer = 0;
}

bool hasMenu() {
  return menu.size() > 0;
}

void transferObject(Object* object, int scene) {
  for (int i = 0; i < engineData::objects.size(); i++) {
    if (engineData::objects[i] == object) {
      transferableObjects.add(new Pair<int, Object*>(scene, object));
      transferedObjects.add(i);
      return;
    }
  }
}

int nameToID(String name) {
  for (int i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
    if (names[i] == name) {
      return i;
    }
  }
  return -1;
}

/*             SAVE & LOAD             */
void saveGame(int newSceneIndex) {
  audio::pause();
  drawFrame();
  saveBytes(format("/profiles/%s/pokemon/data.txt", profilename), serialize("u1si2u4", newSceneIndex, &script::operation, script::id, script::index));
  saveBytes(format("/profiles/%s/pokemon/scenes/%d.txt", profilename, sceneIndex), saveLevel());
  audio::resume();
}

void loadScene(int index) {
  audio::pause();
  drawFrame();
  if (SD.exists(format("/profiles/%s/pokemon/scenes/%d.txt", profilename, index))) {
    loadSavedLevel(index, readBytes(format("/profiles/%s/pokemon/scenes/%d.txt", profilename, index)));
  } else {
    loadLevel(index);
  }
  sceneIndex = index;
  LinkedList<int> objectsToRemove;
  for (int i = transferableObjects.size() - 1; i >= 0; i--) {
    if (transferableObjects[i]->val_1 == sceneIndex) {
      Object* object = transferableObjects[i]->val_2;
      object->x = player->x;
      object->y = player->y;
      engineData::objects.add(object);
      delete transferableObjects[i];
      objectsToRemove.add(i);
    }
  }
  for (int i = 0; i < objectsToRemove.size(); i++) {
    transferableObjects.remove(objectsToRemove[i]);
  }
  audio::resume();
}

void loadGame() {
  audio::pause();
  drawFrame();
  deserialize("u1si2u4", readBytes(format("/profiles/%s/pokemon/data.txt", profilename)), &sceneIndex, &script::operation, &script::id, &script::index);
  loadScene(sceneIndex);
  audio::resume();
}

void exitGame() {
  saveGame(sceneIndex);
  running = false;
}

/*             DRAWMENT             */
void drawMenu(LinkedList<Pair<String, Function>*>& menu, int& menuPointer) {
  int w = oled::width / 4 - 4, h = menu.size() * (oled::getCharHeight() + 3) + 6;
  int x = oled::width - w - 2, y = 2;
  oled::fillRect(x + 1, y + 1, w - 1, h - 1, WHITE);
  oled::drawRect(x, y, w, h, 0x2948);
  oled::setCursor(x + 4, y + 4);
  for (int i = 0; i < menu.size(); i++) {
    if (i == menuPointer) {
      oled::drawRect(oled::cursorX - 2, oled::cursorY - 2, w - 4, oled::getCharHeight() + 3, RED);
      if (buttonX.bReleased) {
        menu[i]->val_2();
      }
    }
    oled::println(menu[i]->val_1);
    oled::cursorX = x + 4;
    oled::cursorY += 2;
  }
  if (bJoyMoved) {
    menuPointer = wrap(menuPointer + joyY, menu.size());
  }
  if (buttonY.bReleased) {
    closeMenu();
  }
}

void drawText(String text) {
  int w = oled::width - 4, h = oled::height / 3 - 4;
  int x = 2, y = oled::height - h - 2;
  oled::fillRect(x + 1, y + 1, w - 2, h - 2, WHITE);
  oled::drawRect(x, y, w, h, 0x2948);
  gui::textAt(text, x + 3, y + 3);
}

void draw() {
  drawMap();
  if (hasText()) drawText(text.substring(0, min((unsigned int)(millis() - tTextStart) / 150, text.length())));
  if (hasMenu()) drawMenu(menu, menuPointer);
  gui::drawFPS();
}

void drawInventory() {
  while (true) {
    updateController();
    draw();
    drawFrame();
  }
}

/*             MAIN             */
void showStartMenu() {
  bool newGame = false;
  do {
    if (!audio::playing) {
      audio::play("/Music/Pokemon/Title.wav");
    }
    updateController();
    if (buttonY.bReleased) {
      newGame = true;
      break;
    }
    oled::drawBackground(startMenu);
    drawFrame();
  } while (!buttonX.bReleased);
  audio::stop();
  if (newGame || !SD.exists(format("/profiles/%s/pokemon/data.txt", profilename))) {
    String emptyOP = "";
    saveBytes(format("/profiles/%s/pokemon/data.txt", profilename), serialize("u1si2u4", 0, &emptyOP, 0, 0));
    removeDir(format("/profiles/%s/pokemon/scenes", profilename));
    SD.mkdir(format("/profiles/%s/pokemon/scenes", profilename));
  }
}

void run() {
  showStartMenu();
  setupEngine(16, data, createObject, depthObjectComparator);
  loadGame();
  oled::setFont(fontPico8);
  oled::setTextColor(0x2948);
  running = true;
  script::script = mainScript;
  while (running) {
    if (!audio::playing) {
      audio::play("/Music/Pokemon/Theme.wav");
    }
    updateController();

    transferedObjects.sort(bigToSmallComparator);
    while (transferedObjects.size() > 0) {
      engineData::objects.remove(transferedObjects[0]);
      transferedObjects.remove(0);
    }

    if (nextScene != -1) {
      saveGame(nextScene);
      loadScene(nextScene);
      nextScene = -1;
    }

    if (hasText() && buttonX.bReleased) {
      buttonX.bReleased = false;
      if ((millis() - tTextStart) / 150 < text.length()) {
        tTextStart = 0;
      } else {
        text = "";
        lockPlayerControls = false;
      }
    }

    if (!hasMenu() && buttonY.bReleased) {
      buttonY.bReleased = false;
      addToMenu("Hey!", nullptr);
      addToMenu("EXIT", exitGame);
    }

    script::execute();
    draw();
    drawFrame();
  }
  audio::stop();
  oled::setFont(font8x12);
  oled::setTextColor(WHITE);
}
}
