#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define RXD2 16
#define TXD2 17

void messageReceived(const uint8_t *macAddr, const uint8_t *incomingData, int len)
{
  Serial2.write(incomingData, len);
  Serial2.write('\n');

  for (int i = 0; i < len; i++)
  {
    Serial.print((char)incomingData[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  Serial.print("MAC-Address: ");
  Serial.println(WiFi.macAddress());

  WiFi.mode(WIFI_STA);

  esp_now_init();
  esp_now_register_recv_cb(messageReceived);
}

void loop()
{
}