#include <WiFi.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "./conf.h"
#include "./SetupWiFi.h"

#define RED 12
#define GREEN 27
#define BLUE 14

#define LDR_SENSOR 36
#define LIGHT 13

// LCD definitions
#define LCD_ADDRESS  0x27 // common address: 0x27, 0x3F
#define LCD_COLUMNS   16
#define LCD_ROWS    2

// setting PWM properties
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;

const int mediumLimit = 300;
const int highLimit = 1000;

int lumens = 0;
int status = 0;
String incomingString = "false";
String outputString = "";

WebSocketsServer webSocket = WebSocketsServer(81);

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);  

void setupLcd() {
  Wire.begin(21,22);
  delay(100);
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void rgb(int r, int g, int b) {
  ledcWrite(redChannel, r);
  ledcWrite(greenChannel, g);
  ledcWrite(blueChannel, b);
}

void setupRgb() {
  // configure LED PWM functionalitites
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(RED, redChannel);
  ledcAttachPin(GREEN, greenChannel);
  ledcAttachPin(BLUE, blueChannel);
}
 
void setup(){
  Serial.begin(115200);
  setupWiFi();
  webSocket.begin(); 
  webSocket.onEvent(webSocketEvent); 
  setupRgb();
  setupLcd();
  pinMode(LIGHT,OUTPUT);
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print("...");
}

void printLcd(int col, int row, String text) {
  lcd.clear();
  lcd.setCursor(col, row);
  lcd.print(text);
}

void processData() {
  lumens = analogRead(LDR_SENSOR);

  if (lumens > highLimit) {
    status = 1;
    rgb(0, 255, 0);
  }
   
  if (lumens >= mediumLimit && lumens <= highLimit) {
    status = 0;
    rgb(255, 100, 0);
  }
 
  if (lumens < mediumLimit) {
    status = -1;
    rgb(255, 0, 0);
  }
}

void toggleLight() {
  digitalWrite(LIGHT, (incomingString == "true") ? HIGH : LOW );
}

void output() {
  if (Serial.available() > 0) {
    incomingString = Serial.readString();
    toggleLight();
  } 

  String lcdText = "Lumens: " + (String)lumens;
  printLcd(0, 0, lcdText);

  outputString = "{\"lumens\":" + (String)lumens + ", \"status\":" + (String)status + ", \"light\":"+incomingString+" }";
  
  webSocket.broadcastTXT(outputString);
  Serial.println(outputString);
}
 
void loop(){
  processData();
  webSocket.loop(); 
  output();
  delay(100); 
}

void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED: 
      printLcd(0, 1, "Disconnected");
      Serial.println("> DISCONNECTED");
      break;
    case WStype_CONNECTED:
      printLcd(0, 1, "Connected");
      Serial.println("> CONNECTED");
      webSocket.sendTXT(num, "CONNECTED");
      break;
    case WStype_TEXT:
      String str = (char*)payload;
      incomingString = str;
      toggleLight();
      break;
  }
}