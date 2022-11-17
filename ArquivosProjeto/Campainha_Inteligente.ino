#define MySSID "SSID-Wifi"
#define MyWifiPassword "Senha-Wifi"
 
#define CHAT_ID "ID-Chat-Telegram"
#define BOT_TOKEN "Token-Bot-Telegram"
 

#define buttonPin D3 //definir pino com capacidade Pull-Up
 
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

 
ESP8266WiFiMulti WiFiMulti;
WiFiClientSecure secured_client;
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
 
 
void setup()
{

pinMode(buttonPin, INPUT_PULLUP);
 
WiFi.mode(WIFI_STA);
WiFiMulti.addAP(MySSID, MyWifiPassword);
 
while(WiFiMulti.run() != WL_CONNECTED)
{
delay(500);
}
 
configTime(0, 0, "pool.ntp.org");
secured_client.setTrustAnchors(&cert);
}
 
void loop()
{
static uint64_t then = millis();
 
if(millis() - then >= 5000)
{
if(!digitalRead(buttonPin))
{
 
bot.sendMessage(CHAT_ID, "Alguem esta na porta!", "");
then = millis();
}
}
}