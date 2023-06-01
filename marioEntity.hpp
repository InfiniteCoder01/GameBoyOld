namespace mario {
struct MarioEntity;
MarioEntity* mario;

inline bool isSystem(int type) {
  return type < MARIOS_INDEX;
}
inline bool isMario(int type) {
  return inRange(type, MARIOS_INDEX, ENEMIES_INDEX - 1);
}
inline bool isEnemy(int type) {
  return inRange(type, ENEMIES_INDEX, COLLECTIBLES_INDEX - 1);
}
inline bool isCollectible(int type) {
  return inRange(type, COLLECTIBLES_INDEX, PROJECTILES_INDEX - 1);
}
inline bool isProjectile(int type) {
  return type >= PROJECTILES_INDEX;
}
inline bool isBoss(int type) {
  return type == FAKE_BOWSER || type == BOOM_BOOM;
}

void typeText(String text, int x, int y) {
  uint32_t tTextStart = millis();
  while ((millis() - tTextStart) / 150 < text.length()) {
    updateController();
    if (buttonX.bReleased) {
      buttonX.bReleased = false;
      tTextStart = 0;
    }
    oled::setCursor(x, y);
    oled::print(text.substring(0, min((unsigned int)(millis() - tTextStart) / 150, text.length())));
    drawFrame();
  }
}

float getMarioX();
float getMarioY();
void saveGame(int index);

/*                      BASES                       */
struct PhysicalEntity : public Object {
  float jumpForce = JUMP_FORCE;
  bool onGround = true;
  float ySpeed = 0;

  PhysicalEntity() : Object() {}
  PhysicalEntity(uint8_t type, int x, int y, float jumpForce = JUMP_FORCE) : Object(type, x, y), jumpForce(jumpForce) {}

  virtual void go(float dx, bool jump, float fElapsedTime) {
    y++;
    onGround = collides(0, 0) || getTile(x / tileSize, y / tileSize) == Tiles::WATER_BASE || getTile(x / tileSize, y / tileSize) == Tiles::WATER_TOP;
    y--;

    if (jump && onGround) {
      ySpeed = jumpForce;
      ySpeed *= getTile(x / tileSize, y / tileSize) == Tiles::WATER_BASE ? 0.3 : 1;
    } else {
      float multiplier = fElapsedTime * (getTile(x / tileSize, y / tileSize) == Tiles::WATER_BASE ? 0.5 : 1);
      if (type == RACOON_MARIO && buttonX.bHeld) {
        ySpeed += GRAVITY_FORCE * (ySpeed < 0 ? 0.5 : 0.25) * multiplier;
      } else {
        ySpeed += GRAVITY_FORCE * multiplier * (type == BOOM_BOOM ? 0.3 : 1);
      }
    }
    move(dx * ENTITY_DATA[type][0] * fElapsedTime, ySpeed * (type == FLAME ? 2 : 1) * fElapsedTime);
  }
};

struct AnimatedPhysicalEntity : public PhysicalEntity {
  int direction = 0;
  uint16_t rnd = 0;

  AnimatedPhysicalEntity() : PhysicalEntity() {}
  AnimatedPhysicalEntity(uint8_t type, int x, int y, float jumpForce = JUMP_FORCE) : PhysicalEntity(type, x, y, jumpForce) {
    rnd = random(0xffff);
  }

  void go(float dx, bool jump, float fElapsedTime) {
    PhysicalEntity::go(dx, jump, fElapsedTime);
    direction = dx > 0 ? 1 : dx < 0 ? -1 : direction;
    if (ySpeed != 0 && type == RACOON_MARIO && buttonX.bHeld) {
      sprite = ENTITY_DATA[type][1] + (millis() + rnd) / 150 % 2 + 1;
      return;
    }
    if (ySpeed < 0 && isMario(type)) {
      sprite = ENTITY_DATA[type][1] + 1;
    } else if (dx != 0) {
      sprite = int(millis() * abs(dx) / 150) % ENTITY_DATA[type][1];
    } else {
      sprite = ENTITY_DATA[type][1];
    }
  }

  void draw() {
    oled::flip = direction < 0;
    Object::draw();
    oled::flip = false;
  }
};

/*                      COLLECTIBLE                       */
struct CollectibleEntity : public PhysicalEntity {
  int8_t AIDirection = 1;

  CollectibleEntity() : PhysicalEntity() {}
  CollectibleEntity(uint8_t type, int x, int y) : PhysicalEntity(type, x, y, JUMP_FORCE * 0.25) {}

  void fromSave(LinkedList<uint8_t>* save) {
    deserialize("i1E", save, &AIDirection);
  }

  void toSave(LinkedList<uint8_t>* save) {
    addAll(save, serialize("i1", AIDirection));
  }

  void loadAfter() {
    sprite = 0;
    if (type == COIN) {
      ySpeed = JUMP_FORCE * 3 / 4;
    }
    if (getTile(x / tileSize, y / tileSize) == Tiles::QUESTION) {
      sprite = -1;
    }
    AIDirection = 1;
  }

  void update(float fElapsedTime) {
    if (y > levelHeight * tileSize) {
      bDead = true;
      return;
    }
    if (sprite == -1) {
      if (getTile(x / tileSize, y / tileSize) != Tiles::QUESTION) {
        sprite = 0;
        y -= tileSize;
        if (type == MUSHROOM && ((Object*)mario)->type > MARIO) type = FIRE_FLOWER;
        if (type == FIRE_FLOWER && ((Object*)mario)->type > SUPER_MARIO && hasFire) type = LEAF;
        resetSprite();
      } else {
        return;
      }
    }
    if (type == MUSHROOM) {
      go(AIDirection, false, fElapsedTime);
      sprite = millis() / 150 % ENTITY_DATA[type][1];
    } else if (type == COIN || type == FIRE_FLOWER) {
      go(0, false, fElapsedTime);
      sprite = millis() / 150 % ENTITY_DATA[type][1];
    } else if (type == LEAF) {
      y -= ENTITY_DATA[type][0] * fElapsedTime;
      sprite = 0;
      if (y < 0) {
        bDead = true;
      }
    }
  }

  bool collides(float dx, float dy) {
    bool result = PhysicalEntity::collides(dx, dy);
    if (result) {
      if (dy != 0 && onGround != 127) {
        ySpeed = 0;
      } else if (dx != 0) {
        AIDirection = -AIDirection;
      }
    }
    return result;
  }

  bool collide(float x, float y, int tile, float dx, float dy) {
    bool result = this->x < 0 || this->x + this->w > levelWidth * tileSize;
    char shape = shapes[tile];
    if (!result) {
      if (shape == ' ') {
        result = false;
      } else if (shape == '#') {
        result = true;
      } else if (shape == '=') {
        result = true;
      } else if (shape == 'c') {
        switch (tile) {
          case Tiles::QUESTION:
            result = true;
            break;
          case Tiles::DOOR1:
          case Tiles::DOOR2:
            result = bossAlive;
            break;
          case Tiles::LAVA_BASE:
            bDead = true;
            result = true;
            break;
        }
      }
    }
    return result;
  }

  void draw() {
    oled::flip = AIDirection < 0;
    Object::draw();
    oled::flip = false;
  }
};

/*                      PROJECTILE                       */
struct ProjectileEntity : public PhysicalEntity {
  int8_t AIDirection = 0;

  ProjectileEntity() : PhysicalEntity() {}
  ProjectileEntity(uint8_t type, int x, int y) : PhysicalEntity(type, x, y, JUMP_FORCE * 0.3) {}

  void fromSave(LinkedList<uint8_t>* save) {
    deserialize("i1E", save, &AIDirection);
  }

  void toSave(LinkedList<uint8_t>* save) {
    addAll(save, serialize("i1", AIDirection));
  }

  void loadAfter() {
    sprite = 0;
    if (type == HAMMER) {
      ySpeed = JUMP_FORCE;
    }
  }

  void update(float fElapsedTime) {
    if (y > levelHeight * tileSize) {
      bDead = true;
      return;
    }
    if (type == FLAME) {
      sprite = millis() / 150 % ENTITY_DATA[type][1];
      go(AIDirection, true, fElapsedTime);
      x -= AIDirection;
      if (collides(AIDirection, 0) || !inRange(x - cameraX, -w, oled::width) || !inRange(y - cameraY, -h, oled::height)) {
        bDead = true;
      }
      x += AIDirection;
    } else if (type == FIRE) {
      sprite = millis() / 150 % ENTITY_DATA[type][1];
      x += AIDirection * ENTITY_DATA[type][0] * fElapsedTime;
      if (collides(AIDirection, 0)) {
        bDead = true;
      }
    } else if (type == HAMMER || type == FIREBALL) {
      go(AIDirection, false, fElapsedTime);
      sprite = millis() / 150 % ENTITY_DATA[type][1];
      if (onGround) {
        bDead = true;
      }
    }
  }

  bool collides(float dx, float dy) {
    bool result = PhysicalEntity::collides(dx, dy);
    if (result) {
      if (dy != 0 && onGround != 127) {
        ySpeed = 0;
      } else if (dx != 0) {
        AIDirection = -AIDirection;
      }
    }
    return result;
  }

  bool collide(float x, float y, int tile, float dx, float dy) {
    bool result = this->x < 0 || this->x + this->w > levelWidth * tileSize;
    char shape = shapes[tile];
    if (!result) {
      if (shape == ' ') {
        result = false;
      } else if (shape == '#') {
        result = true;
      } else if (shape == '=') {
        result = true;
      } else if (shape == 'c') {
        switch (tile) {
          case Tiles::QUESTION:
            result = true;
            break;
          case Tiles::DOOR1:
          case Tiles::DOOR2:
            result = bossAlive;
            break;
          case Tiles::LAVA_BASE:
            bDead = true;
            result = true;
            break;
        }
      }
    }
    return result;
  }

  void draw() {
    oled::flip = AIDirection < 0;
    Object::draw();
    oled::flip = false;
  }
};

/*                      ENEMY                       */
struct Enemy : public AnimatedPhysicalEntity {
  uint32_t deadTimer = 0, unkillableTimer = 0, fireTimer = 0;
  int8_t AIDirection = 0;
  uint8_t health = 1;
  bool sleep = false;
  uint16_t rnd = 0;

  Enemy() : AnimatedPhysicalEntity() {}
  Enemy(uint8_t type, int x, int y) : AnimatedPhysicalEntity(type, x, y, JUMP_FORCE * (type == LAVA_BUBBLE ? 1.5 : type == KOOPA_PARATROOPA ? 0.8 : 0.25)) {}

  void loadSettings(const uint8_t*& settings) {
    if (type == PIRANHA) {
      x += tileSize / 2;
    }
  }

  void fromSave(LinkedList<uint8_t>* save) {
    deserialize("u1u1i1E", save, &sleep, &health, &AIDirection);
  }

  void toSave(LinkedList<uint8_t>* save) {
    addAll(save, serialize("u1u1i1E", sleep, health, AIDirection));
  }

  void loadAfter() {
    sprite = 0;
    if (getTile(x / tileSize, y / tileSize) == Tiles::QUESTION) {
      sprite = -1;
    }
    sleep = true;
    health = ENTITY_DATA[type][2];
    direction = AIDirection = -1;
    rnd = random(0xffff);
  }

  void update(float fElapsedTime) {
    if (sleep) {
      if (!isBoss(type)) {
        if (inRange(x - cameraX, -w, oled::width) && inRange(y - cameraY, -h, oled::height)) {
          sleep = false;
        } else {
          return;
        }
      }  else {
        if (abs((x + w / 2) - (cameraX + oled::width / 2)) < BOSS_ZONE) {
          prepareToBossFight = true;
          cameraX += sign((x + w / 2) - (cameraX + oled::width / 2)) * fElapsedTime * 50;
          if (abs((x + w / 2) - (cameraX + oled::width / 2)) < BOSS_STOP_ZONE) {
            prepareToBossFight = sleep = false;
            bossAlive = true;
          } else {
            return;
          }
        } else {
          return;
        }
      }
    }
    if (y > levelHeight * tileSize) {
      instantKill();
    }
    if (!alive()) {
      if (millis() > deadTimer) bDead = true;
      return;
    }
    if (sprite == -1) {
      if (getTile(x / tileSize, y / tileSize) != Tiles::QUESTION) {
        sprite = 0;
        y -= tileSize;
      } else {
        return;
      }
    }
    if (type == GOOMBA || type == KOOPA_TROOPA || type == KOOPA_PARATROOPA) go(AIDirection, type == KOOPA_PARATROOPA, fElapsedTime);
    else if (type == PIRANHA) {
      const uint16_t TIME_MOVE = 500, TIME_STAY = 600, TIME_HIDE = 2000;
      uint16_t time = (millis() + rnd) % (TIME_MOVE * 2 + TIME_STAY + TIME_HIDE);
      uint8_t oldH = h;
      h = max(0, min(-abs((time - TIME_MOVE - TIME_STAY / 2) * 32 / TIME_MOVE) + 50, 32));
      y += oldH - h;
      sprite = time > TIME_MOVE + TIME_STAY / 2;
    } else if (type == LAVA_BUBBLE) {
      go(0, true, fElapsedTime);
      sprite = ySpeed > 0;
    } else if (type == LAKITU) {
      AIDirection = sign(align(getMarioX() - x, ENTITY_DATA[type][0] * fElapsedTime));
      direction = AIDirection;
      x += AIDirection * ENTITY_DATA[type][0] * fElapsedTime;
      sprite = 0;
      if (millis() - fireTimer > FIRE_TIME * 5) {
        fireTimer = millis();
        spawn<ProjectileEntity>(x, y + h / 2, FIREBALL)->AIDirection = direction;
      }
      if (millis() - fireTimer > FIRE_TIME * 5 - 500) {
        sprite = 1;
      }
    } else if (type == HAMMER_BRO) {
      AIDirection = sign(getMarioX() - x);
      go(AIDirection, false, fElapsedTime);
      if (millis() - fireTimer > FIRE_TIME) {
        fireTimer = millis();
        spawn<ProjectileEntity>(x + w / 2, y + h / 2, HAMMER)->AIDirection = direction;
        sprite = ENTITY_DATA[type][1] - 1;
      } else if (millis() - fireTimer < 100) {
        sprite = ENTITY_DATA[type][1];
      }
    } else if (type == FAKE_BOWSER) {
      AIDirection = sign(getMarioX() - x);
      go(AIDirection, true, fElapsedTime);
      if (millis() - fireTimer > FIRE_TIME * 5) {
        fireTimer = millis();
        if (random(1)) {
          spawn<ProjectileEntity>(x + w / 2, y + h / 2, FIRE)->AIDirection = direction;
        } else {
          spawn<ProjectileEntity>(x, y + h / 2, HAMMER)->AIDirection = direction;
        }
      }
    } else if (type == BOOM_BOOM) {
      AIDirection = sign(getMarioX() - x);
      direction = AIDirection;
      if (millis() - fireTimer > FIRE_TIME * 15) {
        if (millis() - fireTimer - FIRE_TIME * 15 < fElapsedTime * 2) {
          ySpeed = 0;
        }
        if (ySpeed == 0) {
          if (abs(x - getMarioX()) < 5) {
            go(0, false, fElapsedTime);
          } else {
            float dx, dy;
            dx = getMarioX() - x;
            dy = getMarioY() - 100 - y;
            float len = sqrt(dx * dx + dy * dy);
            dx /= max(len, 1.0f);
            dy /= max(len, 1.0f);
            x += dx * ENTITY_DATA[type][0] * fElapsedTime;
            y += dy * ENTITY_DATA[type][0] * fElapsedTime;
          }
        } else {
          go(0, false, fElapsedTime);
          if (ySpeed == 0) {
            fireTimer = millis();
            for (int x1 = x / tileSize; x1 <= x / tileSize + 2; x1++) {
              if (getTile(x1, (y + h + tileSize / 2) / tileSize) == Tiles::BRICK) {
                setTile(x1, (y + h + tileSize / 2) / tileSize, 0);
              }
            }
          }
        }
        sprite = (millis() + rnd) / 150 % ENTITY_DATA[type][2];
      } else {
        sprite = nSprites - 2;
        go(0, false, fElapsedTime);
      }
    } else if (type == KOOPA_SHELL) {
      go(AIDirection, false, fElapsedTime);
      sprite = AIDirection == 0 ? 0 : (millis() + rnd) / 150 % ENTITY_DATA[type][1];
    }
  }

  void touchObject(Object* other) {
    if (!alive()) return;
    if (type == PIRANHA && h < 3) return;
    if (other->type == FLAME) {
      other->bDead = true;
      kill();
    }
  }

  bool collides(float dx, float dy) {
    bool result = PhysicalEntity::collides(dx, dy);
    if (result) {
      if (dy != 0 && onGround != 127) {
        ySpeed = 0;
      } else if (dx != 0) {
        AIDirection = -AIDirection;
      }
    }
    return result;
  }

  bool collide(float x, float y, int tile, float dx, float dy) {
    bool result = this->x < 0 || this->x + this->w > levelWidth * tileSize;
    char shape = shapes[tile];
    if (!result) {
      if (shape == ' ') {
        result = false;
      } else if (shape == '#') {
        result = true;
      } else if (shape == '=') {
        result = true;
      } else if (shape == 'c') {
        switch (tile) {
          case Tiles::QUESTION:
            result = true;
            break;
          case Tiles::DOOR1:
          case Tiles::DOOR2:
            result = bossAlive;
            break;
          case Tiles::LAVA_BASE:
            if (type != LAVA_BUBBLE) {
              instantKill();
            }
            result = true;
            break;
        }
      }
    }
    return result;
  }

  void becameUnkillable(uint16_t time) {
    unkillableTimer = millis() + time;
  }

  void transform(uint8_t newType) {
    if (type != newType) {
      type = newType;
      resetSprite();
    }
  }

  void instantKill() {
    bDead = true;
  }

  void kill() {
    if (sleep) return;
    if (unkillable()) return;
    if (health > 0) health--;
    if (health > 0) return;
    if (type == KOOPA_PARATROOPA) {
      becameUnkillable(100);
      transform(KOOPA_TROOPA);
      return;
    } else if (type == KOOPA_TROOPA) {
      becameUnkillable(100);
      transform(KOOPA_SHELL);
      AIDirection = 0;
      return;
    } else if (type == FAKE_BOWSER) {
      deadTimer = millis() + ENTITY_SQUASHED_TIME;
      bossAlive = false;
      for (int i = 0; i < 10; i++) spawn<CollectibleEntity>(x, y, COIN);
      return;
    } else if (type == BOOM_BOOM) {
      if (y > levelHeight * tileSize) {
        bossAlive = false;
        bDead = true;
        coins += 10;
      }
      return;
    }
    bDead = true;
    spawn<CollectibleEntity>(x, y, COIN);
  }

  void squash() {
    if (type == KOOPA_PARATROOPA || type == KOOPA_TROOPA || type == FAKE_BOWSER || type == BOOM_BOOM) {
      kill();
      return;
    }
    if (sleep) return;
    if (unkillable()) return;

    deadTimer = millis() + ENTITY_SQUASHED_TIME;
    sprite = ENTITY_DATA[type][1];
    spawn<CollectibleEntity>(x, y, COIN);
  }

  bool alive() {
    return deadTimer == 0;
  }

  bool unkillable() {
    return millis() < unkillableTimer;
  }

  void draw() {
    oled::flip = direction < 0;
    Object::draw();
    oled::flip = false;
  }
};

/*                      MARIO                       */
struct MarioEntity : public AnimatedPhysicalEntity {
  bool teleporting = false, touchKill = false, dead = false;
  uint32_t unkillableTimer = 0, fireTimer = 0;

  MarioEntity() : AnimatedPhysicalEntity() {}
  MarioEntity(uint8_t type, int x, int y) : AnimatedPhysicalEntity(type, x, y, JUMP_FORCE) {}

  void loadSettings(const uint8_t*& settings) {
    mario = this;
  }

  void fromSave(LinkedList<uint8_t>* save) {
    mario = this;
  }

  void loadAfter() {
    sprite = 0;
    direction = 1;
  }

  void update(float fElapsedTime) {
    if (y > levelHeight * tileSize) {
      instantKill();
    }
    if (!alive()) return;
    if (prepareToBossFight) return;
    if (teleporting) {
      h = max(0.f, h - fElapsedTime * 20);
      go(0, false, fElapsedTime);
      teleporting = false;
    } else if (h < getRealHeight()) {
      h = min((float)getRealHeight(), h + fElapsedTime * 20);
      go(0, false, fElapsedTime);
    } else {
      go(joyX * (buttonX.bHeld ? SPRINT_FORCE : 1), joyY < 0, fElapsedTime);
    }
    if (buttonY.bReleased) {
      transformToNext();
    }
    if (type == RACOON_MARIO) {
      if (buttonX.bReleased && millis() - fireTimer > FIRE_TIME * 2 || millis() - fireTimer < 400) {
        if (millis() - fireTimer > FIRE_TIME * 2) {
          fireTimer = millis();
          touchKill = true;
        }
        sprite = nSprites - 4 + (millis() - fireTimer) / 100 % 4;
      } else {
        touchKill = false;
      }
    } else if (type == FIRE_MARIO) {
      if (buttonX.bReleased) {
        fireTimer = millis();
        spawn<ProjectileEntity>(x, y + h / 2, FLAME)->AIDirection = direction;
      }
    }
    camera(x + w / 2, y + h / 2);
    if (joyY > 0 && getTile(x / tileSize + 0.5, (y + h) / tileSize + 0.5) == Tiles::GOLD && hasPSwitch) { // P-Switch
      spawn<Object>(align(x + 2, tileSize), align(y + h - tileSize + 2, tileSize), P_SWITCH);
      hasPSwitch = false;
      y -= tileSize * 1.5;
      ySpeed = JUMP_FORCE;
    }
  }

  void touchObject(Object* other) {
    if (other->sprite < 0 || !alive()) return;
    if (other->type == PIRANHA && other->h < 3) return;
    if (isEnemy(other->type)) {
      Enemy* enemy = (Enemy*)other;
      if (!enemy->alive()) return;
      if (touchKill) {
        enemy->kill(); // flip
        return;
      }
      if (enemy->type == LAVA_BUBBLE || enemy->type == PIRANHA) {
        kill();
      } else if (enemy->type == KOOPA_SHELL) {
        if (enemy->AIDirection == 0) {
          enemy->AIDirection = sign(other->x - x);
          enemy->becameUnkillable(100);
        } else {
          kill();
        }
      } else if (ySpeed > 0) {
        ySpeed = JUMP_FORCE * 2 / 5;
        enemy->squash();
      } else {
        kill();
      }
    } else if (isProjectile(other->type) && other->type != FLAME) {
      if (!touchKill) {
        kill();
      }
      other->bDead = true;
    } else if (isCollectible(other->type)) {
      if (other->type == COIN) coins++;
      else if (other->type == MUSHROOM) transform(SUPER_MARIO);
      else if (other->type == FIRE_FLOWER) {
        transform(FIRE_MARIO);
        hasFire = true;
      } else if (other->type == LEAF) {
        transform(RACOON_MARIO);
        hasRacoon = true;
      }
      other->bDead = true;
    }
  }

  bool collides(float dx, float dy) {
    bool result = PhysicalEntity::collides(dx, dy);
    if (result) {
      if (dy != 0 && onGround != 127) {
        ySpeed = 0;
      }
    }
    return result;
  }

  bool collide(float x, float y, int tile, float dx, float dy) {
    bool result = this->x < 0 || this->x + this->w > levelWidth * tileSize;
    char shape = shapes[tile];
    if (!result) {
      if (shape == ' ') {
        result = false;
      } else if (shape == '#') {
        result = true;
      } else if (shape == '=') {
        result = (dy > 0 || dx == 0 && dy == 0) && joyY <= 0;
      } else if (shape == 'c') {
        switch (tile) {
          case Tiles::QUESTION:
            if (dy < 0) {
              setTile(x, y, 0);
              this->y += tileSize * 1.5;
              if (getObject(x, y) == nullptr) spawn<CollectibleEntity>(x * tileSize, y * tileSize - tileSize, COIN);
              this->y -= tileSize * 1.5;
            }
            result = true;
            break;
          case Tiles::DOOR1:
          case Tiles::DOOR2:
            result = bossAlive;
            break;
          case Tiles::LAVA_BASE:
            if (type != LAVA_BUBBLE) {
              instantKill();
            }
            result = true;
            break;
        }
      }
    }
    return result;
  }

  void becameUnkillable(uint16_t time) {
    unkillableTimer = millis() + time;
  }

  void transform(uint8_t newType) {
    if (type != newType) {
      type = newType;
      sprite = 0;
      resetSprite();
    }
  }

  //  void transformToAvailable() {
  //    if (hasFire) {
  //      transform(FIRE_MARIO);
  //    } else if (hasRacoon) {
  //      transform(RACOON_MARIO);
  //    } else {
  //      transform(SUPER_MARIO);
  //    }
  //    becameUnkillable(1000);
  //  }

  bool isAvailable() {
    if (type == FIRE_MARIO) {
      return hasFire;
    } else if (type == RACOON_MARIO) {
      return hasRacoon;
    }
    return false;
  }

  void transformToNext() {
    if (type <= SUPER_MARIO) return;
    do {
      transform(type + 1);
      if (!isMario(type)) {
        transform(SUPER_MARIO + 1);
      }
    } while (!isAvailable());
  }

  void instantKill() {
    dead = true;
  }

  void kill() {
    if (unkillable()) return;
    //    if (type > SUPER_MARIO) {
    //      if (type == RACOON_MARIO) {
    //        hasRacoon = false;
    //        transformToAvailable();
    //      } else if (type == FIRE_MARIO) {
    //        hasFire = false;
    //        transformToAvailable();
    //      }
    //      return;
    //    } else if (type > MARIO) {
    //      transform(type - 1);
    //      return;
    //    }
    dead = true;
  }

  bool alive() {
    return !dead;
  }

  bool unkillable() {
    return millis() < unkillableTimer;
  }
};

/*                      SYSTEM                       */
struct SystemEntity : public Object {
  int16_t targetX = 0, targetY = 0;
  float time = 0;

  SystemEntity() : Object() {}
  SystemEntity(uint8_t type, int x, int y) : Object(type, x, y) {}

  void loadSettings(const uint8_t*& settings) {
    if (type == LEVEL_CHANGER) {
      targetX = readByteSetting(settings);
    } else if (type == TELEPORT) {
      targetX = readIntSetting(settings);
      targetY = readIntSetting(settings);
      x += tileSize * 0.5;
      y -= tileSize * 0.5;
    } else if (type == INSTANT_TELEPORT) {
      targetX = readIntSetting(settings);
      targetY = readIntSetting(settings);
    } else if (type == LETTER) {
      targetX = readByteSetting(settings);
    }
  }

  void fromSave(LinkedList<uint8_t>* save) {
    deserialize("i2i2E", save, &targetX, &targetY);
  }

  void toSave(LinkedList<uint8_t>* save) {
    addAll(save, serialize("i2i2", targetX, targetY));
  }

  void loadAfter() {
    if (type == LEVEL_CHANGER) {
      if (targetX == nextLevel) {
        if (x < levelWidth * tileSize / 2) {
          mario->x = x + tileSize * 1.5;
          mario->y = y - tileSize * 1.5;
        } else {
          mario->x = x - tileSize * 1.5;
          mario->y = y - tileSize * 1.5;
        }
      }
    } else if (type == P_SWITCH || type == LETTER || type == SHOP || type == EXPLOSION) {
      sprite = 0;
    }
  }

  void update(float fElapsedTime) {
    if (type == P_SWITCH) {
      if (sprite == nSprites - 1) {
        time += fElapsedTime;
        if (time > 0.5) {
          int tileX = x / tileSize, tileY = y / tileSize + 1;
          while (getTile(tileX, tileY) != Tiles::CAVE_GROUND && getTile(tileX, tileY + 1) != Tiles::CAVE_STONE) {
            tileX++;
            if (getTile(tileX, tileY) == Tiles::WOOD) {
              bDead = true;
              return;
            }
          }
          setTile(tileX, tileY, Tiles::BRICK);
          setTile(tileX, tileY + 1, Tiles::BRICK);
          spawn<SystemEntity>(tileX * tileSize, tileY * tileSize, EXPLOSION);
          spawn<SystemEntity>(tileX * tileSize, (tileY + 1) * tileSize, EXPLOSION);
          time -= 0.5;
        }
      }
    } else if (type == EXPLOSION) {
      time += fElapsedTime;
      if (time > 0.1) {
        sprite++;
        if (sprite >= nSprites) {
          sprite = -1;
          bDead = true;
        }
        time -= 0.1;
      }
    }
  }

  void touchObject(Object* other) {
    if (!isMario(other->type)) return;
    if (type == LEVEL_CHANGER) {
      nextLevel = targetX;
    } else if (type == TELEPORT) {
      if (joyY > 0) {
        int x1 = x / tileSize, y1 = y / tileSize;
        mario->teleporting = true;
        if (mario->h < 0.1f) {
          mario->x += (targetX - x1) * tileSize;
          mario->y += (targetY - y1) * tileSize;
          mario->teleporting = false;
        }
      }
    } else if (type == INSTANT_TELEPORT) {
      int x1 = x / tileSize, y1 = y / tileSize;
      mario->x += (targetX - x1) * tileSize;
      mario->y += (targetY - y1) * tileSize;
    } else if (type == SHOP && buttonX.bPressed) {
      oled::fillScreen(WHITE);
      oled::setTextColor(BLACK);
      typeText("Hello! You've   "
               "been on a long  "
               "journey! But you"
               "need one thing  "
               "before you meet "
               "you last enemy. "
               "I will give it  "
               "to you for 100$ "
               "Press X to Pay  "
               "Press Y to Quit ", 0, 0);
      updateController();
      while (!buttonY.bReleased) {
        updateController();
        if (buttonX.bReleased && coins > 100) {
          coins -= 100;
          hasPSwitch = true;
          oled::fillScreen(WHITE);
          typeText(" You have got a "
                   "    P-Switch    "
                   "Press down when "
                   "standing on gold"
                   "  to place it!  ", 0, 0);
          wait(1000);
          break;
        }
        drawFrame();
      }
      oled::setTextColor(WHITE);
    } else if (type == P_SWITCH) {
      sprite = nSprites - 1;
    } else if (type == LETTER) {
      if (buttonX.bReleased) {
        sprite = nSprites - 1;
        oled::fillScreen(WHITE);
        oled::setTextColor(BLACK);
        typeText(letters[targetX], 0, 0);
        oled::setTextColor(WHITE);
        if (targetX == 1) {
          fire = true;
          saveProfile();
        }
        wait(1000);
        saveGame(levelIndex);
      }
    }
  }
};

float getMarioX() {
  return mario->x;
}

float getMarioY() {
  return mario->y;
}
}
