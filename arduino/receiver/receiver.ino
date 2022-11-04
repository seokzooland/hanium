#include <WiFi.h>
#include <HardwareSerial.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <stdlib.h>

// Sensor Pin Info
#define LDR_PIN 32
#define SAMPLING_TIME 1

// Network Info
#define SSID "GalaxyZzang"
#define PASS "11111111"
#define DEST "http://k8s-default-backendi-6566bc7d31-1619657679.ap-northeast-2.elb.amazonaws.com/location/1/"

bool previous_state = true;
bool current_state = true;
char buff[64];

void setup() 
{
  Serial.begin(9600);

  WiFi.begin(SSID, PASS);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  delay(5000);
}

void loop()
{
  current_state = get_ldr(); 
  if(!current_state && previous_state)
  {
    sprintf(buff, "%c", get_byte());
    Serial.print(buff);
    
    int location = atoi(buff);
    if (location == 1 || location == 2 || location == 3) {
      post_http(location);
    }
  }
  previous_state = current_state;
}

void post_http(int location)
{
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(DEST);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "employee_id=1&name=이동현&location=" + String(location);
    Serial.println(httpRequestData);
    int httpResponseCode = http.PUT(httpRequestData);

    if(httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    }else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  }else {
    Serial.println("Error in WiFi connection");
  }

  delay(3000);
}

bool get_ldr()
{
  bool val = analogRead(LDR_PIN) > 90 ? true : false;
  return val;
}

char get_byte()
{
  char data_byte = 0;
  delay(SAMPLING_TIME * 1.5);
  for(int i = 0; i < 8; i++)
  {
    data_byte = data_byte | (char)get_ldr() << i;
    delay(SAMPLING_TIME);
  }
  return data_byte;
}