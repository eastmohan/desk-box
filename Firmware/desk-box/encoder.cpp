#include "encoder.h"
#include <Arduino.h>

static int lastCLK;
static int delta = 0;

static unsigned long pressStart = 0;
static bool pressing = false;
static bool shortPressFlag = false;
static bool longPressFlag = false;
static bool longFired = false;

#define LONG_PRESS_MS 600

void encoder_init() {
  pinMode(ENC_CLK, INPUT);
  pinMode(ENC_DT, INPUT);
  pinMode(ENC_SW, INPUT_PULLUP);
  lastCLK = digitalRead(ENC_CLK);
}

void encoder_update() {
  int clk = digitalRead(ENC_CLK);
  if(clk != lastCLK) {
    if (digitalRead(ENC_DT)!= clk) delta++;
    else delta--;
    lastCLK = clk;
  }

  bool pressed = (digitalRead(ENC_SW) == LOW);
  if (pressed && !pressing) {
    pressing = true;
    pressStart = millis();
    longFired = false;
  }
  if (pressing && pressed && !longFired) {
    if (millis() - pressStart >= LONG_PRESS_MS) {
      longPressFlag = true;
      longFired = true;
    }
  }
  if(!pressed && pressing){
    if (!longFired) shortPressFlag = true;
    pressing = false;
  }
}

int encoder_get_delta() {
  int d = delta;
  delta = 0;
  return d;
}

bool encoder_short_press() {
  if(shortPressFlag) { shortPressFlag = false; return true; }
  return false;
}

bool encoder_long_press() {
  if (longPressFlag) { longPressFlag = false; return true; }
  return false;
}