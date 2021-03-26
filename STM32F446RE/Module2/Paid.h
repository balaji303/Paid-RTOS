#ifndef PAID_H
#define PAID_H

/*Thread Control Block*/
typedef struct{
	void *sp; /*Stack Pointer*/
}OSThread;

typedef void (*OSThreadHandler)();

void OS_init(void);

void OS_sched(void);

void OSThread_start(
	OSThread *me, /*Pointer to TCB*/
	OSThreadHandler threadHandler, /*Pointer to Thread Handler*/
	void *stkSto, /*Thread Start Function*/
	uint32_t stkSize /*Size of the Stack*/
);
  
	
#endif /*PAID_H*/
  	