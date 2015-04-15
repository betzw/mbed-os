/**
 ******************************************************************************
 * @file    main.cpp
 * @author  AST / EST
 * @version V0.0.1
 * @date    14-April-2015
 * @brief   Example application for using the X_NUCLEO_IKS01A1 
 *          MEMS Inertial & Environmental Nucleo expansion board.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
*/ 

/**
 * @mainpage X_NUCLEO_IKS01A1 MEMS Inertial & Environmental Nucleo Expansion Board firmware package
 *
 * <b>Introduction</b>
 *
 * This firmware package includes Components Device Drivers, Board Support Package
 * and example application for STMicroelectronics X_NUCLEO_IKS01A1 MEMS Inertial & Environmental Nucleo
 * Expansion Board
 * 
 * <b>Example Application</b>
 *
 */


/*** Includes ----------------------------------------------------------------- ***/
#include "mbed.h"
#include "x_nucleo_iks01a1.h"

#include <Ticker.h>


/*** Constants ---------------------------------------------------------------- ***/
namespace {
	const int MS_INTERVALS = 1000;
}


/*** Macros ------------------------------------------------------------------- ***/
#define APP_LOOP_PERIOD 1000 // in ms

#if defined(TARGET_K64F)
#define USER_BUTTON (SW2)
#elif defined(TARGET_LPC11U68)
#define USER_BUTTON (P0_16)
#endif // !TARGET_MCU_K64F


/*** Typedefs ----------------------------------------------------------------- ***/
typedef struct {
    int32_t AXIS_X;
    int32_t AXIS_Y;
    int32_t AXIS_Z;
} AxesRaw_TypeDef;


/*** Static variables --------------------------------------------------------- ***/
#ifdef DBG_MCU
/* betzw: enable debugging while using sleep modes */
#include "DbgMCU.h"
static DbgMCU enable_dbg;
#endif // DBG_MCU

static X_NUCLEO_IKS01A1 *mems_expansion_board = X_NUCLEO_IKS01A1::Instance();

static Ticker ticker;
static InterruptIn button(USER_BUTTON);

static volatile bool timer_irq_triggered = false;
static volatile bool button_irq_triggered = false;

static DigitalOut myled(LED1);

/*** Helper Functions (1/2) ------------------------------------------------------------ ***/


/*** Interrupt Handler Top-Halves ------------------------------------------------------ ***/
/* Called in interrupt context, therefore just set a trigger variable */
static void timer_irq(void) {
	timer_irq_triggered = true;
}

/* Called in interrupt context, therefore just set a trigger variable */
static void button_irq(void) {
	button_irq_triggered = true;
	button.disable_irq();
}


/*** Interrupt Handler Bottom-Halves ------------------------------------------------- ***/
/* Handle button irq
   (here we are in "normal" context, i.e. not in IRQ context)
*/
static void handle_button_irq(void) {
	/* TODO */

	/* Re-enable button irq */
	button.enable_irq();
}


/*** Helper Functions (2/2) ------------------------------------------------------------ ***/
/* Initialization function */
static void init(void) {
	uint8_t hts221_id;

	/* Set mode & irq handler for button */
	button.mode(PullNone);
	button.fall(button_irq);

	/* Determine ID of Humidity & Tempreture Sensor */
	mems_expansion_board->ht_sensor.ReadID(&hts221_id);
    	printf("HTS221_ID = 0x%x\n\t\r", hts221_id);
}

/* Main cycle function */
static void main_cycle(void) {
	float TEMPERATURE_Value;
	float HUMIDITY_Value;
	float PRESSURE_Value;
	AxesRaw_TypeDef MAG_Value;
	AxesRaw_TypeDef ACC_Value;
	AxesRaw_TypeDef GYR_Value;
	
	/* Switch LED On */
	myled = 1;

	/* Determine Environmental Values */
        mems_expansion_board->ht_sensor.GetTemperature(&TEMPERATURE_Value);
        mems_expansion_board->ht_sensor.GetHumidity(&HUMIDITY_Value);
        mems_expansion_board->pressure_sensor.GetPressure(&PRESSURE_Value);
        mems_expansion_board->magnetometer.Get_M_Axes((int32_t *)&MAG_Value);
        mems_expansion_board->gyroscope.Get_X_Axes((int32_t *)&ACC_Value);
        mems_expansion_board->gyroscope.Get_G_Axes((int32_t *)&GYR_Value);

	/* Print Values Out */
        printf("TEMP: %f HUMIDITY: %f PRESSURE: %f\t\r\n ", 
	       TEMPERATURE_Value, HUMIDITY_Value, PRESSURE_Value);
        printf("X_AXIS: %ld, Y_AXIS: %ld, Z_AXIS: %ld\t\r\n ", 
	       MAG_Value.AXIS_X, MAG_Value.AXIS_Y, MAG_Value.AXIS_Z);
        printf("X_ACC: %ld, Y_ACC: %ld, Z_ACC: %ld\t\r\n ", 
	       ACC_Value.AXIS_X, ACC_Value.AXIS_Y, ACC_Value.AXIS_Z);
        printf("X_GYR: %ld, Y_GYR: %ld, Z_GYR: %ld\t\r\n ", 
	       GYR_Value.AXIS_X, GYR_Value.AXIS_Y, GYR_Value.AXIS_Z);
	
	/* Switch LED Off */
	myled = 0;
}


/*** Main function ------------------------------------------------------------- ***/
/* Generic main function/loop for enabling WFI in case of 
   interrupt based cyclic execution
*/
int main()
{
	/* Start & initialize */
	printf("\n--- Starting new run ---\n");
	init();

	/* Start timer irq */
	ticker.attach_us(timer_irq, MS_INTERVALS * APP_LOOP_PERIOD);

	while (true) {
		__disable_irq();
		if(timer_irq_triggered) {
			timer_irq_triggered = false;
			__enable_irq();
			main_cycle();
		} else if(button_irq_triggered) {
			button_irq_triggered = false;
			__enable_irq();
			handle_button_irq();
		} else {
			__WFI();
			__enable_irq(); /* do NOT enable irqs before WFI to avoid 
					   opening a window in which you can loose
					   irq arrivals before going into WFI */
		}
	}
}
