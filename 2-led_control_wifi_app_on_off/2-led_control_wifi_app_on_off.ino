#define BLINKER_WIFI

#include <Blinker.h>

const char auth[] = "your own Secret Key";
const char ssid[] = "your wifi name ";
const char pswd[] = "your wifi password";

BlinkerButton Button1("btn-on");
BlinkerButton Button2("btn-off");
const int myLed = LED_BUILTIN;

void button1_callback(const String & state)
{
    if(!digitalRead(myLed)){
        Serial.println("the led is already on,but you enter the button 'on' second time!\n you can enter the another 'off' button!");
    }
    else{
        Serial.println("you enter the button 'on'!");
        digitalWrite(myLed, LOW);
    }
}

void button2_callback(const String & state)
{
    if(digitalRead(myLed)){
        Serial.println("the led is already off,but you enter the button 'off' second time!\n you can enter the another 'on' button!");
    }
    else{
        Serial.println("you enter the button off!");
        digitalWrite(myLed, HIGH);
    }
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);
    
    pinMode(myLed, OUTPUT);
    digitalWrite(myLed, HIGH);
    Blinker.begin(auth, ssid, pswd);

    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
}

void loop() {
    Blinker.run();
}
