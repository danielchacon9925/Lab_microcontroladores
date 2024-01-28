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

// Variables de medición
//  DC
float vDC_1, vDC_2, vDC_3, vDC_4 = {0.00};
// AC
float vAC_1, vAC_2, vAC_3, vAC_4 = {0.00};

// MAX values
// DC
#define MAX_DC 20
#define MIN_DC 20
// AC: MAX VOLTAGE=RMS_max=20/sqrt(20)
#define MAX_AC 14.14
#define MIN_AC -14.14

// Setup
void setup()
{

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
  display.setTextSize(1);      // Tamaño de texto
  display.setTextColor(BLACK); // Color de texto
  display.setCursor(5, 0);     // Establece cursor en coordenadas
  display.println("Voltímetro AC/DC");
  display.setCursor(5, 10);
  display.println("Midiendo: ");
  display.display();
  delay(2000);
  display.clearDisplay(); // Clear display
}

// Función de las lecturas analógicas el valor máximo entre esas lecturas.
// Escalar y ajustar el valor máximo para el rango de [-24, 24]V y retornarlo.

// Function that meters a little range of measurements
// and select the max value of them, then is return
// the real value in the range of [-24, 24] v
float obtener_val_max(float PUERTO_ANALOGICO)
{
  float voltage = 0;
  float rawValue = 0;
  for (int i = 0; i < 100; i++)
  {
    //  float val = analogRead(PUERTO_ANALOGICO);
    //  if (val > max_val)
    //  {
    //    max_val = val;
    //  }
    //  delayMicroseconds(150);
    //}
    // max_val = (((max_val * 5.0) / 1023.0) * 9.6) - 24;
    // return max_val;
    // Read the raw ADC value from the analog pin
    int rawValue = analogRead(PUERTO_ANALOGICO);

    // Convert the raw ADC value to voltage
    float voltage = ((rawValue / 1023.0) * 5.0) * (0.83 + 0.165);

    return voltage;
  }
}

////////////////////
/// LOOP Principal///
////////////////////

void loop()
{
  // Lee los valores analógicos de dos pines (A1 y A0) para determinar
  // el estado de los botones AC/DC y de transmisión serial.
  float read_ac_dc = analogRead(A5);
  float read_transmicion = analogRead(A4);

  if (read_ac_dc)
  { // AC/DC button pressed => AC MODE

    float vAC_1 = obtener_val_max(A3);
    float vAC_2 = obtener_val_max(A2);
    float vAC_3 = obtener_val_max(A1);
    float vAC_4 = obtener_val_max(A0);

    // RMS
    vAC_1 = (vAC_1 / sqrt(2)) + 20.5;
    vAC_2 = (vAC_2 / sqrt(2)) + 9.32;
    vAC_3 = (vAC_3 / sqrt(2)) - 10.92;
    vAC_4 = (vAC_4 / sqrt(2)) - 23.72;

    if (read_transmicion)
    {
      Serial.println("------------ AC/DC:  AC ------------");
      Serial.println("CHANNEL 1:");
      Serial.println(vAC_1);
      Serial.println("CHANNEL 2:");
      Serial.println(vAC_2);
      Serial.println("CHANNEL 3:");
      Serial.println(vAC_3);
      Serial.println("CHANNEL 4:");
      Serial.println(vAC_4);
    }

    // Mostrar los valores medidos en el display(PCD8544-136).
    display.print("Voltímetro en AC.\n");

    display.print("vAC_1:");
    display.print(vAC_1);
    display.print("\n");
    display.print("vAC_2:");
    display.print(vAC_2);
    display.print("\n");
    display.print("vAC_3:");
    display.print(vAC_3);
    display.print("\n");
    display.print("vAC_4:");
    display.print(vAC_4);
    display.print("\n");

    display.display();
    display.clearDisplay();

    // Call the function Led Alarm for AC
    PRECAUCION(vAC_1, vAC_2, vAC_3, vAC_4, MAX_AC);
  }
  // Caso cuando se desea hacer la lectura en DC.
  else
  {
    vDC_1 = obtener_val_max(A3) + 19.09;
    vDC_2 = obtener_val_max(A2) + 8.22;
    vDC_3 = obtener_val_max(A1) - 10.48;
    vDC_4 = obtener_val_max(A0) - 23.61;

    // Se imprimen los valores medidos en el monitor serial.
    if (read_transmicion)
    {
      Serial.println("------------ AC/DC:  DC ------------");
      Serial.println("CHANNEL 1:");
      Serial.println(vDC_1);
      Serial.println("CHANNEL 2:");
      Serial.println(vDC_2);
      Serial.println("CHANNEL 3:");
      Serial.println(vDC_3);
      Serial.println("CHANNEL 4:");
      Serial.println(vDC_4);
    }

    // Se imprimen los valores medidos en el display(PCD8544-136).
    display.print("Voltímetro en DC.");
    display.print("\n");

    display.print("vDC_1:");
    display.print(vDC_1);
    display.print("\n");
    display.print("vDC_2:");
    display.print(vDC_2);
    display.print("\n");
    display.print("vDC_3:");
    display.print(vDC_3);
    display.print("\n");
    display.print("vDC_4:");
    display.print(vDC_4);
    display.print("\n");

    display.display();
    display.clearDisplay();

    // Llama a una función Precaucion para verificar si se debe activar
    // un LED de alarma basado en los valores medidos.
    PRECAUCION(vDC_1, vDC_2, vDC_3, vDC_3, MAX_DC);
  }

  // Se aplica un retardo antes de reiniciar el bucle.
  // Para estabilizar la lectura y controlar la frecuencia de actualización.
  delay(150);
}

// Alarma para cuando se sobrepasa valor de medición máximo
void PRECAUCION(float v1, float v2, float v3, float v4, float MODE)
{
  ///////////////////
  // Medición en AC//
  ///////////////////
  if (MODE == MAX_AC)
  {
    // MAX AC VALUE: Channel 1
    if (v1 > MAX_AC || v1 > -MAX_AC)
    {
      digitalWrite(Channel_1_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_1_LED, LOW);
    }
    // MAX AC VALUE: Channel 2
    if (v2 > MAX_AC)
    {
      digitalWrite(Channel_2_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_2_LED, LOW);
    }
    // MAX AC VALUE: Channel 3
    if (v3 > MAX_AC)
    {
      digitalWrite(Channel_3_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_3_LED, LOW);
    }
    // MAX AC VALUE: Channel 4
    if (v4 > MAX_AC || v4 < -MAX_AC)
    {
      digitalWrite(Channel_4_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_4_LED, LOW);
    }
    ///////////////////
    // Medición en DC//
    ///////////////////
  }
  else
  {
    // MAX DC VALUE: Channel 1
    if (v1 > MAX_DC || v1 > -MAX_DC)
    {
      digitalWrite(Channel_1_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_1_LED, LOW);
    }
    // MAX DC VALUE: Channel 2
    if (v2 > MAX_DC)
    {
      digitalWrite(Channel_2_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_2_LED, LOW);
    }
    // MAX DC VALUE: Channel 3
    if (v3 > MAX_DC)
    {
      digitalWrite(Channel_3_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_3_LED, LOW);
    }
    // MAX DC VALUE: Channel 4
    if (v4 > MAX_DC || v4 > -MAX_DC)
    {
      digitalWrite(Channel_4_LED, HIGH);
    }
    else
    {
      digitalWrite(Channel_4_LED, LOW);
    }
  }
}
