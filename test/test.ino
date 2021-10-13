#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#include <Blinker.h>

const char auth[] = "cd3216a3fdc2";
const char ssid[] = "TP-LINK_0957";
const char pswd[] = "HelloWorld123456";

void miotPowerState(const String & state)
{
    if (state == BLINKER_CMD_ON) {
        Serial.println("GEN the 'ON' message of led");
    }
    else if (state == BLINKER_CMD_OFF) {
        Serial.println("GET the 'OFF' message of led");
    }
}

void setup() {
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    
    Blinker.begin(auth, ssid, pswd);

    BlinkerMIOT.attachPowerState(miotPowerState);
}

void loop() {
    Blinker.run();
}
