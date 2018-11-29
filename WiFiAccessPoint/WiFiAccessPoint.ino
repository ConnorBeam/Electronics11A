
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>
const char *ssid = "DoorLock";
const char *password = "S3CuR3Pa$5W0Rd!";
ESP8266WebServer server(80);
void handleRoot() {
  server.send(200, "text/html", "DOORLOCK SERVER");
  if (server.hasArg("sensor_reading")) { // this is the variable sent from the client
    int readingInt = server.arg("sensor_reading").toInt();
    Serial.write(readingInt);
    server.send(200, "text/html", "<hl>Data received</hl>");
  }
}

void setup() {
  delay(1000);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
