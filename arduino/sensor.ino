#define LDR_SENSOR 0
#define LIGHT 8

const int highLumens = 9;
const int mediumLumens = 10;
const int lowLumens = 11;

const int mediumLimit = 600;
const int highLimit = 800;

int lumens = 0;
int status = 0;
String incomingString = "false";
 
void setup(){
  Serial.begin(115200);
  pinMode(highLumens,OUTPUT);
  pinMode(mediumLumens,OUTPUT);
  pinMode(lowLumens,OUTPUT);
  pinMode(LIGHT,OUTPUT);
}
 
void turnOffLeds() {
  digitalWrite(highLumens,LOW);
  digitalWrite(mediumLumens,LOW);
  digitalWrite(lowLumens,LOW);
}

void processData() {
  lumens = analogRead(LDR_SENSOR);
  turnOffLeds();

  if (lumens > highLimit) {
    status = 1;
    digitalWrite(highLumens,HIGH);
  }
   
  if (lumens >= mediumLimit && lumens <= highLimit) {
    status = 0;
    digitalWrite(mediumLumens,HIGH);
  }
 
  if (lumens < mediumLimit) {
    status = -1;
    digitalWrite(lowLumens,HIGH);
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
