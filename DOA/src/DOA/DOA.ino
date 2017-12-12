/*
This is Arduino sketch for Door Open Alert device. 
=========================================================================
For OLED graphics we are using U8glib

  Universal 8bit Graphics Library, http://code.google.com/p/u8glib/

  Copyright (c) 2012, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list
    of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice, this
    list of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
===============================================================================
*/


#include "U8glib.h"

// setup u8g object, please remove comment from one of the following constructor calls
// IMPORTANT NOTE: The following list is incomplete. The complete list of supported
// devices with all constructor calls is here: http://code.google.com/p/u8glib/wiki/device

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);	// Display which does not send ACK



//-------------------------------------------------------------------------------------

bool doorActive = 0;


//Set up for Reed Switch
const int ReedSwPin = 3;    // the number of the reedSw pin
const int OnBoardledPin = 13;      // the number of the LED pin. Only used for debugging

int ledState = HIGH;         // the current state of the output pin
int ledPrevState = LOW;
int ReedSwState;             // the current reading from the Reed Switch pin
int lastReedSwState = LOW;   // the previous reading from the input pin


unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//Set-up for Bluetooth Module
#define ExternalLedPin 7 //If we want to add LED when the door is open. This will consume extra energy so maybe not
int state = 0; //Decides in which state we are and stores data from bluetooth

//--------------------------------------------------------------------------------------

//======================================================================================
void drawActivated(void) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);

  //u8g.setFont(u8g_font_contributed);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 23, 10, "Activated");
//  u8g.drawStr( 5, 25, "Closed Time:");
//  u8g.drawStr( 5, 40, "Open Time");
  if(ledState)
  {
    u8g.drawStr( 16, 40, "Door Opened");
  }
}

void drawNotActivated(void) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 23, 35, "Not Active");
}

void checkReedSw(void) {
  int reading = digitalRead(ReedSwPin);

  if (reading != lastReedSwState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != ReedSwState) {
      ReedSwState = reading;

      // If reed switch input is high than turn LED ON
      if (ReedSwState == HIGH) {
        ledState = HIGH;
      }
      else
      {
        ledState = LOW;
      }
    }
  }
  // set the LED:
  digitalWrite(OnBoardledPin, ledState);

  // save the reading.  Next time through the loop,
  // it'll be the lastReedSwState:
  lastReedSwState = reading;


}



void getBluetoothData(void) {
  if (Serial.available() > 0) { // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
  }
  if (state == '0') {
    //digitalWrite(OnBoardledPin, LOW); // Turn LED OFF
    //Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
    doorActive = 0;
    state = 0;
  }
  else if (state == '1') {
    //digitalWrite(OnBoardledPin, HIGH);
    //Serial.println("LED: ON");;
    doorActive = 1;
    state = 0;
  }
}

void sendBluetoothData(int state) {
  if(state)
  {
    Serial.println("Door: Open");
  }
  else
  {
    Serial.println("Door: Closed");
  }
  
}

//======================================================================================



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


void setup(void) {

  // flip screen, if required
  // u8g.setRot180();

  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255, 255, 255);
  }

  //-------------------------------------------------------
  pinMode(ReedSwPin, INPUT);
  pinMode(OnBoardledPin, OUTPUT);

  // set initial LED state
  digitalWrite(OnBoardledPin, ledState);


  //-------------------------------------------------------

  //Set-up for Bluetooth (Hc-05)
  //  pinMode(OnBoard, OUTPUT);
  //  digitalWrite(OnBoardOnBoardledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module



}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void loop(void) {
  // picture loop
  u8g.firstPage();
  do {
    if (doorActive)
    {
      drawActivated();
    }
    else
    {
      drawNotActivated();
    }
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(500);

  // Add timer. If no activity for 15 seconds, turn of LED.
  checkReedSw();
  getBluetoothData();
  delay(500);
  sendBluetoothData(ledState);
  


}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

