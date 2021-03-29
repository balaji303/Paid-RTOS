#include <stdint.h>
#include "paid.h"
#include "bsp.h"

/*Points to the current thread*/
OSThread * volatile OS_curr;

/*Points to the next thread*/
OSThread * volatile OS_next;

/*
* Trigger the Pendsv exception but only when
* Next thread is not equal to the 
* current thread
*/
void OS_sched(void){
	/*Automatic scheduling but only works for two
	functions
	*/
	extern OSThread blinky1;
	extern OSThread blinky2;
	
	if(OS_curr == &blinky1){
		OS_next = &blinky2;
	}
	else{
		OS_next = &blinky1;
	}
	
	
	if (OS_next!=OS_curr){
		*(uint32_t volatile*)0xE000ED04 = (1U << 28); 	
	}
}

void OS_init(void){
	*(uint32_t volatile *)0xE000ED20 |= (0xFFU<<16);
}

void OSThread_start(
    OSThread *me,
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize)
{
			uint32_t *sp=(uint32_t *)((((uint32_t)stkSto + stkSize)/8)*8);
			uint32_t *stk_limit;
				
	  *(--sp) = (1U << 24);  /* xPSR */
    *(--sp) = (uint32_t)&threadHandler; /* PC */
    *(--sp) = 0x0000000EU; /* LR  */
    *(--sp) = 0x0000000CU; /* R12 */
    *(--sp) = 0x00000003U; /* R3  */
    *(--sp) = 0x00000002U; /* R2  */
    *(--sp) = 0x00000001U; /* R1  */
    *(--sp) = 0x00000000U; /* R0  */
    /* additionally, fake registers R4-R11 */
    *(--sp) = 0x0000000BU; /* R11 */
    *(--sp) = 0x0000000AU; /* R10 */
    *(--sp) = 0x00000009U; /* R9 */
    *(--sp) = 0x00000008U; /* R8 */
    *(--sp) = 0x00000007U; /* R7 */
    *(--sp) = 0x00000006U; /* R6 */
    *(--sp) = 0x00000005U; /* R5 */
    *(--sp) = 0x00000004U; /* R4 */
	
		me->sp=sp;
		stk_limit= (uint32_t *)(((((uint32_t)stkSto - 1U ) / 8 )+ 1U)* 8);
		for(sp=sp-1U;sp>=stk_limit;--sp)
		{
			*sp=0xDEADBEEFU;
		}
		
 }
 
 /*Context switch inside PendSV*/
__asm 
void PendSV_Handler(void) {
    IMPORT  OS_curr  /* extern variable */
    IMPORT  OS_next  /* extern variable */
   
    /* __disable_irq(); */
    CPSID         I

    /* if (OS_curr != (OSThread *)0) { */ 
    LDR           r1,=OS_curr
    LDR           r1,[r1,#0x00]
    CBZ           r1,PendSV_restore

    /*     push registers r4-r11 on the stack */
    PUSH          {r4-r11}    

    /*     OS_curr->sp = sp; */ 
    LDR           r1,=OS_curr
    LDR           r1,[r1,#0x00]
    STR           sp,[r1,#0x00]
    /* } */

PendSV_restore    
    /* sp = OS_next->sp; */
    LDR           r1,=OS_next
    LDR           r1,[r1,#0x00]
    LDR           sp,[r1,#0x00]

    /* OS_curr = OS_next; */
    LDR           r1,=OS_next
    LDR           r1,[r1,#0x00]
    LDR           r2,=OS_curr
    STR           r1,[r2,#0x00]

    /* pop registers r4-r11 */ 
    POP           {r4-r11}    

    /* __enable_irq(); */
    CPSIE         I

    /* return to the next thread */
    BX            lr    
} 
 