// Laboratorio 4: Daniel Chacón Mora (B72018)-Erick Sancho

/////////////////////////
// Librerías utilizadas//
/////////////////////////

// Para poder implementar funciones de SMT32F429 es necesario importar librerías de repositorio.
// Link de repo para más librerías e información.
#include "gfx.h"                    //	Control de interax gráfica
#include "console.h"                // Control de funciones comunicación con consola de SMT32F429
#include "lcd-spi.h"                // Control de LCD através de SPI BUS
#include <libopencm3/stm32/adc.h>   //	Control de convertidor analog-digital
#include <libopencm3/stm32/gpio.h>  //	Control de pines de GPIO
#include <libopencm3/stm32/rcc.h>   //	Control de reloj
#include <libopencm3/stm32/usart.h> //	Control de comunicación serial
#include <libopencm3/stm32/spi.h>   //	Control de SPI BUS
#include <stdio.h>                  // IO estandar
#include "clock.h"                  // Control de funciones de reloj de SMT32F429
#include "sdram.h"                  //	Control de SDRAM

//////////////////////////////////////
//	Definición de registros L3GD20. //
//////////////////////////////////////

// Se hace uso de recursos disponibles en repositorio.
// Configuración de registros de SPI se implementa:
// 	1. spi-mems.c encontrado en libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/spi
//	2. spi.c encontrado en libopencm3-examples/examples/stm32/f3/stm32f3-discovery/spi
//  Configuración de registros USART1 se implementa
//  1. usart_irq.c encontrado en libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/usart_irq

//////////////////
// Ejes X, Y, Z	//
//////////////////
//	X
#define GYR_OUT_X_L 0x28
#define GYR_OUT_X_H 0x29
//	Y
#define GYR_OUT_Y_L 0x2A
#define GYR_OUT_Y_H 0x2B
//	Z
#define GYR_OUT_Z_L 0x2C
#define GYR_OUT_Z_H 0x2D
// Definición de registros
#define GYR_RNW (1 << 7) /* Escribe cuando es 0*/
#define GYR_MNS (1 << 6) /* Multiples lecturas cuando es 1 */
#define GYR_WHO_AM_I 0x0F
#define GYR_OUT_TEMP 0x26
#define GYR_STATUS_REG 0x27
#define GYR_CTRL_REG1 0x20
#define GYR_CTRL_REG1_PD (1 << 3)
#define GYR_CTRL_REG1_XEN (1 << 1)
#define GYR_CTRL_REG1_YEN (1 << 0)
#define GYR_CTRL_REG1_ZEN (1 << 2)
#define GYR_CTRL_REG1_BW_SHIFT 4
#define GYR_CTRL_REG4 0x23
#define GYR_CTRL_REG4_FS_SHIFT 4

// Definición de atributos del objeto
typedef struct GYRO
{
  int16_t X;
  int16_t Y;
  int16_t Z;
} GYRO;

// Declaración de variables
static void usart_setup(void);

// Funciones

// USART Setup
static void usart_setup(void)
{
  /* Configuración de pines para USAR.*/
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO9);

  /* Se configura GPP para funciones de USART. */
  gpio_set_af(GPIOA, GPIO_AF7, GPIO9);

  ////////////////////////////
  // Configuración de USART1//
  ////////////////////////////
  //  Velocidad de transmisión de datos 115200 bits por segunda
  usart_set_baudrate(USART1, 115200);
  //  Número de bits de datos en cada trama a 8 bits.
  usart_set_databits(USART1, 8);
  //  Un solo bit de parada para cada trama de datos
  usart_set_stopbits(USART1, USART_STOPBITS_1);
  //  Modo USART1 solo de Tx para envío de datos
  usart_set_mode(USART1, USART_MODE_TX);
  //  No se utilizará ningún bit de paridad en las tramas de datos.
  usart_set_parity(USART1, USART_PARITY_NONE);
  //  No se controla la velocidad de transmisión de datos entre el microcontrolador y el dispositivo conectado.
  usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
  //  Se habilita la USART1
  usart_enable(USART1);
}
