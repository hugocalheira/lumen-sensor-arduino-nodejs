#define RED 12
#define GREEN 27
#define BLUE 14

#define LDR_SENSOR 36
#define LIGHT 13

// setting PWM properties
const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;

const int mediumLimit = 100;
const int highLimit = 300;

int lumens = 0;
int status = 0;
String incomingString = "false";

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
  setupRgb();
  pinMode(LIGHT,OUTPUT);
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

void output() {
  if (Serial.available() > 0) {
    incomingString = Serial.readString();
    digitalWrite(LIGHT, (incomingString == "true") ? HIGH : LOW );
  } 
  Serial.println("{\"lumens\":" + (String)lumens + ", \"status\":" + (String)status + ", \"light\":"+incomingString+" }");
}
 
void loop(){
  processData();
  output();
  delay(100); 
}