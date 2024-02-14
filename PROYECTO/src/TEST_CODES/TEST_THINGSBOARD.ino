#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <stdlib.h>

const char *ssid =  "TP-LINK_WIFI";    // replace with your wifi ssid and wpa2 key
const char *pass =  "yourwifipassword";//WiFi Password 

WiFiClient client;
PubSubClient pubsub_client(client);

void setup() 
{
       Serial.begin(9600);
       delay(10);
               
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 

      pubsub_client.setServer("demo.thingsboard.io", 1883); // This is default if you are using thingsboard

      while (!pubsub_client.connect ("Device_Name","Access Token", NULL)) // This need to be configured by adding a new device and copying the access token
      {
            delay(500);
            Serial.print(".");
      }
      Serial.println("");
      Serial.println("Thingsboard connected"); 
}
 
void loop() 
{   
     
   /* Getting the RSSI in 2 seconds intervals and Print to the Serial Port */
  delay(2000);     
  long rssi = WiFi.RSSI();
  char buffer[3];
  char* strptr = ltoa(rssi,buffer,10);
  Serial.println(strptr);

   /* Creating The JSON Payload */
 String payload = "{";
 payload += "\"rssi\":"; payload += strptr;
 payload += "}";
 Serial.println(payload);
 
  /* Publishing The Payload to the ThingsBoard IoT Cloud */
 if(pubsub_client.publish("v1/devices/me/telemetry",payload.c_str()))
    Serial.println("Published");
}