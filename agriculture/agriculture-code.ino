#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define LM73_ADDR 0x4D
#define SEND_DELAY 100
//WIFI NAME&PASSWORD
char* ssid = "FourTeenYakGinTeen";
char* password =  "giveme100baht";
//---------------------------------------
int light_value, light_server, fan_server, sp_server;
String light_on, fan_on, sprinkler_on;
float temp_value;
int humid_value;
float readTemperature();
String light_text, temp_text, humid_text, light_show, temp_show, humid_show, light_status, fan_status, sp_status;
void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  Wire1.begin(4, 5);
  pinMode(light_value, INPUT);
  pinMode(27, OUTPUT); //light output2
  pinMode(26, OUTPUT); //fan output1
  pinMode(23, OUTPUT); //sprinkler output23

  pinMode(humid_value, INPUT);
  light_text = String("Lihgt Value:");
  temp_text = String("Temperature Value:");
  humid_text = String("Humid Value:");

}
void loop() {
  light_value = analogRead(36);
  temp_value = readTemperature();
  humid_value = analogRead(35);
  light_show = light_text + light_value;
  temp_show = temp_text + String((float) temp_value) + " C";
  humid_show = humid_text + humid_value;
  Serial.println(light_show);
  Serial.println(temp_show);
  Serial.println(humid_show);
  Serial.println("______________________");
  Serial.println(WiFi.localIP());
  Serial.println("______________________");



  if (WiFi.status() == WL_CONNECTED) { //Check the current connection status

    HTTPClient http;

    http.begin("http://192.168.43.177:1880/pl_light?pl_light=" + String(light_value)); //Specify the URL
    int light_http = http.GET();
    http.begin("http://192.168.43.177:1880/pl_temp?pl_temp=" + String((float)temp_value));
    int temp_http = http.GET();                                        //Make the request
    http.begin("http://192.168.43.177:1880/pl_humid?pl_humid=" + String(humid_value));
    int humid_http = http.GET();
    // to main server
    String node = "http://192.168.43.181:1880/datain_plant?pl_light=" + String(light_value) + "&pl_temp=" + String((float)temp_value) + "&pl_humid=" + String(humid_value);
    //http.begin(node);
    Serial.print(node);
    //int fffff = http.GET();


    //-----------------input switch----------------
    http.begin("http://192.168.43.177:1880/lightsw");
    light_server = http.GET();
    if (light_server == 200) {
      String light_status = http.getString();
      Serial.println(light_status);
      if (light_value > 600 || light_status == "light_on") { /*<====change light value here*/
        digitalWrite(27, HIGH);
      }
      else {
        digitalWrite(27, LOW);
      }
    } else {
      Serial.println("ERROR");
    }
    //---------------------------------------------
    http.begin("http://192.168.43.177:1880/fansw");
    fan_server = http.GET();
    if (fan_server == 200) {
      String fan_status = http.getString();
      Serial.println(fan_status);
      if (temp_value >= 33.0 || fan_status == "fan_on") {
        digitalWrite(26, LOW);
      }
      else {
        digitalWrite(26, HIGH);
      }
    } else {
      Serial.println("ERROR");
    }
    //---------------------------------------------------
    http.begin("http://192.168.43.177:1880/spsw");
    sp_server = http.GET();
    if (sp_server == 200) {
      String sp_status = http.getString();
      Serial.println(sp_status);

      if (humid_value == 0 || sp_status == "sprinkler_on") {
        digitalWrite(23, LOW);
      }
      else {
        digitalWrite(23, HIGH);
      }
    } else {
      Serial.println("ERROR");
    }
    //-------------------------------------------------------


    if (light_http > 0) { //Check for the returning code

      Serial.println(light_http);
      Serial.println(temp_http);
      Serial.println(humid_http);
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
  delay(250);
}
float readTemperature() {
  Wire1.beginTransmission(LM73_ADDR);
  Wire1.write(0x00);
  Wire1.endTransmission();

  uint8_t count = Wire1.requestFrom(LM73_ADDR, 2);
  float temp = 0.0;
  if (count == 2) {
    byte buff[2];
    buff[0] = Wire1.read();
    buff[1] = Wire1.read();
    temp += (int)(buff[0] << 1);
    if (buff[1] & 0b10000000) temp += 1.0;
    if (buff[1] & 0b01000000) temp += 0.5;
    if (buff[1] & 0b00100000) temp += 0.25;
    if (buff[0] & 0b10000000) temp *= -1.0;
  }
  return temp;
}
