#include <SD.h>
#include <Pair.h>
#include <LinkedList.h>

//#define DRAW_COLLIDERS
#define TRIPPLE_BUFFER
#define SPI_SPEED 39999999

#include <MiniString.hpp>
#include <OreonBSSD1351.hpp>
#include <OreonSerializer.hpp>
#include <OreonBSSD1351Gui.hpp>
#include <OreonBSSD1351Tile.hpp>
#include <OreonBSSD1351Anim.hpp>

#include "01controller.hpp"
#include "02audio.hpp"
#include "03apps.hpp"

void setup() {
  Serial.begin(115200);
  SD.begin(4, SPI, SPI_SPEED);
  digitalWrite(4, HIGH);
  initController();
  oled::begin(5, 17, 16);
  audio::begin();
  delay(100);
  xTaskCreatePinnedToCore(outputTask, "Output Task", 10240, NULL, 5, NULL, 0);
  profilename = "p"; // inputText("Profile:");
  loadProfile();
  //  pokemon::run();
}

void loop() {
  updateController();
  if (bJoyMoved) {
    nAppPointer = wrap(nAppPointer + joyY, nApps);
  } else if (buttonX.bReleased) {
    appsFunctions[nAppPointer]();
  }

  oled::clear();
  gui::drawList("Apps", apps, nApps, nAppPointer);
  if (mario::fire) oled::drawImage(95, 111, 16, 16, mario::fireImage, MAGENTA);
  if (water) oled::drawImage(111, 111, 16, 16, waterImage, MAGENTA);
  if (cuby::earth) oled::drawImage(63, 111, 16, 16, cuby::earthImage, MAGENTA);
  if (geometry::wind) oled::drawImage(79, 111, 16, 16, geometry::windImage, MAGENTA);
  drawFrame();
}
