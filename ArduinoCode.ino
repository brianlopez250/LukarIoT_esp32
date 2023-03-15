#include <WiFi.h>
#include <HTTPClient.h>
#define Button 5 //button connected to gpio 5
//modify  this part acording to your WIFI
const char * ssid = "BALEXA"; //Your Wifi name 
const char * password = "b12345678"; //Your Wifi password

//modify  this part acording to your IFTTT
String server = "http://maker.ifttt.com";
String eventName = "esp32_alert";//your event name for IFTTT
String IFTTT_Key = "bfAPHi9mofE7FeMP1c_kzN"; //your key for IFTTT
String IFTTTUrl="https://maker.ifttt.com/trigger/esp32_alert/json/with/key/bfAPHi9mofE7FeMP1c_kzN";  //your IFTTT url


void setup() {
  Serial.begin(9600);

 //Initialize button
  pinMode(Button,INPUT);

  //Wifi Connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}


void SendAlert(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key;  

  //Starts Connection
  Serial.println(url);
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url);
  Serial.print("[HTTP] GET...\n");
  int httpCode = http.GET();
  
  //If failed connection
  if(httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET failed: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

}

void loop() {
  
  int ButtonState=digitalRead(Button); //Reads the button pin
  
  if(ButtonState==HIGH){
    SendAlert(); //Sends the alert if the button is pressed 
    Serial.println("Sent");
  }

}
