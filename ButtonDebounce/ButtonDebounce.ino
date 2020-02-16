#include "Arduino.h"
#include "definitions.h"
#include "debBtns.h"

uint8_t gStPins[PIN_IN_BTN_QTY]{
  PIN_IN_BTN_USR_OFF,
  PIN_IN_BTN_USR_ON,
  PIN_IN_BTN_MOTION
};
// An array to hold debounced pin states.
bool gStDebStates[PIN_IN_BTN_QTY]{};


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_IN_BTN_USR_OFF, INPUT_PULLUP);
  pinMode(PIN_IN_BTN_USR_ON, INPUT_PULLUP);
  // const bool isEnabled = (ACTV_ST == LOW) ? !digitalRead(PIN_IN_BTN_USR_ON):digitalRead(PIN_IN_BTN_USR_ON);
  pinMode(PIN_IN_BTN_MOTION, INPUT_PULLUP);
  //const bool isEnabled = (ACTV_ST == LOW) ? !digitalRead(PIN_IN_BTN_MOTION):digitalRead(PIN_IN_BTN_MOTION);
  pinMode(PIN_IN_BTN_MODE, INPUT_PULLUP);

  btn_deb_Init(gStPins, gStDebStates);

  #ifdef DBG_ALL
  DBG_PORT.begin(DBG_BAUD);
  DBG_PORT.println(F("Buttons Debounce Test!"));
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
  // Debounce single pin start =====
  bool pinModeStRaw = digitalRead(PIN_IN_BTN_MODE);
  static bool pinModeStPrev{};
  static bool pinModeStDeb{};
  static uint8_t pinModeStSm{};
  static uint32_t pinModeTRef{};
  if(btn_deb_Btn(pinModeStRaw, &pinModeStPrev, &pinModeStDeb, &pinModeStSm, &pinModeTRef)){
    #ifdef DBG_ALL
    DBG_PORT.print(F("stPrevBtnMode: ")); DBG_PORT.println(pinModeStDeb);
    #endif
  }
  // Debounce single pin end   =====

  // Debounce multiple pins start =====
  btn_deb_Btns(gStPins, gStDebStates);
  static bool stPrevBtnUsrOff{};
  static bool stPrevBtnUsrOn{};
  static bool stPrevBtnMotion{};
  
  if(stPrevBtnUsrOff != gStDebStates[0]){
    #ifdef DBG_ALL
    DBG_PORT.print(F("stPrevBtnUsrOff: ")); DBG_PORT.println(gStDebStates[0]);
    #endif
    stPrevBtnUsrOff = gStDebStates[0];
  }

  if(stPrevBtnUsrOn != gStDebStates[1]){
    #ifdef DBG_ALL
    DBG_PORT.print(F("stPrevBtnUsrOn: ")); DBG_PORT.println(gStDebStates[1]);
    #endif
    stPrevBtnUsrOn = gStDebStates[1];
  }

  if(stPrevBtnMotion != gStDebStates[2]){
    #ifdef DBG_ALL
    DBG_PORT.print(F("stPrevBtnMotion: ")); DBG_PORT.println(gStDebStates[2]);
    #endif
    stPrevBtnMotion = gStDebStates[2];
  }
  // Debounce multiple pins end   =====

}
