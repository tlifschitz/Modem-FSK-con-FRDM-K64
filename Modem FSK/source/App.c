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
//#include "DAC.h"
//#include "PDB.h"
#include "math.h"
#include "SysTick.h"
#include "GPIO.h"
#include "DMAMUX.h"
#include "DMA.h"
#include "PIT.h"
/////////////////////////////////////////////////////////////////////////////////
//                       Constants and macro definitions                       //
/////////////////////////////////////////////////////////////////////////////////

#define SINE_FREQ (1100)
#define N_SAMPLE (256)

#define DAC_BUFFER_SIZE (1)
#define DAC_WATERMARK (2)
/////////////////////////////////////////////////////////////////////////////////
//                    Enumerations, structures and typedefs                    //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                         Global variables definition                         //
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//                   Local variable definitions ('static')                     //
/////////////////////////////////////////////////////////////////////////////////

static uint16_t signal[N_SAMPLE];

/////////////////////////////////////////////////////////////////////////////////
//                   Local function prototypes ('static')                      //
/////////////////////////////////////////////////////////////////////////////////

void DAC0_IRQHandler()
{
	//digitalToggle(PORTNUM2PIN(PC,10));

	static uint8_t index = 0;

	//DAC_WriteValue(DAC_0,signal[index++]);

	/*if(DAC_GetFlag(DAC_0,DAC_INTERRUPT_POINTER_TOP)==true)
	{
		for(int n=DAC_BUFFER_SIZE-DAC_WATERMARK-1;n<DAC_BUFFER_SIZE; n++)
			DAC_SetBufferValue (DAC_0, n, signal[index+n]);

		index = (index + DAC_BUFFER_SIZE)%N_SAMPLE;

		DAC_ClearFlag(DAC_0,DAC_INTERRUPT_POINTER_TOP);
	}
	else if(DAC_GetFlag(DAC_0,DAC_INTERRUPT_WATERMARK)==true)
	{
		for(int n=0;n<DAC_BUFFER_SIZE-DAC_WATERMARK-1; n++)
				DAC_SetBufferValue (DAC_0, n, signal[index+n]);

		DAC_ClearFlag(DAC_0,DAC_INTERRUPT_WATERMARK);
	}
	digitalToggle(PORTNUM2PIN(PC,10));*/

	/*for(int n=0;n<DAC_BUFFER_SIZE; n++)
		DAC_SetBufferValue (DAC_0, n, signal[index+n]);

	index = (index + DAC_BUFFER_SIZE)%N_SAMPLE;

	// Reset pointer
	//DAC_SetBufferPointer (DAC_0,0);

	DAC_ClearFlag(DAC_0,DAC_INTERRUPT_POINTER_TOP);*/


}

/////////////////////////////////////////////////////////////////////////////////
//                         Global function prototypes                          //
/////////////////////////////////////////////////////////////////////////////////


void App_Init (void)
{
	// Fill table with samples
	for(int i=0; i<N_SAMPLE; i++)
		signal[i]=sin((float)i/N_SAMPLE*2*M_PI)*2048+2047;


	DMAMUX_Init();
	DMAMUX_SetSource(0,PORTA);
	DMAMUX_EnableChannel(0);


	DMA_Config DMAconfig;
	DMA_GetDefaultConfig(&DMAconfig);
	DMA_Init(&DMAconfig);

	uint8_t srcARR[] = {1,2,3,4,5};
	uint8_t destARR[] = {1,2,3,4,5};

	DMA_TransferConfig DMATransfer;
	DMATransfer.sourceAddress = (uint32_t)srcARR;
	DMATransfer.destinationAddress = (uint32_t)destARR;
	DMATransfer.destinationOffset = 1;
	DMATransfer.sourceOffset = 1;
	DMATransfer.destinationTransferSize = DMA_TransferSize1Bytes;
	DMATransfer.sourceTransferSize = DMA_TransferSize1Bytes;
	DMATransfer.majorLoopCounts = 5;
	DMATransfer.minorLoopBytes = 1;

	DMA_SetTransferConfig(0,&DMATransfer);

	PIT_Config PITConfig;
	PIT_GetDefaultConfig(&PITConfig);
	PIT_Init(&PITConfig);
	PIT_SetTimerPeriod (PIT_CHNL_0, 0xFFFFFF);
	PIT_TimerIntrruptEnable(PIT_CHNL_0, true);
	PIT_TimerEnable(PIT_CHNL_0, true);


	/*
	// Configure PDB module
	PDB_Config PDBconfig;
	PDBconfig.enableContinuousMode = true;
	PDBconfig.loadValueMode = PDB_ON_COUNTER_OVERFLOW;
	PDBconfig.multiplicationFactor = PDB_MULT_FACTOR_1;
	PDBconfig.prescalerDivider = PDB_PRESCALER_DIVIDER_64;
	PDBconfig.triggerInputSource = PDB_TRIGGER_SOFTWARE;
	PDB_Init(&PDBconfig);
	PDB_SetModulusValue((int)(50000000.0/(N_SAMPLE*SINE_FREQ)));
	PDB_SetDacTriggerPeriod(355);
	PDB_EnableDacTriger(true);


	// Configure DAC buffer
	DAC_Init(DAC_0,DAC_VREF_2);

	DAC_BufferConfig DACBufferConfig;
	DACBufferConfig.triggerMode = DAC_HARDWARE_TRIGGER;
	DACBufferConfig.upperLimit = DAC_BUFFER_SIZE-1;
	DACBufferConfig.watermark = DAC_WATERMARK_2_WORD;
	DACBufferConfig.workMode = DAC_MODE_NORMAL;//DAC_MODE_ONE_TIME;
	//DAC_SetBufferConfig(DAC_0,&DACBufferConfig);

	DAC_EnableInterrupts(DAC_0,DAC_INTERRUPT_POINTER_TOP);

	pinMode(PIN_SW2,INPUT);
	pinMode(PORTNUM2PIN(PC,10),OUTPUT);
*/

	/*FTM_Config config;
	config.clockSource = FTM_SYSTEM_CLOCK;
	config.prescale = FTM_PRESCALE_4;
	FTM_Init(FTM_0,&config);


	FTM_PwmConfig PWMConfig;
	PWMConfig.channel = FTM_CHNL_0;
	PWMConfig.mode = FTM_PWM_EDGE_ALIGNED;
	PWMConfig.PWMFreq = 1000;

	FTM_SetupPwm(FTM_0,&PWMConfig);

	PORTC->PCR[1] =  PORT_PCR_MUX(4); //PTC1  Alt4 FTM0_CH0


	FTM_EnableOverflowInterrupt(FTM_0);*/

}


void App_Run (void)
{
	PDB_Trigger();
	while(1);
	//DAC_TriggerBuffer(DAC_0);
	//uint16_t n= 0x00F;
	//while(n--);
	/*static uint64_t debounceTime;
	static uint8_t currState, lastState;

	currState = digitalRead(PIN_SW2);

	if(currState!=lastState)
	{
		lastState = currState;
		debounceTime = millis();
	}
	else if (lastState == 1 && (millis() - debounceTime) > 25)
	{
		lastState=0;

		uint8_t pointe = DAC_GetBufferPointer(DAC_0);
	}*/


}

