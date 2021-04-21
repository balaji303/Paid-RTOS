/*
* Things we need are 
*				1. Scheduler
*				2. TCB or Thread Control Block
*       3. Stack to hold the contents of each Thread 
*/
#include "OS_Kernel.h"

/*Constants*/
#define NUM_OF_THREAD       3
#define STACKSIZE           100
#define BUS_FREQ            16000000
#define SYSPRI3             (*((volatile  uint32_t*)0xE000ED20))


/*Structures*/
struct ThreadControlBlock{
	int32_t *stackPt;
	struct ThreadControlBlock *nextStructPt;
};


/*TypeDef*/
typedef struct ThreadControlBlock tcb_t;

/*Declaration*/
tcb_t tcbs[NUM_OF_THREAD];
tcb_t *currentPt;
void OsSchedulerLaunch(void);

uint32_t MillisPrescaler;
int32_t TcbStack[NUM_OF_THREAD][STACKSIZE];

void OsKernelStackInit(int ThreadNum){
	tcbs[ThreadNum].stackPt= &TcbStack[ThreadNum][STACKSIZE-16];         /*Each thread should point to the  Top of the same thread*/
	TcbStack[ThreadNum][STACKSIZE-1]=0x01000000;                         /*Initialize the ExPSR register to 1 so the processor runs in Thumb mode*/
}

uint8_t OsKernelAddThread( void (*task0)(void),
													 void (*task1)(void) )
{
	__disable_irq();
  tcbs[0].nextStructPt= &tcbs[1];	
  tcbs[1].nextStructPt= &tcbs[0];
	OsKernelStackInit(0);
	TcbStack[0][STACKSIZE-2]= (int32_t)(task0); //Subtracted by two because of location of Program Counter register
	OsKernelStackInit(1);
	TcbStack[1][STACKSIZE-2]= (int32_t)(task1);

	currentPt = &tcbs[0];
	
  __enable_irq();					 
	
	return 1;													 
}

void OsKernelInit(void){
	__disable_irq();
	MillisPrescaler = BUS_FREQ/1000;
	__enable_irq();
}

void OsKernelLaunch(uint32_t QuantaSize){
	SysTick->CTRL =0; //Disable SysTick
	SysTick->VAL  =0;
	SYSPRI3 = (SYSPRI3 & 0x00FFFFFF)|(0XE0000000); //Setting Priority as 7 (lowest)
  SysTick->LOAD =(QuantaSize*MillisPrescaler)-1 ; //Count values or countdown timer, -1 becauses start from zero
	SysTick->CTRL = 0x00000007; //Enable SysTick
	OsSchedulerLaunch();
}

