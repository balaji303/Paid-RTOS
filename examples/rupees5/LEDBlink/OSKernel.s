			AREA |.text|, CODE, READONLY, ALIGN=2
			THUMB
			EXTERN currentPt
			EXPORT SysTick_Handler
			EXPORT OsSchedulerLaunch
				
SysTick_Handler          ;Saves r0,r1,r2,r3,r12,link register,Program Counter, PSR
	CPSID      I         ;Disable Interrupt
	PUSH       {R4-R11}  ;Push Register r4 to r11 into Stack
	LDR        R0,=currentPt;We Load the currentPt to R0
	LDR        R1,[R0]   ;Load R0 into R1. CurrentPt point to current running Thread
	STR        SP,[R1]   ;Stack Pointer is equal to CurrentPt
	LDR        R1,[R1,#4];Number  4 takes us to the second entry in thread control block 
	STR        R1,[R0]   ;currentPt= r1
	LDR        SP,[R1]   ;Stack Pointer Points to the Top of the new Stack
	POP        {R4-R11}  ;Restore the  registers that we pushed
	CPSIE      I         ;Enable Interrupt
	BX         LR        ;Return so All registers r0,r1,r2,r3,r12,LR,PC,xPSR register are restored by the processor
	
OsSchedulerLaunch        ;SP to the value of 1st thread
	CPSID      I         ;Disable Interrupt
	LDR    R0,=currentPt
	LDR    R2,[R0]       ;R2=currentPt
	LDR    SP,[R2]       ;SP=currentPt->StackPt
	POP    {R4-R11}
	POP    {R0-R3}
	POP    {R12}
	ADD    SP,SP,#4      ;Get rid of LR register
	POP    {LR} 
	ADD    SP,SP,#4      ;Get rid of PSR register
	CPSIE  I             ;Enable interrupts
	BX     LR            ;Return
	
	
	ALIGN
	END
	
