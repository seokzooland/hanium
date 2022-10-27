#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HttpClient.h>
#include <stdlib.h>

#define LDR_PIN A6
#define LED 4
#define SAMPLING_TIME 1
#define SSID "iptime604"
#define PW



//Declaration
bool led_state = false;
bool previous_state = true;
bool current_state = true;
char buff[64];
void setup() 
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  
}

void loop() 
{
  current_state = get_ldr(); 
  if(!current_state && previous_state)
  {
    sprintf(buff, "%c", get_byte());
    Serial.print(buff);
  }
  digitalWrite(LED, current_state);
  previous_state = current_state;
}
bool get_ldr()
{
  bool val = analogRead(LDR_PIN) > 90 ? true : false;
  digitalWrite(LED, val);
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

// //#include <SoftwareSerial.h>
// #include <ArduinoJson.h>
// #include <WiFi.h>
// #include <HTTPClient.h>
// #include <HttpClient.h>
// #include <stdlib.h>

// #define LDR_PIN A6
// #define LED 4
// #define SAMPLING_TIME 1

// const char* ssid = "iptime604";
// const char* password = "01097893615";
// const char* serverName = "http://3.38.192.3:8000/location/4/";

// int value;
// IPAddress hostIp(3, 38, 192, 3);
// int SERVER_PORT = 8000;
// WiFiClient client;

// //Declaration
// bool led_state = false;
// bool previous_state = true;
// bool current_state = true;
// char buff[64];
// void setup() 
// {
//   pinMode(LED,OUTPUT);
//   Serial.begin(19200);


//   WiFi.begin(ssid, password);
//   while(WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     //Serial.println("Connecting to WiFi..");
//   }

//   //Serial.println("Connected to the WiFi network");

// }

// void loop() 
// {

//   Serial.println("Started!");

//   current_state = get_ldr(); 
//   Serial.println(current_state);
//   if(!current_state && previous_state)
//   {
    
//     sprintf(buff, "%c", get_byte());
//     Serial.print(buff);

//     int floor = atoi(buff);
//     Serial.print(floor);
//     if (floor == 1 || floor == 2) {
//       post_http(floor);
//     }
//   }

//   digitalWrite(LED, current_state);
//   previous_state = current_state;

// }
// void post_http(int lo)
// {
//   if(WiFi.status() == WL_CONNECTED) {
//     value = analogRead(LDR_PIN);
//     HTTPClient http;

//     http.begin(serverName);
//     http.addHeader("Content-Type", "application/x-www-form-urlencoded");

//     String httpRequestData = "employee_id=4&name=leegunhee&location=" + String(lo);
//     Serial.println(httpRequestData);
//     int httpResponseCode = http.PUT(httpRequestData);

//     if(httpResponseCode > 0) {
//       String response = http.getString();
//       Serial.println(httpResponseCode);
//       Serial.println(response);
//     }else {
//       Serial.print("Error on sending POST: ");
//       Serial.println(httpResponseCode);
//     }

//     http.end();

//   }else {
//     Serial.println("Error in WiFi connection");
//   }

//   delay(30000000);
// }

// bool get_ldr()
// {
//   bool val = analogRead(LDR_PIN) > 200 ? true : false;
//   digitalWrite(LED, val);
//   return val;
// }

// char get_byte()
// {
//   char data_byte = 0;
//   delay(SAMPLING_TIME);
//   for(int i = 0; i < 8; i++)
//   {
//     data_byte = data_byte | (char)get_ldr() << i;
//     delay(SAMPLING_TIME);
//   }

//   return data_byte;

// }