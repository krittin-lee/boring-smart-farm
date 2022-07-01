#include <WiFi.h>
#include <HttpClient.h>

#define WIFI_STA_NAME "3BB_Tunyarut_5GHz"
#define WIFI_STA_PASS "14032547"

const int fi_kun = 32;
int fi_time = 1;
String fi_kun_value = "99";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  while (!WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS)) {
    Serial.println("Name or Password weren't correct!!");
  } 
}

void loop() {
  HttpClient http;
  http.begin("http://192.168.0.130:1880/controlout_fish");
  int bottonPump = http.get();
  
  if (bottonPump = 200) {
    String fi_pump = http.getString();
    Serial.print("Pump Status: ");
    Serial.print(fi_pump);
    Serial.println("  ( 1 is botton was press. )");
  }else{
    Serial.print("Error404");
  }
  
  http.end();
}
  
}
