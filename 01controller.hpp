const int PIN_UP = 14;
const int PIN_DOWN = 27;
const int PIN_LEFT = 32;
const int PIN_RIGHT = 33;
const int PIN_X = 12;
const int PIN_Y = 13;
const int JOY_HOLD = 300;

struct Button {
  Button() {}
  Button(int pin) : pin(pin) {}

  void tick() {
    bool bLast = bHeld;
    bHeld = !digitalRead(pin);
    bPressed = !bLast && bHeld;
    bReleased = bLast && !bHeld;
  }

  bool bPressed;
  bool bReleased;
  bool bHeld;
  int pin;
};

bool bJoyMoved;
int joyX, joyY;
Button buttonX(PIN_X), buttonY(PIN_Y);

void initController() {
  pinMode(PIN_UP, INPUT_PULLUP);
  pinMode(PIN_DOWN, INPUT_PULLUP);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
  pinMode(PIN_X, INPUT_PULLUP);
  pinMode(PIN_Y, INPUT_PULLUP);
}

void updateController() {
  static uint32_t t;
  yield();
  int newJoyX = digitalRead(PIN_LEFT) - digitalRead(PIN_RIGHT);
  int newJoyY = digitalRead(PIN_UP) - digitalRead(PIN_DOWN);
  buttonX.tick();
  buttonY.tick();
  if ((joyX != newJoyX) || (joyY != newJoyY) || (millis() - t > JOY_HOLD)) {
    t = millis();
    joyX = newJoyX;
    joyY = newJoyY;
    bJoyMoved = true;
  } else {
    bJoyMoved = false;
  }
}
