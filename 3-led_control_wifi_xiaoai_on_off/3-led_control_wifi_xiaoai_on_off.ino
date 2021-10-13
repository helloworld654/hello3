#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#include <Blinker.h>

const char auth[] = "your own Secret Key";
const char ssid[] = "your wifi name ";
const char pswd[] = "your wifi password";

const int myLed = LED_BUILTIN;

void miotPowerState(const String & state)
{
    if (state == BLINKER_CMD_ON) {
        digitalWrite(myLed, LOW);

        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(myLed, HIGH);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}

void setup() {
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    
    pinMode(myLed, OUTPUT);
    digitalWrite(myLed, HIGH);
    
    Blinker.begin(auth, ssid, pswd);

    BlinkerMIOT.attachPowerState(miotPowerState);
}

void loop() {
    Blinker.run();
}
