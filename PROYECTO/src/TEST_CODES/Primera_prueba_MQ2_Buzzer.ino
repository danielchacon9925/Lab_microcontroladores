#include <ESP8266WiFi.h>
#define sensorPin 4
//#define buzzer 5


// WiFi
const char *ssid =  "REX2.4";     // Enter your WiFi Name
const char *pass =  "Daniel0625"; // Enter your WiFi Password

//const int sensorPin= 2; //D4-NARANJA
const unsigned char buzzer= 5; //D3-VERDE KK

int lpg;

void send_event(const char *event);
const char *host = "maker.ifttt.com";
const char *privateKey = "BrGvT48etH1P7TA8olaC-";

WiFiClient client;

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, pass); 
  Serial.println();
  Serial.print("Connecting...");

  while(WiFi.status() != WL_CONNECTED) 
  {
    delay(550);
    Serial.print(".");
  }
  Serial.println("IP Address: ");
  Serial.print(WiFi.localIP());
}

void loop() 
{
     lpg = digitalRead(sensorPin);
     Serial.print("Air:");
     Serial.println(lpg);
     digitalWrite(LED_BUILTIN, LOW);  
     delay(1000);                      // Wait for a second
     digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
     delay(2000);
         
  if (lpg == 0)
    {
    Serial.println("Smoke: Detected!");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec      
    send_event("LPG_event");
            
    }
}


void send_event(const char *event)
{
  Serial.print("Connecting to ");
  Serial.println(host);  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }  
  // We now create a URI for the request
  String url = "/trigger/";
  url += event;
  url += "/with/key/";
  url += privateKey;  
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  while(client.connected())
  {
    if(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    } else {
      // No data yet, wait a bit
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
  client.stop();
}
