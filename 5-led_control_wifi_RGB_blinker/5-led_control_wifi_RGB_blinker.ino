#define BLINKER_WIFI
#include <Blinker.h>

const char auth[] = "your own Secret Key";
const char ssid[] = "your wifi name ";
const char pswd[] = "your wifi password";

const int PIN_LED_RED = 13;
const int PIN_LED_GREEN = 12;
const int PIN_LED_BLUE = 14;

BlinkerRGB RGB1("RGBKey");

void rgb1_callback(uint8_t r_value, uint8_t g_value, 
                    uint8_t b_value, uint8_t bright_value)
{
    Serial.print("R:");
    Serial.print(r_value);
    Serial.print(", G:");
    Serial.print(g_value);
    Serial.print(", B:");
    Serial.print(b_value);
    Serial.print(", bright:");
    Serial.println(bright_value);
    analogWrite(PIN_LED_RED, r_value*bright_value*0.041);
    analogWrite(PIN_LED_GREEN, g_value*bright_value*0.041);
    analogWrite(PIN_LED_BLUE, b_value*bright_value*0.041);
}

void setup() {
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_BLUE, OUTPUT);
    
    Blinker.begin(auth, ssid, pswd);
    RGB1.attach(rgb1_callback);
}

void loop() {
    Blinker.run();
}
