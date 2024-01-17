// Laboratorio 2-Daniel Chacón Mora(B72018)|Erick Sancho
// Programa realiza control automático de lavadora con 4 etapas de funcionamiento.

// Librerías utilizadas
// Brinda acceso a entradas y salidas de microcontrolador
#include <avr/io.h>
// Permite usar función _delay_ms()
#include <util/delay.h>
// Utilizada para habilitar interrupciones globales
#include <avr/interrupt.h>
#include <stdio.h>



//Definicion de pines

// Carga
#define HIGH_LOAD_BUTTON (1<<PD6)
#define MEDIUM_LOAD_BUTTON (1<<PB0)
#define LOW_LOAD_BUTTON (1<<PA0)
// START/PAUSE/RESET
#define RESET_BUTTON (1<<PD3)
#define START_PAUSE_BUTTON (1<<PD2)
#define LED_START_PAUSE (1<<PB1)
// LEDs de ciclo
#define LED_STATE_FILL (1<<PB7)
#define LED_STATE_WASH (1<<PA2)
#define LED_STATE_RINSE (1<<PD4)
#define LED_STATE_SPIN (1<<PD5)
// LEDS load
#define LED_HIGH_LOAD (1<<PD0)
#define LED_MEDIUM_LOAD (1<<PD1)
#define LED_LOW_LOAD (1<<PA1)



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
// Tiempo
volatile uint8_t diferential_time_value = 0;
volatile uint8_t time = 0, time_left = 0;

//Declaracion de funciones
// Configuraciones iniciales
void setup();
void SET_TIMER(uint8_t diferential_time_value);
// Configuraciones de 7seg display
void COUNTDOWN_TIMER(int timer);
void LED_7s_display(int valor, int display);
// Máquina de estados
void fsm();
// Estados
uint8_t FILL(uint8_t load);
uint8_t WASH(uint8_t load);
uint8_t RINSE(uint8_t load);
uint8_t SPIN(uint8_t load);
void FINAL(uint8_t load);

int main(void)
{
	// Se inicia configurando entradas, salidas e interrupciones
    setup();
	// Se pone TIMER en 0
	SET_TIMER(diferential_time_value);
	// Bucle con máquina de estados
	while(1){
		fsm();
	}
	return 0;
}


void setup()
{
	// Inputs
	DDRD &= ~(HIGH_LOAD_BUTTON | RESET_BUTTON | START_PAUSE_BUTTON );
	DDRB &= ~MEDIUM_LOAD_BUTTON;
	DDRA &= ~LOW_LOAD_BUTTON;

	// Outputs
	DDRA |= ( LED_LOW_LOAD | LED_STATE_WASH);
	DDRB |= (LED_START_PAUSE | LED_STATE_FILL);
	DDRD |= (LED_STATE_RINSE | LED_STATE_SPIN | LED_MEDIUM_LOAD | LED_HIGH_LOAD);

	// Habilitar pull-up en botones
	PORTD |= (START_PAUSE_BUTTON | RESET_BUTTON | HIGH_LOAD_BUTTON);
	PORTB |= MEDIUM_LOAD_BUTTON;
	PORTA |= LOW_LOAD_BUTTON;


	//Configucion registro PCMSK para activar interupciones
	PCMSK |= (1<<PCINT8); // Interrupcion carga baja A0

	PCMSK2 |= (1<<PCINT0); //Interrupcion nivel media B0

    PCMSK1 |= (1<<PCINT17); // Interrupcion nivel alta D6

    //Configuracion GIMSK para activar interupciones
	GIMSK |= ((1<<PCIE0) | (1<<PCIE1) | (1<<PCIE2)); //Interupciones de los botones de carga
	GIMSK |= ((1 << INT0) | (1 << INT1)); // Interrupcion de start/pause y reset

}

void SET_TIMER(uint8_t diferential_time_value)
{
	// Configurar el prescaler a 64
	TCCR0B |= (1 << CS01) | (1 << CS00);

	// Definir el valor de comparación
	OCR0A = diferential_time_value; //15624 si es cada 1s para el prescaler de 64 y un reloj de 1MHz

	// Configuracion del modo de operacion CTC
	TCCR0A |= (1 << WGM01);

	// Habilitar la interrupción de comparación en la salida A
  	TIMSK |= (1 << OCIE0A);

	// Se habilitan interrupciones globales
	sei();
}

void fsm()
{	
	if (PORTB & LED_START_PAUSE) // todo
	{
		state = next_state;
		switch (state)
		{
		case STATE_IDE:
			next_state = STATE_FILL; 
			break;	
		case STATE_FILL:
			diferential_time_value = FILL(load);
			next_state = STATE_WASH;
			break;
		case STATE_WASH:
			diferential_time_value = WASH(load);
			next_state = STATE_RINSE;
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
			next_state = STATE_IDE;
		}
	}
}

uint8_t FILL(uint8_t load)
{	
    // Input
	PORTA &= ~LED_STATE_WASH;
    PORTD &= ~(LED_STATE_RINSE | LED_STATE_SPIN);
    // Output
    PORTB |= LED_STATE_FILL;

    // Selección de carga baja
	if (load == 1){
		diferential_time_value = 1;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga media
	else if (load == 2){
		diferential_time_value = 2;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga pesada
	else if (load == 3){
		diferential_time_value = 3;
		COUNTDOWN_TIMER(diferential_time_value);
	}

	return diferential_time_value;
}

uint8_t WASH(uint8_t load)
{	
    // Input
    PORTB &= ~LED_STATE_FILL;
	PORTD &= ~(LED_STATE_RINSE | LED_STATE_SPIN);
    // Output
	PORTA |= LED_STATE_WASH;

    // Selección de carga baja
	if (load == 1){
		diferential_time_value = 3;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga media
	else if (load == 2){
		diferential_time_value = 5;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga pesada

	else if (load == 3){
		diferential_time_value = 7; // TODO: No se pudo usar los dos displays al mismo tiempo
		COUNTDOWN_TIMER(diferential_time_value);
	}

	return diferential_time_value;
}

uint8_t RINSE(uint8_t load)
{	
    // Input
    PORTB &= ~LED_STATE_FILL;
	PORTA &= ~LED_STATE_WASH;
	PORTD &= ~LED_STATE_SPIN;
    // Output
    PORTD |= LED_STATE_RINSE;
	
    // Selección de carga baja
	if (load == 1){
		diferential_time_value = 2;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga media
	else if (load == 2){
		diferential_time_value = 4;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga pesada
	else if (load == 3){
		diferential_time_value = 5;
		COUNTDOWN_TIMER(diferential_time_value);
	}

	return diferential_time_value;
}

uint8_t SPIN(uint8_t load)
{
    // Input	
	PORTB &= ~LED_STATE_FILL; 
	PORTA &= ~LED_STATE_WASH;
    PORTD &= ~LED_STATE_RINSE;
    // Output
    PORTD |= LED_STATE_SPIN;

    // Selección de carga baja
	if (load == 1){
		diferential_time_value = 3;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga media
	else if (load == 2){
		diferential_time_value = 5;
		COUNTDOWN_TIMER(diferential_time_value);
	}
    // Selección de carga pesada
	else if (load == 3){
		diferential_time_value = 6;
		COUNTDOWN_TIMER(diferential_time_value);
	}

	return diferential_time_value;
}

void FINAL(uint8_t load)
{	
	// Como final se ponen todas las leds de los estados de lavado en alto 
	PORTB |= LED_STATE_FILL;
	PORTA |= LED_STATE_WASH;
    PORTD |= (LED_STATE_RINSE | LED_STATE_SPIN);
	// Reinicio de TIMER
	diferential_time_value = 0; 
	COUNTDOWN_TIMER(diferential_time_value);
	SET_TIMER(diferential_time_value);

}

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

//////// INTERRUPCIONES ////////

// RESET
ISR(INT1_vect) 
{
	if(PIND & RESET_BUTTON){
		state = STATE_IDE;
		PORTB &= ~LED_STATE_FILL;
		PORTA &= ~LED_STATE_WASH;
		PORTD &= ~LED_STATE_RINSE;
		PORTD &= ~LED_STATE_SPIN;
		// Reinicio de TIMER
		diferential_time_value = 0; 
		COUNTDOWN_TIMER( diferential_time_value);
		SET_TIMER(diferential_time_value);
	}
	else {
		state = STATE_IDE;
		PORTB |= ~LED_STATE_FILL;
		PORTA |= ~LED_STATE_WASH;
		PORTD |= ~LED_STATE_RINSE;
		PORTD |= ~LED_STATE_SPIN;
		// Reinicio de TIMER
		diferential_time_value = 0; 
		COUNTDOWN_TIMER( diferential_time_value);
		SET_TIMER(diferential_time_value);		
	}
}

// START/PAUSE
ISR(INT0_vect) 
{
	if(PIND & START_PAUSE_BUTTON){
		//Cuando el timer esta activado se detiene
		if (TIMSK & (1<<TOIE0)){
			TIMSK &= ~(1<<TOIE0);
			PORTB &= ~LED_START_PAUSE;
		}
		//Si esta detenido lo iniciamos
		else{
			TIMSK |= (1<<TOIE0);
			PORTB |= LED_START_PAUSE;
		}
	}
}

// LOW 
ISR(PCINT1_vect)
{
	if(PIND & LOW_LOAD_BUTTON){
		load = 1;
		PORTA |= LED_LOW_LOAD;
	}
	else {
		PORTA &= ~LED_LOW_LOAD;
	}

}

// MEDIUM
ISR(PCINT0_vect) 
{
	if(PIND & MEDIUM_LOAD_BUTTON){
		load = 2;
		PORTB |= LED_MEDIUM_LOAD;
	}
	else {
		PORTB &= ~LED_MEDIUM_LOAD;
	}

}

//HIGH
ISR(PCINT2_vect) 
{
	if(PINA & HIGH_LOAD_BUTTON){
		load = 3;
		PORTD |= LED_HIGH_LOAD;
	}
	else {
		PORTD &= ~LED_HIGH_LOAD;
	}
}

ISR(TIMER0_COMPA_vect) {
  // Aqui va la rutina de interrupcion
  // Hacer LED display cada vez que se produzca la interrupción
	static uint8_t contador = 0;
	contador++;
	 
	// Se configuró el timer0 con un prescales de 64 y reloj de 1 MHz
	// Se ocupan 15625 ciclos del timer para que pase un segundo
	if(contador == 15625){
		time++;
		time_left--;
		//led_display();
	}
	else if(time == diferential_time_value){
		//led_display(0,0);
		TCNT0 = 0;
		TIMSK &= ~(1<<TOIE0);
	}
	contador = 0;
	time = 0;
	time_left = 0;
}

