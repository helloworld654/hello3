#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
#include <Blinker.h>

const char auth[] = "your own Secret Key";
const char ssid[] = "your wifi name ";
const char pswd[] = "your wifi password";

int colorR = 255;
int colorG = 255;
int colorB = 255;
int colorW = 100;
const int PIN_LED_RED = 13;
const int PIN_LED_GREEN = 12;
const int PIN_LED_BLUE = 14;

void myRGB(int R,int G,int B,int W)
{
    int W1;
    W1 = map(W,0,100,0,255);
    Serial.print("RED:");
    Serial.print(R);
    Serial.print(", GREEN:");
    Serial.print(G);
    Serial.print(", BLUE:");
    Serial.print(B);
    Serial.print(", BRIGHTNESS:");
    Serial.println(W1);
    analogWrite(PIN_LED_RED, R*W1*0.041);
    analogWrite(PIN_LED_GREEN, G*W1*0.041);
    analogWrite(PIN_LED_BLUE, B*W1*0.041);
}

void miotColor(int32_t color)
{
    colorR = color >> 16 & 0xFF;
    colorG = color >>  8 & 0xFF;
    colorB = color       & 0xFF;
    BlinkerMIOT.color(color);
    BlinkerMIOT.print();
    myRGB(colorR,colorG,colorB,colorW);
}

void miotBright(const String & bright)
{
    colorW = bright.toInt();
    BlinkerMIOT.brightness(colorW);
    BlinkerMIOT.print();
    myRGB(colorR,colorG,colorB,colorW);
}

void setup() {
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  Blinker.begin(auth,ssid,pswd);
  BlinkerMIOT.attachColor(miotColor);
  BlinkerMIOT.attachBrightness(miotBright);
  myRGB(colorR,colorG,colorB,colorW);
}

void loop() {
  Blinker.run();
}
