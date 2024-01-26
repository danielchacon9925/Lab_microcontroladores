// Laboratorio 3: Daniel Chacón Mora (B72018), Erick Sancho Alvarado

//  Librerías utilizadas

// GFX: Funciones y operaciones básicas para el dibujo de formas geométricas, texto y manipulación de píxeles en una pantalla.
#include <Adafruit_GFX.h>   
// PCD8544: Funciones para la inicialización de la pantalla, el dibujo de píxeles, la escritura de texto y otras operaciones gráficas.
#include <Adafruit_PCD8544.h>


/////////////////////////
// Definición de pines //
/////////////////////////

// Pantalla LCD PCD8544
#define SCLK 8
#define DIN 9
#define DC 10
#define CS 11
#define RST 12
// LEDs de alerta de exceso de tensión por medir
#define Channel_1_LED 4
#define Channel_2_LED 5
#define Channel_3_LED 6
#define Channel_4_LED 7

// Inicialización de display
Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS, RST);

//Variables de medición
// DC
float vDC_A, vDC_B, vDC_C, vDC_D = {0.00};
// AC
float vAC_A, vAC_B, vAC_C, vAC_D = {0.00};

// MAX values
// DC
#define MAX_DC 20
// AC: MAX VOLTAGE=RMS_max=20/sqrt(20)
#define MAX_AC 14.14 

// Setup
void setup() {

  // Initialize serial communication
  Serial.begin(9600);
  
  // LEDs se configuran como salidas
  pinMode(Channel_1_LED, OUTPUT);
  pinMode(Channel_2_LED, OUTPUT);
  pinMode(Channel_3_LED, OUTPUT);
  pinMode(Channel_4_LED, OUTPUT);
  
  // Llamado a función de display
  // Inicialización
  display.begin();
  // Constraste
  display.setContrast(50);
  // Adafruit LOGO: Si se muestra florcita se inició bien
  display.display();
  delay(1500);
  
  // Configuración inicial de display
  display.clearDisplay();
  display.setTextSize(1);   // Tamaño de texto
  display.setTextColor(BLACK);  //Color de texto
  display.setCursor(5,0);   // Establece cursor en coordenadas
  display.println("Voltímetro AC/DC");
  display.setCursor(5,10);
  display.println("Midiendo: ");
  display.display();
  delay(2000);
  display.clearDisplay(); // Clear display
}

void loop(){
    // Por desarrollar
    // Debe estar constantemente reciebiendo mediciones y mostrando valores en pantalla
}

// Alarma para cuando se sobrepasa valor de medición máximo
void PRECAUCION(float vA, float vB, float vC, float vD, float MODE){
    ///////////////////
    // Medición en AC//
    ///////////////////
    if (MODE == MAX_AC) {
        //MAX AC VALUE: Channel 1 
      if(vA > MAX_AC){
        digitalWrite(Channel_1_LED, HIGH);
      } else{
        digitalWrite(Channel_1_LED, LOW); 
      }
        //MAX AC VALUE: Channel 2 
      if(vB > MAX_AC){
        digitalWrite(Channel_2_LED, HIGH);
      } else{
        digitalWrite(Channel_2_LED, LOW); 
      }
        //MAX AC VALUE: Channel 3 
      if(vC > MAX_AC){
        digitalWrite(Channel_3_LED, HIGH);
      } else{
        digitalWrite(Channel_3_LED, LOW); 
      }
        //MAX AC VALUE: Channel 4 
      if(vD > MAX_AC){
        digitalWrite(Channel_4_LED, HIGH);
      } else{
        digitalWrite(Channel_4_LED, LOW); 
      }
    ///////////////////
    // Medición en DC//
    ///////////////////
    } else{  
        //MAX DC VALUE: Channel 1 
      if(vA > MAX_DC || vA < -MAX_DC){
        digitalWrite(Channel_1_LED, HIGH);
      } else{
        digitalWrite(Channel_1_LED, LOW); 
      }
        //MAX DC VALUE: Channel 2 
      if(vB > MAX_DC || vB < -MAX_DC){
        digitalWrite(Channel_2_LED, HIGH);
      } else{
        digitalWrite(Channel_2_LED, LOW); 
      }
        //MAX DC VALUE: Channel 3 
      if(vC > MAX_DC || vC < -MAX_DC){
        digitalWrite(Channel_3_LED, HIGH);
      } else{
        digitalWrite(Channel_3_LED, LOW); 
      }
        //MAX DC VALUE: Channel 4 
      if(vD > MAX_DC || vD < -MAX_DC){
        digitalWrite(Channel_4_LED, HIGH);
      } else{
        digitalWrite(Channel_4_LED, LOW); 
      }
    }
    
}