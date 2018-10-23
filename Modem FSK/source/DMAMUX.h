#ifndef DMAMUX_H_
#define DMAMUX_H_
#include "stdint.h"
#include "stdbool.h"

typedef enum{
	DMAMUX_UART0_RX,
	DMAMUX_UART0_TX,
	DMAMUX_UART1_RX,
	DMAMUX_UART1_TX,
	DMAMUX_UART2_RX,
	DMAMUX_UART2_TX,
	DMAMUX_UART3_RX,
	DMAMUX_UART3_TX,
	DMAMUX_UART4_RX_TX,
	DMAMUX_UART5_RX_TX,
	DMAMUX_I2S0_RX,
	DMAMUX_I2S0_TX,
	DMAMUX_SPI0_RX,
	DMAMUX_SPI0_TX,
	DMAMUX_SPI1_RX_TX,
	DMAMUX_SPI2_RX_TX,
	DMAMUX_I2C0,
	DMAMUX_I2C1,
	DMAMUX_FTM0_CH0,
	DMAMUX_FTM0_CH1,
	DMAMUX_FTM0_CH2,
	DMAMUX_FTM0_CH3,
	DMAMUX_FTM0_CH4,
	DMAMUX_FTM0_CH5,
	DMAMUX_FTM0_CH6,
	DMAMUX_FTM0_CH7,
	DMAMUX_FTM1_CH0,
	DMAMUX_FTM1_CH1,
	DMAMUX_FTM2_CH0,
	DMAMUX_FTM2_CH1,
	DMAMUX_FTM3_CH0,
	DMAMUX_FTM3_CH1,
	DMAMUX_FTM3_CH2,
	DMAMUX_FTM3_CH3,
	DMAMUX_FTM3_CH4,
	DMAMUX_FTM3_CH5,
	DMAMUX_FTM3_CH6,
	DMAMUX_FTM3_CH7,
	DMAMUX_ADC0,
	DMAMUX_ADC1,
	DMAMUX_CMP0,
	DMAMUX_CMP1,
	DMAMUX_CMP2,
	DMAMUX_DAC0,
	DMAMUX_DAC1,
	DMAMUX_CMT ,
	DMAMUX_PDB ,
	DMAMUX_PortA,
	DMAMUX_PortB,
	DMAMUX_PortC,
	DMAMUX_PortD,
	DMAMUX_PortE,
	DMAMUX_IEEETimer0,
	DMAMUX_IEEETimer1,
	DMAMUX_IEEETimer2,
	DMAMUX_IEEETimer3,
	DMAMUX_AlwaysEnabled0,
	DMAMUX_AlwaysEnabled1,
	DMAMUX_AlwaysEnabled2,
	DMAMUX_AlwaysEnabled3,
	DMAMUX_AlwaysEnabled4,
	DMAMUX_AlwaysEnabled5
} DMAMUX_Source;


void DMAMUX_Init ();
void DMAMUX_Deinit ();
void DMAMUX_EnableChannel ( uint32_t channel, bool periodicTrigger);
void DMAMUX_DisableChannel (uint32_t channel);
void DMAMUX_SetSource ( uint32_t channel, DMAMUX_Source source);

#endif /* DMAMUX_H_ */