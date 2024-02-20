#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <stdlib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

/////////////////// Definición del pin de MQ2 ///////////////////
#define sensorPin 0 //D3-Naranja

/////////////////// Definición de pines para ADC ///////////////////
#define analogPin A0 /* ESP8266 Analog Pin ADC0 = A0 */

/////////////////// DEFINICIÓN PINES DE LOS LEDS ////////////////////
#define LED_BLUE 9 // LED AZUL
#define LED_RED  10 // LED ROJO

// WiFi
// Casa
//const char *ssid =  "REX2.4";    // replace with your wifi ssid and wpa2 key
//const char *pass =  "Daniel0625";//WiFi Password 

// Configuración de Wifi del celular
const char *ssid =  "Daniel's Galaxy Note20 Ultra";    // replace with your wifi ssid and wpa2 key
const char *pass =  "19990625";//WiFi Password 
const unsigned char buzzer = 14; //D5-VERDE KK, define el pin para el buzzer

/////////////////// Variables para mediciones ///////////////////
int lpg; // Valor de detección de gas
int lpgA; // Valor de detección de gas (alterno)
float TEMP; // Temperatura
float HUM; // Humedad
float PRESS; // Presión atmosférica
float ALT; // Altitud
int adcValue = 0;  // Variable para almacenar el valor del ADC
float BAT;  // Variable para almacenar el valor de la batería


// Instancia del sensor BME280
Adafruit_BME280 bme; // Sensor de temperatura, humedad y presión (I2C)

WiFiClient client; // Cliente WiFi
PubSubClient pubsub_client(client); // Cliente MQTT

/////////////////// Configuración inicial ///////////////////

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);  // Inicializa el pin LED_BUILTIN como salida
  pinMode(buzzer, OUTPUT); // Inicializa el pin del buzzer como salida
  pinMode(LED_RED, OUTPUT); // Configura el pin del LED rojo como salida
  pinMode(LED_BLUE, OUTPUT); // Configura el pin del LED azul como salida

  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios
  delay(10);


  Serial.println(F("BME280 test"));

  // Inicialización del sensor BME280
  bool status;
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not detect a BME280 sensor, Fix wiring Connections!");
    while (1);
  }

  Serial.println("-- Print BME280 readings--");
  Serial.println();

  // Conexión a la red WiFi
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

  // Conexión al servidor MQTT (Thingsboard)
  pubsub_client.setServer("iot.eie.ucr.ac.cr", 1883); // This is default if you are using thingsboard

  while (!pubsub_client.connect ("Lab_04_B72018_B87388","aknw9qgidmkg8t5radyi", NULL)) // This need to be configured by adding a new device and copying the access token
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("Thingsboard connected"); 
}

/////////////////// Bucle principal ///////////////////
 
void loop() 
{ 
  // Lectura del sensor de gas MQ2
  lpg = digitalRead(sensorPin);
  Serial.print("Air:");
  Serial.println(lpg);
  digitalWrite(LED_BUILTIN, LOW);  
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);  

  // Lectura del valor de la batería a través del ADC
  adcValue = analogRead(analogPin); /* Read the Analog Input value */
  BAT=(((float)adcValue/920)*100);
  Serial.print("Bateria = ");
  Serial.print(BAT);
  Serial.println("%");

  // Lecturas del sensor BME280
  Serial.print("Temperature = ");
  TEMP=bme.readTemperature();
  Serial.print(TEMP);
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  PRESS=(bme.readPressure() / 100.0F);
  Serial.print(PRESS);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  ALT=(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.print(ALT);
  Serial.println(" m");

  Serial.print("Humidity = ");
  HUM=bme.readHumidity();
  Serial.print(HUM);
  Serial.println(" %");

  Serial.println();
  delay(1000);

  // Encender el LED rojo si la batería está baja
  if (BAT < 20) { // Valor menor a 20
    digitalWrite(LED_RED, HIGH); // Encender el LED rojo
  }
  
  if (lpg == 0)
  {
  // Se detecta humo
  Serial.println("Smoke: Detected!");
  digitalWrite(LED_BLUE, HIGH); // Encender el LED AZUL cuando se detecte humo
  tone(buzzer, 1000); // Emitir sonido de alarma
  delay(1000);        // Durante 1 segundo
  noTone(buzzer);     // Detener el sonido
  delay(1000);        // Esperar 1 segundo             
  }

  // Crear el payload JSON con todas las variables y publicarlo en ThingsBoard
  String payload = "{";
  payload += "\"lpg\":"; payload += !lpg;
  payload += ",\"temperature\":"; payload += TEMP;
  payload += ",\"pressure\":"; payload += PRESS;
  payload += ",\"altitude\":"; payload += ALT;
  payload += ",\"humidity\":"; payload += HUM;
  payload += ",\"BAT\":"; payload += BAT;
  payload += "}";
  Serial.println(payload);

  // Publicar el payload en ThingsBoard
  if(pubsub_client.publish("v1/devices/me/telemetry", payload.c_str())) 
    Serial.println("Published");  

  // Estado de reposo cuando no se detecta humo ni la batería está baja
  else {
    digitalWrite(LED_BLUE, LOW); // Apagar el LED AZUL si no se ha detectado humo
    digitalWrite(LED_RED, LOW); // Apagar el LED ROJO si la batería no está baja
  }
}