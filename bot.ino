#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

// Humidity sensor
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE, 30);

// Replace with your network credentials
const char* ssid = "Oficina";
const char* password = "2292922000";
 
// Initialize Telegram BOT
#define BOTtoken "1459070941:AAFd8_CO8RBrww6ioq_-yq5BEZ3zv7k9bGg"  // your Bot Token (Get from Botfather) 
#define CHAT_ID "872623800"
 
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;
 
const int ledPin = 5;
bool ledState = LOW;

float humi;
float tempC;
float tempF;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(DHTPIN, INPUT);
  dht.begin(); // initialize the sensor
 
  #ifdef ESP8266
    client.setInsecure();
  #endif
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
   
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}
 
void loop() {
  delay(5000);
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
  // Leemos la temperatura en grados Fahrenheit
  float f = dht.readTemperature(true);

  Serial.println(h);
  Serial.println(t);
  Serial.println(f);

  // Mesages from telegram
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
 
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
