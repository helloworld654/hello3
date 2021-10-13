#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT 
#define BLINKER_DUEROS_LIGHT 

#include <Blinker.h>
#include <ESP8266WiFi.h>

const char auth[] = "your own Secret Key";
const char ssid[] = "your wifi name ";
const char pswd[] = "your wifi password";
const int myLED = 4;
BlinkerButton Button1("btn-on");
BlinkerButton Button2("btn-off");
WiFiServer server(80);

void button1_callback(const String & state)
{
    digitalWrite(myLED, HIGH);
    Serial.println("you enter the button 'on'!");
}

void button2_callback(const String & state)
{
    digitalWrite(myLED, LOW);
    Serial.println("you enter the button off!");
}

void miotPowerState(const String & state)
{
    if (state == BLINKER_CMD_ON) {
        digitalWrite(myLED, HIGH);
        Serial.println("the linght is ON from XIAO AI TONG XUE!");
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(myLED, LOW); 
        Serial.println("the linght is OFF from XIAO AI TONG XUE!");
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}

void duerPowerState(const String & state)
{
    if (state == BLINKER_CMD_ON) {
        digitalWrite(myLED, HIGH);
        Serial.println("the linght is ON from XIAO DU XIAO DU!");
        BlinkerDuerOS.powerState("on");
        BlinkerDuerOS.print();
    } 
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(myLED, LOW);
        Serial.println("the linght is OFF from XIAO DU XIAO DU!");
        BlinkerDuerOS.powerState("off");
        BlinkerDuerOS.print();
    }
}

void setup() {
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(myLED, OUTPUT);
    digitalWrite(myLED, HIGH);
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerDuerOS.attachPowerState(duerPowerState);

    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    server.begin();
    Serial.println(WiFi.localIP());
}
int val = 1;
void loop() {
    Blinker.run();
    WiFiClient client = server.available();
    if (!client) {
      delay(100);
      return;
    }
    String req = client.readStringUntil('\r');
    if (req.indexOf("/gpio/0") != -1) {
      Serial.println("request: ");
      Serial.println(req);
      val = 0;
    } else if (req.indexOf("/gpio/1") != -1) {
      Serial.println("request: ");
      Serial.println(req);
      val = 1;
    }
    digitalWrite(myLED, val);
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nwelcom to child program";
    s += "</html>\n";
    client.print(s);
}
