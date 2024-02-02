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
// 	1.  spi-mems.c encontrado en libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/spi
//	2.  spi.c encontrado en libopencm3-examples/examples/stm32/f3/stm32f3-discovery/spi
//  Configuración de registros USART1 se implementa
//  1.  usart_irq.c encontrado en libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/usart_irq
//  Configuración de registros para ADC se implementa:
//  1.  libopencm3-examples/examples/stm32/f4/stm32f429i-discovery/adc-dac-printf/adc-dac-printf.c
//  2.  libopencm3-examples/examples/stm32/f3/stm32f3-discovery/adc/adc.c

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

// Declaración de funciones
static void usart_setup(void);
static void spi_setup(void);
void input_setup(void);
static void adc_setup(void);
static uint16_t read_adc_naiive(uint8_t channel);

/////////
// Main//
/////////
int main(void)
{

  // Inicialización de funciones
  input_setup();
  usart_setup();
  spi_setup();
  adc_setup();
}

//////////////
// Funciones//
//////////////

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

// SPI Setup
static void spi_setup(void)
{
  /////////////////////////////
  //  Configuraciones de GPIO//
  /////////////////////////////

  //  Configura GPIO7, GPIO8 y GPIO9 en el puerto GPIOF como salidas.
  gpio_mode_setup(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE,
                  GPIO7 | GPIO8 | GPIO9);
  //  Se configuran en su alternate function.
  gpio_set_af(GPIOF, GPIO_AF5, GPIO7 | GPIO8 | GPIO9);

  //  Pin GPIO1 en el puerto GPIOC como una salida en modo push-pull sin PU/PD.
  gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
  gpio_set(GPIOC, GPIO1);

  //  Habilitación de clk para pin de SPI
  rcc_periph_clock_enable(RCC_SPI5);
  //  Habilitación de clk para GPP
  rcc_periph_clock_enable(RCC_GPIOC);
  rcc_periph_clock_enable(RCC_GPIOF);

  //////////////////////
  // SPI configuration//
  //////////////////////
  //  Se define SPI5 como maestro.
  spi_set_master_mode(SPI5);
  //  Velocidad de transmisión de periférico es dividida por preescaler (64).
  spi_set_baudrate_prescaler(SPI5, SPI_CR1_BR_FPCLK_DIV_64);
  //  Nivel de tensión es 0 cuando no se usa.
  spi_set_clock_polarity_0(SPI5);
  //  Los datos se muestrean en el inicio del ciclo de reloj.
  spi_set_clock_phase_0(SPI5);
  //  Se habilita trasmisión y recepción simultánea
  spi_set_full_duplex_mode(SPI5);
  //  En SPI se tienen MISO y MOSI para permitir señal bidireccional.
  spi_set_unidirectional_mode(SPI5); /* bidirectional but in 3-wire */
  //  Se selecciona el slave por medio de software.
  spi_enable_software_slave_management(SPI5);
  //  Se envía primero bits más significativos.
  spi_send_msb_first(SPI5);
  //  Señal en alto cuando no se está transmitiendo.
  spi_set_nss_high(SPI5);

  //  Como SPI5 se utiliza para SPI, se deshabilita modo I2S
  SPI_I2SCFGR(SPI5) &= ~SPI_I2SCFGR_I2SMOD;
  // Se habilita SPI5 para transmisión y recepción de datos.
  spi_enable(SPI5);
  //  Limpia señales en GPIO
  gpio_clear(GPIOC, GPIO1);
  //  Se envía comando para leer registor de control
  spi_send(SPI5, GYR_CTRL_REG1);
  //  Lee respuesat del registro de control
  spi_read(SPI5);
  //  Se envía señal de enable a registros de giroscopio
  spi_send(SPI5, GYR_CTRL_REG1_PD | GYR_CTRL_REG1_XEN |
                     GYR_CTRL_REG1_YEN | GYR_CTRL_REG1_ZEN |
                     (3 << GYR_CTRL_REG1_BW_SHIFT));
  //  Se leen datos en SPI5 del giroscopio
  spi_read(SPI5);
  //  Se configuira GPIO1 en alto
  gpio_set(GPIOC, GPIO1);
  //  Se limpia registro
  gpio_clear(GPIOC, GPIO1);
  //  Se envía información de registro de control de giroscopio
  spi_send(SPI5, GYR_CTRL_REG4);
  //  Se lee pin
  spi_read(SPI5);
  //  Se genera número donde solo el bit indicado por señal de giroscopio está en alto
  //  y se envía dato a SPI5
  spi_send(SPI5, (1 << GYR_CTRL_REG4_FS_SHIFT));
  //  Se lee el dato en SPI5
  spi_read(SPI5);
  //  Se configuira GPIO1 en alto
  gpio_set(GPIOC, GPIO1);
}
//  Input setup
void input_setup(void)
{

  //  Se habilita pin como entrada open drain para conectar varios dispositivos
  gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);

  //  Se habilita pin para suministrar alta o baja corriente a pines de LEDs.
  gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
  gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO14);

  //  Reloj se habilita para pin GPP digital
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOG);

  //  Se habilita clk para convertidor analog-digital
  rcc_periph_clock_enable(RCC_ADC1);
  //  Se habilita en reloj para módulo USART1
  rcc_periph_clock_enable(RCC_USART1);
}
// ADC Setup
static void adc_setup(void)
{

  //  Pines de entrada analógica(podría ser batería)
  gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO2);
  //  Se apaga módulo ADC1
  adc_power_off(ADC1);
  adc_disable_scan_mode(ADC1);
  // Tiempo de muestreo es cada 3 ciclos de reloj
  adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_3CYC);
  //  Se enciende modo
  adc_power_on(ADC1);
}

static uint16_t read_adc_naiive(uint8_t channel)
{

  // Array para almacenar información de canal
  uint8_t channel_array[1];
  channel_array[0] = channel;
  // Se inicia secuencia regular con canal especificado
  adc_set_regular_sequence(ADC1, 1, channel_array);
  // Conversión
  adc_start_conversion_regular(ADC1);
  // Se espera a que conversión termine
  while (!adc_eoc(ADC1))
    ;
  // Lee conversión
  uint16_t reg16 = adc_read_regular(ADC1);
  return reg16;
}

//____________________________________________________
