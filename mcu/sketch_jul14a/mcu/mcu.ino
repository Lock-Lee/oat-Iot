#include "MicroGear.h"
#include "WiFi.h"
#include <WiFiManager.h>
#include "DHT.h"

WiFiClient client;
int timer = 0;
MicroGear microgear(client);
#include <SoftwareSerial.h>
const char *ssid = "1234";
const char *password = "12345678";

#define APPID "APPID"
#define KEY "yK9NFu6yGPE3X9g"
#define SECRET "kxrqwROU3h1VlPu4ZesoIWsFA"
#define ALIAS "esp32"

#define DHTPIN1 D5
#define DHTPIN2 D6
#define DHTTYPE DHT11
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
WiFiManager wm;
SoftwareSerial mySerial(D7, D6);
void onConnected(char *attribute, uint8_t *msg, unsigned int msglen);
void onMsghandler(char *topic, uint8_t *msg, unsigned int msglen);
/////////////////////////////////////////////////////////////
typedef struct
{
  int hour;
  int min;
  int sec;
} TIMER;
TIMER realTime;
int readTemp_1 = 0;
int readHum_1 = 0;
int readTemp_2 = 0;
int readHum_2 = 0;

////////////////////////////////////////////////////////////
TIMER Time1;
TIMER Time2;

int setTemp_start_1 = 0;
int setTemp_end_1 = 0;
int setHum_start_1 = 0;
int setHum_end_1 = 0;

int setTemp_start_2 = 0;
int setTemp_end_2 = 0;
int setHum_start_2 = 0;
int setHum_end_2 = 0;

/////////////////////////////////////////////////////////////

void setup()
{

  microgear.on(MESSAGE, onMsghandler);

  microgear.on(CONNECTED, onConnected);

  Serial.println("Starting...");
  mySerial.begin(9600);

  dht1.begin();
  dht2.begin();

  Serial.println("xxx");
  bool res;
  res = wm.autoConnect("SetWiFi"); // password protected ap

  if (!res)
  {
  }
  else
  {

    microgear.on(MESSAGE, onMsghandler);
    microgear.on(CONNECTED, onConnected);
    microgear.init(KEY, SECRET, ALIAS);

    microgear.connect(APPID);
  }
}

void loop()
{

  if (microgear.connected())
  {

    microgear.loop();
  }
  else
  {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000)
    {
      microgear.connect(APPID);
      timer = 0;
    }
    else
      timer += 100;
  }
  delay(100);
}
String getSplit(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
