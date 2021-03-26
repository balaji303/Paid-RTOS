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
	if (OS_next!=OS_curr){
		*(uint32_t volatile*)0xE000ED04 = (1U << 28); 	
	}
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
 
 void PendSV_Handler(void){
	   
 }
 