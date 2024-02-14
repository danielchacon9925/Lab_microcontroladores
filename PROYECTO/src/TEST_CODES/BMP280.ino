
/***************************************************************************
  Example for BME280 Weather Station using two Sensors with I2C Communication
  written by Thiago Barros for BlueDot UG (haftungsbeschränkt)
  BSD License

  This sketch was written for the Bosch Sensor BME280.
  The BME280 is a MEMS device for measuring temperature, humidity and atmospheric pressure.
  For more technical information on the BME280, please go to ------> http://www.bluedot.space

 ***************************************************************************/


#include <Wire.h>
#include "BlueDot_BME280.h"

BlueDot_BME280 bme1;                                     //Object for Sensor 1
BlueDot_BME280 bme2;                                     //Object for Sensor 2

int bme1Detected = 0;                                    //Checks if Sensor 1 is available
int bme2Detected = 0;                                    //Checks if Sensor 2 is available
int LEDROJO1 = 13;
int LEDAZUL2 = 10;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Barómetro"));



    bme1.parameter.communication = 0;                    //I2C communication for Sensor 1 (bme1)
    bme2.parameter.communication = 0;                    //I2C communication for Sensor 2 (bme2)
    bme1.parameter.I2CAddress = 0x77;                    //I2C Address for Sensor 1 (bme1)
    bme2.parameter.I2CAddress = 0x76;                    //I2C Address for Sensor 2 (bme2)
    bme1.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 1
    bme2.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 2 
    bme1.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 1
    bme2.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor 2
    bme1.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 1
    bme2.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 2
    bme1.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 1
    bme2.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor 2
    bme1.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 1
    bme2.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor 
  
    bme1.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 1)
    bme2.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor 2)


    bme1.parameter.tempOutsideCelsius = 10;               //default value of 15°C
    bme2.parameter.tempOutsideCelsius = 10;               //default value of 15°C
  
    bme1.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
    bme2.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F



  if (bme2.init() != 0x60)
  {    
    Serial.println(F("Ops! Second BME280 Sensor not found!"));
    bme2Detected = 0;
  }

  else
  {
    Serial.println(F("Tomando datos..."));
    bme2Detected = 1;
  }

  if ((bme1Detected == 0)&(bme2Detected == 0))
  {
    Serial.println();
    Serial.println();
    Serial.println(F("Troubleshooting Guide"));
    Serial.println(F("*************************************************************"));
    Serial.println(F("1. Let's check the basics: Are the VCC and GND pins connected correctly? If the BME280 is getting really hot, then the wires are crossed."));
    Serial.println();
    Serial.println(F("2. Did you connect the SDI pin from your BME280 to the SDA line from the Arduino?"));
    Serial.println();
    Serial.println(F("3. And did you connect the SCK pin from the BME280 to the SCL line from your Arduino?"));
    Serial.println();
    Serial.println(F("4. One of your sensors should be using the alternative I2C Address(0x76). Did you remember to connect the SDO pin to GND?"));
    Serial.println();
    Serial.println(F("5. The other sensor should be using the default I2C Address (0x77. Did you remember to leave the SDO pin unconnected?"));

    Serial.println();
    
    while(1);
  }
    
  Serial.println();
  Serial.println();

}


void loop() {
   
  Serial.print(F("Duración(s):  "));
  Serial.println(float(millis())/1000);
  pinMode(LEDROJO1, OUTPUT);
  pinMode(LEDAZUL2, OUTPUT);

  if (bme2Detected)
  {
    digitalWrite(LEDROJO1, HIGH);
    delay(50);
    digitalWrite(LEDROJO1, LOW);
    delay(50);
    
    Serial.print(F("Temperature Sensor   [°C]:\t\t")); 
    Serial.println(bme2.readTempC());
 
    
    Serial.print(F("Humidity Sensor   [%]:\t\t\t")); 
    Serial.println(bme2.readHumidity());
    
    
    Serial.print(F("Pressure Sensor   [hPa]:\t\t")); 
    Serial.println(bme2.readPressure());
    
    
    Serial.print(F("Altitude Sensor   [m]:\t\t\t")); 
    Serial.println(bme2.readAltitudeMeter());
    
    digitalWrite(LEDAZUL2, HIGH);
    delay(50);
    digitalWrite(LEDAZUL2, LOW);
    delay(50);
    
        
  }

  else
  {
    Serial.print(F("Temperature Sensor  [°C]:\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Temperature Sensor  [°F]:\t\t")); 
    //Serial.println(F("Null"));
    Serial.print(F("Humidity Sensor  [%]:\t\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Pressure Sensor  [hPa]:\t\t")); 
    Serial.println(F("Null"));
    Serial.print(F("Altitude Sensor  [m]:\t\t\t")); 
    Serial.println(F("Null"));
    //Serial.print(F("Altitude Sensor  [ft]:\t\t\t")); 
    //Serial.println(F("Null"));
  }
   
   Serial.println();
   Serial.println();

   delay(1000);
   
 
}
