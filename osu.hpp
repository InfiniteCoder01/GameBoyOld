#include "osuData.hpp"

namespace osu {
using math3d::vec2i;
const int SONGS_X = 64, SONG_SHIFT = 20, SONG_W = 60, SONG_H = 20, SONG_SPACE = 2, MOD_SPACE = 2;
const int NODE_RADIUS = 10, CURSOR_RADIUS = 5;
const int RESTING_TIME = 400;
int nSelectedMod = 0;

struct Node {
  vec2i pos;
  int time;
  int index;
  bool clickable = false, passed = false;
  bool clicked = false;

  Node() {}
  Node(int x, int y, int index, int time) : pos(x, y), index(index), time(time) {}

  void draw(int t) {
    int nodeRadius = NODE_RADIUS;
    float alpha = 1;
    if (t < time - RESTING_TIME * 1.5f) {
      alpha = 1.f - float(time - RESTING_TIME * 1.5f - t) / (RESTING_TIME / 2);
      nodeRadius = alpha * NODE_RADIUS;
    } else if (t > time) {
      passed = true;
      alpha = 1.f - float(t - time) / RESTING_TIME;
      nodeRadius = (1.f - alpha) * NODE_RADIUS * 0.5 + NODE_RADIUS;
    }

    int nodeRadiusSquared = nodeRadius * nodeRadius;
    int circleRadius = nodeRadius;
    clickable = false;
    if (t < time && time - t < RESTING_TIME) {
      circleRadius = (time - t) / 24;
      if (circleRadius >= NODE_RADIUS) clickable = true;
      else circleRadius = nodeRadius;
    }

    for (int y1 = -circleRadius; y1 <= circleRadius; y1++) {
      for (int x1 = -circleRadius; x1 <= circleRadius; x1++) {
        vec2i pixel(x1, y1);
        int distanceSquared = pixel.sqrMagnitude();
        if (clickable && abs(distanceSquared - circleRadius * circleRadius) <= 32) {
          oled::setPixel(pos + pixel, WHITE);
        } else if (distanceSquared <= nodeRadiusSquared - 24) {
          oled::setPixelAlpha(pos + pixel, BLACK, 0.5 * alpha);
        } else if (distanceSquared <= nodeRadiusSquared - 4) {
          oled::setPixelAlpha(pos + pixel, WHITE, alpha);
        }
      }
    }
    if (inRange(time - t, 0, RESTING_TIME * 1.5f)) {
      oled::setCursor(pos.x - oled::getStringWidth(String(index)) / 2 + 1, pos.y - oled::getCharHeight() / 2 + 1);
      oled::print(String(index));
    }
  }
};

struct Cursor {
  vec2i pos, target, start;
  int tTargetStart = 0, tTargetTime = 0;

  Cursor() {}
  Cursor(int x, int y) : pos(x, y) {}

  void moveTo(vec2i to, int time) {
    if (to == target) return;
    target = to;
    start = pos;
    tTargetStart = millis();
    tTargetTime = max(time - tTargetStart, 1);
  }

  bool moving() {
    return pos != target && tTargetStart != 0;
  }

  void draw() {
    vec2i prevPos = pos;
    if (moving()) {
      pos = vec2i::lerp(start, target, min((millis() - tTargetStart) / (float)tTargetTime, 1.f));
    }
    oled::drawLine(prevPos.x, prevPos.y, pos.x, pos.y, CYAN, 2);
    int CURSOR_RADIUS_SQUARED = CURSOR_RADIUS * CURSOR_RADIUS;
    for (int y1 = -CURSOR_RADIUS; y1 <= CURSOR_RADIUS; y1++) {
      for (int x1 = -CURSOR_RADIUS; x1 <= CURSOR_RADIUS; x1++) {
        vec2i pixel(x1, y1);
        int distanceSquared = pixel.sqrMagnitude();
        if (distanceSquared <= CURSOR_RADIUS_SQUARED - 4) {
          oled::setPixelAlpha(pos + pixel, CYAN, 1.f - (float)distanceSquared / CURSOR_RADIUS_SQUARED);
        }
      }
    }
  }
};

struct Song {
  LinkedList<Node> nodes;
  const uint8_t* background;
  float score, accuracy;
  const char* file;
  bool failed;
  int time;

  Song() {}
  Song(const uint8_t* background, const int* beats, int nBeats, const char* file) : background(background), file(file) {
    nBeats /= sizeof(int) * 3;
    for (int i = 0; i < nBeats; i++) {
      nodes.add(Node(beats[i * 3 + 1], beats[i * 3 + 2], nodes.size() % 50 + 1, beats[i * 3]));
    }
  }

  void restart() {
    score = 0;
    accuracy = 1;
    failed = false;
    for (int i = 0; i < nodes.size(); i++) {
      nodes[i].passed = false;
    }
    audio::play(file);
    time = millis() + 700;
  }

  void stop() {
    audio::stop();
  }

  void onClick(vec2i pos, int time) {
    bool found = false;
    int maxScore = 0;
    for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i].passed) {
        maxScore++;
      }
      if (vec2i::sqrDistance(nodes[i].pos, pos) < NODE_RADIUS * NODE_RADIUS) {
        if (inRange(time - nodes[i].time, -RESTING_TIME * 2, RESTING_TIME)) {
          if (inRange(time - nodes[i].time, -RESTING_TIME, RESTING_TIME / 2) & !nodes[i].passed) {
            int timeDiff = abs(nodes[i].time - time);
            score += 1.f - (float)timeDiff / RESTING_TIME;
            nodes[i].clicked = nodes[i].passed = true;
          }
          found = true;
        }
      }
    }
    if (!found) {
      score = max(score - maxScore / 2.f, 0.f);
    }
  }

  void draw(int time, Cursor& cursor) {
    oled::drawBackground(background);
    int maxScore = 0;
    for (int i = 0; i < nodes.size(); i++) {
      if (nodes[i].passed) {
        if (time > nodes[i].time + RESTING_TIME && !nodes[i].clicked) {
          failed = true;
        }
        maxScore++;
      }
      if (inRange(time - nodes[i].time, -RESTING_TIME * 2, RESTING_TIME)) {
        nodes[i].draw(time);
        vec2i diff = nodes[i].pos - cursor.pos;
        float aspect = abs(diff.x) / (float)max(abs(diff.y), 1);
        bool move = false;
        if (nSelectedMod == MOD_AUTOPULOT || nSelectedMod == MOD_AUTO) {
          move = !nodes[i].passed && (i == 0 ? true : nodes[i - 1].passed) && !cursor.moving();
        } else {
          move = bJoyMoved && (sign(diff.x) * (aspect > 0.7) == joyX && sign(diff.y) * (aspect < 1.3) == joyY);
        }
        if (move) {
          cursor.moveTo(nodes[i].pos, nodes[i].time - time + millis() - RESTING_TIME * 1.5);
        }
        if (nSelectedMod == MOD_AUTO && nodes[i].time - time < 100 && !nodes[i].passed) {
          onClick(cursor.pos, time);
        }
      }
    }
    accuracy = maxScore == 0 ? 1 : score / maxScore;
    if (accuracy == 0) {
      failed = true;
    }
  }
};

struct SongDisplay {
  String name;
  const uint8_t* background;
  const char* file;
  const int* beats;
  int nBeats;
  float x;

  SongDisplay() {}
  SongDisplay(String name, const uint8_t* background, const int* beats, int nBeats, const char* file) : name(name), background(background),
    file(file), beats(beats), nBeats(nBeats), x(SONGS_X) {}

  Song* createSong() {
    return new Song(background, beats, nBeats, file);
  }
};

Cursor cursor;

SongDisplay songs[] {
  SongDisplay("Pirate", heIsAPirateBG, heIsAPirateBeats, sizeof(heIsAPirateBeats), "/Music/Songs/HeIsAPirate.wav"),
  SongDisplay("Changes", changesBG, changesBeats, sizeof(changesBeats), "/Music/Songs/Changes.wav"),
  SongDisplay("Unity", unityBG, unityBeats, sizeof(unityBeats), "/Music/Songs/Unity.wav"),
  SongDisplay("Rush E", rushEBG, rushEBeats, sizeof(rushEBeats), "/Music/Songs/RushE.wav"),
  SongDisplay("Meet", wellMeetAgainBG, wellMeetAgainBeats, sizeof(wellMeetAgainBeats), "/Music/Songs/WellMeetAgain.wav"),
};

void play(Song& song) {
  while (true) {
    song.restart();
    cursor = Cursor(oled::width / 2, oled::height / 2);
    while (!song.failed) {
      updateController();
      float dt = deltaTime();
      int time = millis() - song.time;

      if (buttonX.bPressed) {
        song.onClick(cursor.pos, time);
      }

      if (buttonY.bReleased) {
        song.stop();
        return;
      }

      song.draw(time, cursor);
      cursor.draw();
      gui::drawFPS();
      oled::println(format("%0.2f%%", song.accuracy * 100.f));
      drawFrame();
    }
    song.stop();
  }
}

void run() {
  for (auto& song : songs) {
    song.x = SONGS_X;
  }
  int nSelectedSong = 0;
  int nSongs = sizeof(songs) / sizeof(songs[0]);
  int songsH = nSongs * SONG_H + (nSongs - 1) * SONG_SPACE;
  while (true) {
    updateController();
    float dt = deltaTime();

    if (bJoyMoved) {
      nSelectedSong = wrap(nSelectedSong + joyY, nSongs);
    }

    if (buttonY.bReleased) {
      int nMods = sizeof(mods) / sizeof(mods[0]);
      while (true) {
        updateController();
        if (bJoyMoved) {
          nSelectedMod = wrap(nSelectedMod + joyX, nMods);
        }
        if (buttonX.bReleased) {
          buttonX.bReleased = false;
          break;
        }
        if (buttonY.bReleased) {
          return;
        }
        oled::drawBackground(songs[nSelectedSong].background);
        gui::centerText(modDescriptions[nSelectedMod], 0);
        int x = (oled::width - 34 * nMods - MOD_SPACE * (nMods - 1)) / 2;
        for (int i = 0; i < nMods; i++) {
          if (i == nSelectedMod) oled::drawRect(x, oled::height / 2 - 17, 34, 34, WHITE);
          oled::drawImage(x + 1, oled::height / 2 - 16, 32, 32, mods[i], MAGENTA);
          x += 34 + MOD_SPACE;
        }
        drawFrame();
      }
    }

    if (buttonX.bReleased) {
      Song* song = songs[nSelectedSong].createSong();
      play(*song);
      delete song;
    }

    oled::drawBackground(songs[nSelectedSong].background);

    int y = (oled::height - songsH) / 2;
    for (int i = 0; i < nSongs; i++) {
      float dst = 1.f - abs(nSelectedSong - i) / (float)max(nSelectedSong, nSongs - nSelectedSong);
      songs[i].x += (SONGS_X - SONG_SHIFT * dst - songs[i].x) * dt;
      oled::fillRect(songs[i].x, y, SONG_W + SONGS_X - songs[i].x, SONG_H, oled::interpolateColor(RED, BLUE, i / (float)nSongs));
      oled::setCursor(songs[i].x + 3, y + (SONG_H - oled::getCharHeight()) / 2);
      oled::print(songs[i].name);
      y += SONG_H + SONG_SPACE;
    }

    drawFrame();
  }
}
}
