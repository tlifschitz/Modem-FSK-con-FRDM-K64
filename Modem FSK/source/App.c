/////////////////////////////////////////////////////////////////////////////////
//                     				MODEM FSK                              	   //
//          Grupo 3 - Laboratorio de Microprocesadores - ITBA - 2018           //
//	                                                                           //
/////////////////////////////////////////////////////////////////////////////////

/**
 * @file App.c
 * @brief Trabajo Practico N°3.
 */

/////////////////////////////////////////////////////////////////////////////////
//                             Included header files                           //
/////////////////////////////////////////////////////////////////////////////////
#include "CPUTimeMeasurement.h"
#include "Modem.h"
#include "UART.h"

/////////////////////////////////////////////////////////////////////////////////
//                       Constants and macro definitions                       //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                    Enumerations, structures and typedefs                    //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                         Global variables definition                         //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                   Local variable definitions ('static')                     //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                   Local function prototypes ('static')                      //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                         Global function prototypes                          //
/////////////////////////////////////////////////////////////////////////////////

void App_Init (void)
{

#ifdef MEASURE_CPU_TIME
	MEASURE_CPU_TIME_PORT->PCR[MEASURE_CPU_TIME_PIN] = PORT_PCR_MUX(1);
	MEASURE_CPU_TIME_GPIO->PDDR |= (1<<MEASURE_CPU_TIME_PIN);
	MEASURE_CPU_TIME_GPIO->PDOR &= ~(1<<MEASURE_CPU_TIME_PIN);
#endif


	UART_Config UARTconfig;
	UARTconfig.baud = UART_Baud_1200_Bps;
	UARTconfig.enableRx = true;
	UARTconfig.enableTx = true;
	UARTconfig.parityMode = UART_ParityOdd;
	UARTconfig.RxFIFOEnable = true;
	UARTconfig.TxFIFOEnable = true;
	UARTconfig.loopBackEnable = false;
	UART_Init(&UARTconfig);

	MODEM_Init();
}


void App_Run (void)
{
	static uint8_t b;

	MODEM_Demodulate();

	if(UART_ReceiveByte(&b))
	{
		SET_TEST_PIN;
		MODEM_SendByte(b);
		CLEAR_TEST_PIN;
	}

	if(MODEM_ReceiveByte(&b))
	{
		SET_TEST_PIN;
		UART_SendByte(b);
		CLEAR_TEST_PIN;
	}
}


