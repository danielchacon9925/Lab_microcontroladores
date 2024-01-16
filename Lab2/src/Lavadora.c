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

//Declaracion de funciones
// Configuraciones iniciales
void setup();
void SET_TIMER(uint8_t diferential_time_value);
// Configuraciones de 7seg display
void COUNTDOWN_TIMER(int timer);
void LED_7s_display(int valor, int display);




void setup()
{
	// Inputs
	DDRD &= ~(LOW_LOAD_BUTTON | MEDIUM_LOAD_BUTTON | START_PAUSE_BUTTON | RESET_BUTTON);
	DDRA &= ~HIGH_LOAD_BUTTON;

	// Outputs
	DDRA |= (LED_STATE_FILL | LED_STATE_WASH);
	DDRB |= (LED_START_PAUSE | LED_HIGH_LOAD | LED_LOW_LOAD);
	DDRD |= (LED_STATE_RINSE | LED_STATE_SPIN | LED_MEDIUM_LOAD);

	// Habilitar pull-up en botones
	PORTD |= (LOW_LOAD_BUTTON | MEDIUM_LOAD_BUTTON | START_PAUSE_BUTTON | RESET_BUTTON);
	PORTA |= HIGH_LOAD_BUTTON;

	//Activación de interrupciones en PCMSK 
	PCMSK |= (1<<PCINT12); // Interrupcion carga baja D1

	PCMSK2 |= (1<<PCINT11); //Interrupcion nivel media D0

    PCMSK1 |= (1<<PCINT10); // Interrupcion nivel alta A2

    //Configuracion GIMSK para activar interupciones
	GIMSK |= ((1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2)); //Interupciones de los botones de carga
	GIMSK |= ((1 << INT0) | (1 << INT1)); // Interrupcion de start/pause y reset

}

// Maquina de estados
void fsm()
{	
	if (PORTD & LED_START_PAUSE) // todo
	{
		state = next_state;
		switch (state)
		{
		case STATE_IDE:
			next_state = STATE_WATER_SUPPLY; 
			break;	
		case STATE_FILL:
			diferential_time_value = FILL(load);
			next_state = STATE_WASH;
			break;
		case STATE_WASH:
			diferential_time_value = WASH(load);
			next_state = STATE_RISE;
			break;
		case STATE_RINSE:
			diferential_time_value = RINSE(load);
			next_state = STATE_SPIN;
			break;
		case STATE_SPIN:
			diferential_time_value = SPIN(load);
			next_state = STATE_FINISH;
			break;
		case STATE_FINISH:
			FINAL(load);
			break;
		default:
			next_state = STATE_IDEL;
		}
	}
}
// Función para configurar TIMER 
void SET_TIMER(uint8_t diferential_time_value)
{
	// Escritura en registro para prescaler. Cada 64 pulsos de reloj se incrementa timer
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Definir el valor de comparación
	OCR0A = diferential_time_value; //15624 si es cada 1s para el prescaler de 64 y un reloj de 1MHz

	// Modo de operacion CTC: se genera interrupción cada segundo
	TCCR0A |= (1 << WGM01);

	// Se genera interrupción cuando timer=diferential_time_value
  	TIMSK |= (1 << OCIE0A);

	// Se habilitan interrupciones globales
	sei();
}


/// Sección de funciones de display ////

// Muestra en pantalla tiempo restante 
void COUNTDOWN_TIMER(int timer)
{
	while(timer > 0)
	{
		LED_7s_display(timer, 1);
		_delay_ms(10000);
		timer--;
	}
	LED_7s_display(0, 0);
}

// Display 7 segmentos
void LED_7s_display(int valor, int display)
{
	PORTB &= 0b10000111;
    if (display == 0)
	{
		if (valor == 0) PORTB |= 0b00000000;

		else if (valor == 1) PORTB |= 0b01000000; 

		else if (valor == 2) PORTB |= 0b00100000; 

		else if (valor == 3) PORTB |= 0b01100000;

		else if (valor == 4) PORTB |= 0b00010000;

		else if (valor == 5) PORTB |= 0b01010000;

		else if (valor == 6) PORTB |= 0b00110000;

		else if (valor == 7) PORTB |= 0b01110000;

		else if (valor == 8) PORTB |= 0b00001000;

		else PORTB |= 0b01001000;
	}
	else  // display == 1
	{
		if (valor == 0) PORTB |= 0b00100000;

		else if (valor == 1) PORTB |= 0b01000100; 

		else if (valor == 2) PORTB |= 0b00100100; 

		else if (valor == 3) PORTB |= 0b01100100;

		else if (valor == 4) PORTB |= 0b00010100;

		else if (valor == 5) PORTB |= 0b01010100;

		else if (valor == 6) PORTB |= 0b00110100;

		else if (valor == 7) PORTB |= 0b01110100;

		else if (valor == 8) PORTB |= 0b00001100;

		else PORTB |= 0b01001100;
	}
}