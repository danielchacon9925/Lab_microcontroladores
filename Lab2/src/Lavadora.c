// Laboratorio 2-Daniel Chacón Mora(B72018)|Erick Sancho
// Programa realiza control automático de lavadora con 4 etapas de funcionamiento.

// Librerías utilizadas
#include <avr/io.h>
#include <util/delay.h>

//Definicion de pines

// Carga
#define HIGH_LOAD_BUTTON (1<<PA2)
#define MEDIUM_LOAD_BUTTON (1<<PD0)
#define LOW_LOAD_BUTTON (1<<PD1)
// START/PAUSE/RESET
#define START_PAUSE_BUTTON (1<<PD5)
#define LED_START_PAUSE (1<<PB4)
#define RESET_BUTTON (1<<PD4)
// LEDs de ciclo
#define LED_STATE_FILL (1<<PA1)
#define LED_STATE_WASH (1<<PA0)
#define LED_STATE_RINSE (1<<PD2)
#define LED_STATE_SPIN (1<<PD3)
// LEDS load
#define LED_HIGH_LOAD (1<<PB7)
#define LED_MEDIUM_LOAD (1<<PD6)
#define LED_LOW_LOAD (1<<PB5)


//Definicion de estados
typedef enum {
	STATE_IDE,
	STATE_FILL,
	STATE_WASH,
	STATE_RINSE,
	STATE_SPIN,
	STATE_FINISH
} state_t;

// Varibles globales
// Se define IDE como estado inicial
volatile state_t state = STATE_IDE;
volatile state_t next_state = STATE_IDE;
// Tipo de carga
volatile uint8_t load = 0;




