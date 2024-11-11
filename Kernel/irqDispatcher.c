// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <time.h>
#include <stdint.h>
#include <defs.h>

void timer_handler(void);
void kb_update_buffer(void);

static void timer_tick_handler(void);
static void kb_handler(void);

static void (*irq_handlers[])(void) = {
	timer_tick_handler,
	kb_handler
};

static int handlers_size = sizeof(irq_handlers)/sizeof(irq_handlers[0]);

void irq_dispatcher(uint64_t irq) {
	if(irq >= 0 && irq < handlers_size && irq_handlers[irq] != NULL) {
		irq_handlers[irq]();
	}
	return;
}

void kb_handler(){
	kb_update_buffer();
}

void timer_tick_handler() {
	timer_handler();
}