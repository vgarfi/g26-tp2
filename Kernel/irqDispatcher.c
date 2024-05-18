#include <time.h>
#include <stdint.h>
#include <naiveConsole.h>
#include <defs.h>

static void timer_tick_handler();
static void kb_handler();

static uint64_t (*irqHandlers[])(void)={
	timer_tick_handler,
	kb_handler
};

static int handlersSize = sizeof(irqHandlers)/sizeof(irqHandlers[0]);


void irqDispatcher(uint64_t irq) {
	if(irq >=0 && irq < handlersSize && irqHandlers[irq]!=NULL)
		irqHandlers[irq]();
	return;
}

void kb_handler(){
	// TODO: Handling para recepcion de teclas
}

void timer_tick_handler() {
	timer_handler();
}