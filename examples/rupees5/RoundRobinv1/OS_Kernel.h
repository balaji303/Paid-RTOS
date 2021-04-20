#ifndef _OS_KERNEL_H
#define _OS_KERNEL_H

#include "stm32f4xx.h"                  // Device header

#include <stdint.h>

void OsKernelLaunch(uint32_t QuantaSize);

void OsKernelInit(void);

uint8_t OsKernelAddThread( void (*task0)(void),
													 void (*task1)(void),
													 void (*task2)(void) );

#endif
