#include "OS_Kernel.h"

#define QUANTA 10 //This makes each thread runs for 10 milli second

uint32_t count0,count1,count2;

void Task0(void);
void Task1(void);
void Task2(void);

int main(void){
	count0=0;
	count1=0;
	count2=0;
	OsKernelInit();
	OsKernelAddThread(&Task0,&Task1,&Task2);
	OsKernelLaunch(QUANTA);
	return 0;
}

void Task0(void){
	while(1){
		count0++;
	}
}

void Task1(void){
	while(1){
		count1++;
	}	
}

void Task2(void){
	while(1){
		count2++;
	}
}
