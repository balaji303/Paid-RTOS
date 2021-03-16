#ifndef PAID_H
#define PAID_H

/*Thread Control Block*/
typedef struct{
	void *sp; /*Stack Pointer*/
}OSThread;

typedef void (*OSThreadHandler)();

void OSThread_start(
	OSThread *me,
	OSThreadHandler threadHandler,
	void *stkSto,
	uint32_t stkSize
);
	
#endif /*PAID_H*/
	