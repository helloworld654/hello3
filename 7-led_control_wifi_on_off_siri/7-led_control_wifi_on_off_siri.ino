#include <ESP8266WiFi.h>

const char ssid[] = "your wifi name ";
const char pswd[] = "your wifi password";

const int myLed = LED_BUILTIN;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(myLed, OUTPUT);
  digitalWrite(myLed, 1);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pswd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");

  server.begin();

  Serial.println(WiFi.localIP());
}
int val = 0;
void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String req = client.readStringUntil('\r');
  
  if (req.indexOf("/gpio/0") != -1) {
    Serial.println("request: ");
    Serial.println(req);
    val = 1;
  } else if (req.indexOf("/gpio/1") != -1) {
    Serial.println("request: ");
    Serial.println(req);
    val = 0;
  }

  digitalWrite(myLed, val);

  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nwelcom to child program";
  s += "</html>\n";
  client.print(s);
}
