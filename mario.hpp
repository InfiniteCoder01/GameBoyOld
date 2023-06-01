#include "marioData.hpp"
#include "marioEntity.hpp"

namespace mario {
Object* createEntity(uint8_t type, int x, int y) {
  if (isMario(type)) {
    return new MarioEntity(type, x, y);
  } else if (isCollectible(type)) {
    return new CollectibleEntity(type, x, y);
  } else if (isProjectile(type)) {
    return new ProjectileEntity(type, x, y);
  } else if (isSystem(type)) {
    return new SystemEntity(type, x, y);
  }
  return new Enemy(type, x, y);
}

void saveGame(int index) {
  audio::pause();
  drawFrame();
  saveBytes(format("/profiles/%s/mario/data.txt", profilename), serialize("u1u1u1u1u1u1", mario->type, coins, levelIndex, hasFire, hasRacoon, hasPSwitch));
  saveBytes(format("/profiles/%s/mario/levels/%d.txt", profilename, index), saveLevel());
  audio::resume();
}

void restartGame() {
  audio::stop();
  drawFrame();
  prepareToBossFight = bossAlive = false;
  int nMarioType = 0;
  deserialize("u1u1u1u1u1u1", readBytes(format("/profiles/%s/mario/data.txt", profilename)), &nMarioType, &coins, &levelIndex, &hasFire, &hasRacoon, &hasPSwitch);
  if (nextLevel < 0) nextLevel = levelIndex - 1;
  if (SD.exists(format("/profiles/%s/mario/levels/%d.txt", profilename, levelIndex))) {
    loadSavedLevel(levelIndex, readBytes(format("/profiles/%s/mario/levels/%d.txt", profilename, levelIndex)));
  } else {
    loadLevel(levelIndex);
  }
  mario->type = nMarioType;
  mario->resetSprite();
  nextLevel = -1;
  if (engineData::levelBackground == 0) audio::play("/Music/SuperMarioBros/Underground.wav");
  else audio::play("/Music/SuperMarioBros/Overworld.wav");
}

/*                      MAIN FUNCTIONS                      */
void showStartMenu() {
  bool newGame = false;
  do {
    updateController();
    if (buttonY.bReleased) {
      newGame = true;
      break;
    }
    oled::drawBackground(startMenu);
    drawFrame();
  } while (!buttonX.bReleased);
  if (newGame || !SD.exists(format("/profiles/%s/mario/data.txt", profilename))) {
    saveBytes(format("/profiles/%s/mario/data.txt", profilename), serialize("u1u1u1u1u1u1", MARIO, 0, 0, 0, 0, 0));
    removeDir(format("/profiles/%s/mario/levels", profilename));
    SD.mkdir(format("/profiles/%s/mario/levels", profilename));
  }
}

void gameLoop() {
  while (true) {
    updateController();
    if (!mario->alive()) {
      restartGame();
    }
    if (nextLevel != -1) {
      swap(levelIndex, nextLevel);
      saveGame(nextLevel);
      restartGame();
    }
    drawMap();
    gui::rightText("WORLD", 0);
    gui::rightText(format(" %d-%d ", levelIndex / 10 + 1, levelIndex % 10 + 1), oled::getCharHeight());
    gui::drawFPS();
    oled::println(format("Coins: %d!", coins));
    drawFrame();
  }
}

void run() {
  setupEngine(16, data, createEntity);
  showStartMenu();
  restartGame();
  gameLoop();
}
}
