#include <jsonlite.h>
#include <LWiFi.h>
#include <LWiFiClient.h>

#include "M2XStreamClient.h"

char ssid[] = "<ssid>"; //  your network SSID (name)
char pass[] = "<WPA password>";    // your network password (use for WPA, or use as key for WEP)

char deviceId[] = "<device id>"; // Device you want to push to
char streamName[] = "<stream name>"; // Stream you want to push to
char m2xKey[] = "<M2X access key>"; // Your M2X access key

LWiFiClient client;
M2XStreamClient m2xClient(&client, m2xKey);

void setup() {
  Serial.begin(9600);
  while (!Serial.available()) {}
  while (Serial.available()) { Serial.read(); }
  LWiFi.begin();

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  if (LWiFi.connectWPA(ssid, pass) < 0) {
    Serial.println("Failed to connect to Wifi!");
    /* Loop forever */
    while (1) ;
  }
  Serial.println("Connected to wifi");
}

void loop() {
  int response = m2xClient.updateStreamValue(deviceId, streamName, 42);
  Serial.print("M2X client response code: ");
  Serial.println(response);

  if (response == -1) while(1) ;

  delay(5000);
}
