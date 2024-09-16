#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <ArduinoHttpClient.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include "secrets.h"

ESP8266WebServer server(80);

void GetData(){
  if(server.method() != HTTP_GET) server.send(403, "text/plain", "Method not allowed");
  for(uint8_t i = 0; i < server.args(); i++){
    Serial.println(server.arg(i));
  }
  server.send(200, "text/plain", "Message recieved");
}
void SendHttpMessage(String message){
  
}
void Wait(int seconds){
  seconds *= 1000;
  delay(seconds);
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  PRT("Startig web server");
  WiFi.mode(WIFI_STA);
  if(strlen(ssid) == 0) WiFi.begin();
  else WiFi.begin(ssid, passPhrase);
  Serial.printf("Attempting to connect to: %s\n", ssid);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  server.enableCORS(true);
  server.on("/api/Get/Message", GetData);
  server.begin();
  Serial.print("Server created with IP: ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  Wait(5);
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  WiFiClient wifi;
  HTTPClient client; //HttpClient(wifi, "192.168.0.22", 5900);
  client.begin(wifi, "http://192.168.0.22:5900/api/Test");
  int code = client.GET();
  String response = client.getString();
  Serial.printf("Status code: %d\n",code);
  Serial.print("Response: ");
  Serial.print(response);
  Serial.println("");
  delay(500);
}
