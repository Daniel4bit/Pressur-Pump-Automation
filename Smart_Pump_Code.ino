#include <WiFi.h>
#include <HTTPClient.h>

#include "mb_getdata.h"
#include "push_data_int.h"
bool st = false;

String SSID = "ssid";
String PASS = "password";

modb dev1(1, "Serverurl,");
modb dev2(2, "serverurl,");
modb dev3(3, "serverurl,");


modb devices[] = {
  dev1,
  dev2,
  dev3,
};

void setup() {
  Serial.begin(9600);
    WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("connection to wifi...");
  }
  Serial.println("connected to wifi");

}

void loop() {

  for (int i = 0; i < 3; i++) {
    devices[i].load_data();
    devices[i].push_data();
  }
  
  }
