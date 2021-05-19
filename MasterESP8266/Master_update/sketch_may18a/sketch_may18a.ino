
#include <ESP8266WiFi.h>
#include "FirebaseESP8266.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "WIFI FREE";
const char* password =  "Khanh123";


#define FIREBASE_HOST "https://bienaqi-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "UzPTEzxdvbctreJhVill2eEyqFYImkJDKnmV2lhq"

float temp=34;
float humid=64;
int AQI=83;
int PM10=44;
int PM25=33;
int pressure=1004;
String path, signal1;
FirebaseData firebaseData;

AsyncWebServer server(80);
void setup() {
  pinMode(4,INPUT);
  
  Serial.begin(115200);
 //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network: ");
  Serial.println(WiFi.localIP());

    

  
    //FirebaseData firebaseData;
FirebaseJson json;
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
Firebase.setReadTimeout(firebaseData,1000*60);
Firebase.setwriteSizeLimit(firebaseData,"tiny");

server.on("/signal", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send_P(200, "text/plain", signal1.c_str());
});
server.begin();

}

    
  
void loop() {
  
     Firebase.setFloat(firebaseData,"/Master/Temp",temp);
 
  Firebase.setFloat(firebaseData,"/Master/Humid",humid);
 
  Firebase.setInt(firebaseData,"/Master/AQI",AQI);
  Firebase.setFloat(firebaseData,"/Master/PM10",PM10);
  Firebase.setFloat(firebaseData,"/Master/PM25",PM25);
  Firebase.setFloat(firebaseData,"/Master/Pressure",pressure);

  signal1=(String)digitalRead(4);
  int a=digitalRead(4);
  Serial.println(a);

  
  }
