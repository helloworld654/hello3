String inString = "";
int n = 0;
int red = 0;
int green = 0;
int blue = 0;
int bright = 0;
const int PIN_LED_RED = 13;
const int PIN_LED_GREEN = 12;
const int PIN_LED_BLUE = 14;
void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  Serial.println();
  Serial.print("input the RED value:");
}
void loop() {
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    inString += (char)inChar;
    if (inChar=='\n' || inChar=='\r') {
      if(n == 0){
        red = inString.toInt();
        Serial.println(red);
        Serial.print("input the GREEN value:");
      }
      else if(n == 1){
        green = inString.toInt();
        Serial.println(green);
        Serial.print("input the BLUE value:");
      }
      else if(n == 2){
        blue = inString.toInt();
        Serial.println(blue);
        Serial.print("input the BRIGHTNESS value:");
      }
      else{
        bright = inString.toInt();
        Serial.println(bright);
        analogWrite(PIN_LED_RED, red*bright*0.041);
        analogWrite(PIN_LED_GREEN, green*bright*0.041);
        analogWrite(PIN_LED_BLUE, blue*bright*0.041);
        Serial.println("the led is already OPEN!");
        Serial.println("you can input the RED GREEN BLUE and BRIGHTNESS once again!");
        Serial.print("input the RED value:");
        n = -1;
      }
      n++;
      inString = "";
    }
  }
  delay(10);
}
