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
	BX         LR        ;All registers r0,r1,r2,r3,r12,LR,PC,xPSR register are restored by the processor
	
	
	
	
	
	;**************
	;LDR        R0,=currentPt  ;R1 = currentPtr->StackPtr
    ;STR SP,[R1]       ;SP store to  currentPtr->StackPtr
    ;LDR R1,[R1,#4]    ;R1=currentPtr->nextPtr
    ;STR R1,[R0]       ;currentPtr->nextPtr store to currentPtr
    ;LDR SP,[R1]       ;currentPtr->StackPtr store to SP
    ;POP {R4 - R11}      ;currentPtr->StackPtr storerage to R4-R11
	;**************
	; On Each SysTick_Handler save the current thread and load the next thread:
; --------------------------------------
; 1. save stack to thread (currentPtr->stackPtr)
; 2. switch to the new thread (currentPtr = currentPtr->nextPtr)
; 3. load stack from next thread for switch (SP = currentPtr->stackPtr)
 
;SysTick_Handler               ; Automatically Saves r0, r1, r2, r3, r12, lr, pc, psr to stack
	
;    CPSID    I		       ; disable interrupts
;    PUSH    {R4-R11}	       ; save r4, r5, r6, r7, r8, r9, r10, r11 to stack
 
                                                                        ;     C-Equivalent
                                                                        ;     --------------
;    LDR    R0, =currentPtr   ; Assign r0 to point to currentPtr        ::     R0 = &currentPtr
;    LDR    R1, [R0]          ; Load the value of R1 with R0. 	        ::     R1 = currentPtr
;    STR    SP, [R1]          ; Stores stack pointer into R1.	        ::     currentPtr->StackPtr = SP
;    LDR    R1, [R1, 4]       ; Load R1 with the value of R1+4	        ::     R1 = currentPtr->nextPtr
;    STR    R1, [R0]	      ; store R1 in R0. points to next thread   ::     currentPtr = R1 = currentPtr->nextPtr
;    LDR    SP, [R1]	      ; loads SP with R1. 			::     SP = currentPtr->stackPtr
	
;    POP    {R4-R11}	      ; restore r4, r5, r6, r7, r8, r9, r10, r11 from new stack
	
;    CPSIE  I		      ; enable interrupts
	
;    BX	   LR		      ; return from subroutine. Automatically restores r0, r1, r2, r3, r12, lr, pc, psr from new stack



OsSchedulerLaunch         ;SP to the value of 1st thread
	CPSID      I         ;Disable Interrupt
	LDR    R0,=currentPt
	LDR    R2,[R0]      ;R2=currentPt
	LDR    SP,[R2]      ;SP=currentPt->StackPt
	POP    {R4-R11}
	POP    {R0-R3}
	POP    {R12}
	ADD    SP,SP,#4     ;Get rid of LR register
	POP    {LR}
	ADD    SP,SP,#4     ;Get rid of PSR register
	CPSIE  I
	BX     LR
	
	
	ALIGN
	END
	
