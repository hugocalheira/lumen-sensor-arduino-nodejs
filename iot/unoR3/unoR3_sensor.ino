#define BLUE 9
#define GREEN 10
#define RED 11

#define LDR_SENSOR 0
#define LIGHT 8

const int mediumLimit = 600;
const int highLimit = 800;

int lumens = 0;
int status = 0;
String incomingString = "false";

void rgb(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void setupRgb() {
  pinMode(BLUE,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(RED,OUTPUT);
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
