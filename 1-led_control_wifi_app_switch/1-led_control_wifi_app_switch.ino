#define BLINKER_WIFI

#include <Blinker.h>

const char auth[] = "your own Secret Key";
const char ssid[] = "your wifi name";
const char pswd[] = "your wifi password";

BlinkerButton Button1("btn-switch");

const int myLed = LED_BUILTIN;

void button1_callback(const String & state)
{
    digitalWrite(myLed, !digitalRead(myLed));
    if(digitalRead(myLed))
        Serial.println("get button state: off");
    else
        Serial.println("get button state: on");
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    
    pinMode(myLed, OUTPUT);
    digitalWrite(myLed, HIGH);
    Blinker.begin(auth, ssid, pswd);

    Button1.attach(button1_callback);
}

void loop() {
    Blinker.run();
}
