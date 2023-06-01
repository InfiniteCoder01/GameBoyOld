#include "04utils.hpp"
#include "05elements.hpp"
#include "cuby.hpp"
#include "mario.hpp"
#include "asteroids.hpp"
#include "osu.hpp"

void notAvailableYet() {
  oled::clear();
  oled::setTextColor(WHITE);
  oled::setFont(font8x12);
  gui::centerText("Not coded yet!");
  drawFrame();
  delay(3000);
}

void displayInfo() {
  oled::clear();
  oled::setCursor(0, 0);
  oled::setFont(fontPico8);
  oled::print("          GameBoy v3.2          "
              "Hold \x7f\x80 to run!                 "
              "Press \x7f\x80 to fire!               "
              "Press \x81\x82 to switch/exit!        "
              "Press \x7f\x80 to jump in GD!         "
              "Press \x7f\x80 to perform an action!  "
              "Press \x7f\x80 to attack!             "
              "Tetris:                         "
              "Press down to hard drop!        "
              "Press \x81\x82 to soft drop!          "
              "Press \x7f\x80 to rotate!             "
              "Press \x81\x82 to enter zone!         "
              "Clear 3+ lines to enter Tetris  "
              "Effect mode!                    "
              "                                "
              "                                "
              "                                "
              "                                "
              "                                "
              "Press \x7f\x80 to reset everything!   "
              "Press \x81\x82 to quit!               ");
  drawFrame();
  do {
    updateController();
    if (buttonX.bReleased && SD.exists(format("/profiles/%s/elements.txt", profilename.c_str()))) {
      SD.remove(format("/profiles/%s/elements.txt", profilename));
      mario::fire = water = cuby::earth = geometry::wind = false;
      loadProfile();
      break;
    }
  } while (!buttonY.bReleased);
  oled::setTextColor(WHITE);
  oled::setFont(font8x12);
}

String apps[] = {"Super Mario", "Asteroids", "Cuby", "Tetris", "OSU!", "Info"};

Function appsFunctions[] = {
  mario::run,
  asteroids::run,
  cuby::run,
  tetris::run,
  osu::run,
  displayInfo,
};

const uint8_t nApps = sizeof(apps) / sizeof(apps[0]);
uint8_t nAppPointer = 0;
