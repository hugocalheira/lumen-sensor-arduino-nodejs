const int sensor = 0;
const int light = 7;
const int highLumens = 8;
const int mediumLumens = 9;
const int lowLumens = 10;

const int mediumLimit = 600;
const int highLimit = 800;

int lumens = 0;
String incomingString = "false";
 
void setup(){
  Serial.begin(9600);
  pinMode(highLumens,OUTPUT);
  pinMode(mediumLumens,OUTPUT);
  pinMode(lowLumens,OUTPUT);
  pinMode(light,OUTPUT);
}
 
void turnOffLeds() {
  digitalWrite(highLumens,LOW);
  digitalWrite(mediumLumens,LOW);
  digitalWrite(lowLumens,LOW);
}

void processData() {
  lumens = analogRead(sensor);
  turnOffLeds();

  if (lumens > highLimit) {
    digitalWrite(highLumens,HIGH);
  }
   
  if (lumens >= mediumLimit && lumens <= highLimit) {
    digitalWrite(mediumLumens,HIGH);
  }
 
  if (lumens < mediumLimit) {
    digitalWrite(lowLumens,HIGH);
  }
}

void output() {
  if (Serial.available() > 0) {
    incomingString = Serial.readString();
    digitalWrite(light, (incomingString == "true") ? HIGH : LOW );
  } 

  Serial.println("{\"lumens\":" + (String)lumens + " ,\"light\":"+incomingString+" }");
}
 
void loop(){
  processData();
  output();
  delay(100); 
}
