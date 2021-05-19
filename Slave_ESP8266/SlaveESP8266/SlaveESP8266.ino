#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include <FirebaseESP8266.h>

const char* ssid = "WIFI FREE";
const char* password =  "Khanh123";

#define FIREBASE_HOST "https://bienaqi-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "UzPTEzxdvbctreJhVill2eEyqFYImkJDKnmV2lhq"

unsigned long previousMillis = 0;
const long interval = 5000;
const char* serverNameSignal = "http://192.168.1.120/signal";
String Signall;

FirebaseData firebaseData;

#define LED 4
 
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  //FirebaseData firebaseData;
FirebaseJson json;
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
Firebase.setReadTimeout(firebaseData,1000*60);
Firebase.setwriteSizeLimit(firebaseData,"tiny");

 
}

void loop() 
{
  int BUTTON;
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
        Signall = httpGETRequest(serverNameSignal);
        if(Signall.toInt()==1)
        {
          digitalWrite(LED,LOW);
        }
        else if(Signall.toInt()==0)
        { digitalWrite(LED,HIGH);}
      Serial.println(Signall);
      Serial.println(Signall.toInt());
      }
      else {
      Serial.println("WiFi Disconnected");
      }
  }
  Firebase.getInt(firebaseData,"/Master/Slave_1", BUTTON);
  Serial.println(BUTTON);
  if(BUTTON==1){digitalWrite(LED, HIGH);}
  else digitalWrite(LED,LOW);
  }
 String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
