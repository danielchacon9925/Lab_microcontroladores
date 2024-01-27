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
float vDC_1, vDC_2, vDC_3, vDC_4 = {0.00};
// AC
float vAC_1, vAC_2, vAC_3, vAC_4 = {0.00};

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

// Función de las lecturas analógicas el valor máximo entre esas lecturas.
// Escalar y ajustar el valor máximo para el rango de [-24, 24]V y retornarlo.

float obtener_val_max(float PUERTO_ANALOGICO) {

float max = 0; // Para contar la iteración
for (int j = 0; j < count; j++) // Bucle de 100 iteraciones
{
  // Lee el valor analógico del puerto
  // Y se guarda en el flotante lectura
  float lectura = analogRead(PUERTO_ANALOGICO); 
  // Compara la lectura con el valor actual max. 
  // Si la lectura es mayor que max, se actualiza val con el valor de lectura.
  if (lectura > max){ 
    max = lectura;
  }
  delayMicroseconds(300); // Pequeño delay entre las lecturas.
  // Luego se las lecturas, se realiza una conversión para escalar
  // El valor máximo que se leyó.
  max =  (((lectura * 5) / 1023) * 9.6) - 24;
}
// Se retorna el valor máximo calculado.
return PUERTO_ANALOGICO;
}

// Función que toma como argumento el número de pin y 
// retorna el voltaje DC calculado para ese canal. 
float calcularVoltajeDC(int pin) {
  
  // Lee el valor analógico del pin especificado
  float valorADC = analogRead(pin);

  // Calcula y devuelve el voltaje DC para el canal
  return (((valorADC * 5.0) / 1023.0) * 9.6) - 24;
}

////////////////////
///LOOP Principal///
////////////////////

void loop(){
  // Lee los valores analógicos de dos pines (A1 y A0) para determinar
  // el estado de los botones AC/DC y de transmisión serial.
  float read_ac_dc = analogRead(A1);
  float read_transmicion = analogRead(A0);

  if (read_ac_dc){ // AC/DC button pressed => AC MODE
    """
    Si el botón AC/DC está presionado (cuando read_ac_dc es diferente de cero) 
    realiza lecturas de valores máximos para cada canal en modo AC, 
    calcula el valor RMS y muestra los resultados.
    """
    // Lectura
    float vAC_1 = obtener_val_max(Channel_1_LED);
    float vAC_2 = obtener_val_max(Channel_2_LED);
    float vAC_3 = obtener_val_max(Channel_3_LED);
    float vAC_4 = obtener_val_max(Channel_4_LED);

    // RMS
    vAC_1 = vAC_1/sqrt(2); 
    vAC_2 = vAC_2/sqrt(2);
    vAC_3 = vAC_3/sqrt(2);
    vAC_4 = vAC_4/sqrt(2); 

    if(read_transmicion){
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
    display.print("Lectura del voltímetro en AC.\n");

    display.print("v1:", vAC_1, "V\n");
    display.print("v2:", vAC_2, "V\n"); 
    display.print("v3:", vAC_3, "V\n"); 
    display.print("v4:", vAC_1, "V\n"); 

    display.display();
    display.clearDisplay();

    //Call the function Led Alarm for AC
    LED_Alarm(vAC_1, vAC_2, vAC_3, vAC_4, MAX_AC);
    } 
      // Caso cuando se desea hacer la lectura en DC.
    else{  
      vDC_1 = calcularVoltajeDC(Channel_1_LED);
      vDC_1 = calcularVoltajeDC(Channel_2_LED);
      vDC_1 = calcularVoltajeDC(Channel_3_LED);
      vDC_1 = calcularVoltajeDC(Channel_4_LED);
      
      // Se imprimen los valores medidos en el monitor serial.
      if(read_transmicion){
        Serial.println("------------ AC/DC:  DC ------------");
        Serial.println("CHANNEL 1:", vDC_1);
        Serial.println("CHANNEL 2:", vDC_2);
        Serial.println("CHANNEL 3:", vDC_3);
        Serial.println("CHANNEL 4:", vDC_4);
      }
  
    // Se imprimen los valores medidos en el display(PCD8544-136).
    display.print("Lectura del voltímetro en DC.");
    display.print("\n");

    display.print("v1: ", vDC_1, "V\n");
    display.print("v2: ", vDC_2, "V\n");
    display.print("v3: ", vDC_3, "V\n");
    display.print("v4: ", vDC_4, "V\n");

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
void PRECAUCION(float v1, float v2, float v3, float v4, float MODE){
    ///////////////////
    // Medición en AC//
    ///////////////////
    if (MODE == MAX_AC) {
        //MAX AC VALUE: Channel 1 
      if(v1 > MAX_AC){
        digitalWrite(Channel_1_LED, HIGH);
      } else{
        digitalWrite(Channel_1_LED, LOW); 
      }
        //MAX AC VALUE: Channel 2 
      if(v2 > MAX_AC){
        digitalWrite(Channel_2_LED, HIGH);
      } else{
        digitalWrite(Channel_2_LED, LOW); 
      }
        //MAX AC VALUE: Channel 3 
      if(v3 > MAX_AC){
        digitalWrite(Channel_3_LED, HIGH);
      } else{
        digitalWrite(Channel_3_LED, LOW); 
      }
        //MAX AC VALUE: Channel 4 
      if(v4 > MAX_AC){
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