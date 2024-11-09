#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include <idtLoader.h>

/**
 * @brief IRQ handler for interrupt 0.
 */
void _irq00Handler(void);

/**
 * @brief IRQ handler for interrupt 1.
 */
void _irq01Handler(void);

/**
 * @brief IRQ handler for interrupt 2.
 */
void _irq02Handler(void);

/**
 * @brief IRQ handler for interrupt 3.
 */
void _irq03Handler(void);

/**
 * @brief IRQ handler for interrupt 4.
 */
void _irq04Handler(void);

/**
 * @brief IRQ handler for interrupt 5.
 */
void _irq05Handler(void);

/**
 * @brief Exception handler for exception 0.
 */
void _exception0Handler(void);

/**
 * @brief Exception handler for exception 6.
 */
void _exception6Handler(void);

/**
 * @brief System call handler.
 */
void _syscallHandler(void);

/**
 * @brief Clears the interrupt flag (disables interrupts).
 */
void _cli(void);

/**
 * @brief Sets the interrupt flag (enables interrupts).
 */
void _sti(void);

/**
 * @brief Halts the CPU.
 */
void _hlt(void);

/**
 * @brief Sets the mask for the master PIC.
 *
 * @param mask The mask to set.
 */
void pic_master_mask(uint8_t mask);

/**
 * @brief Sets the mask for the slave PIC.
 *
 * @param mask The mask to set.
 */
void pic_slave_mask(uint8_t mask);

/**
 * @brief Ends CPU execution.
 */
void halt_cpu(void);

/**
 * @brief Requests a schedule.
 */
void request_schedule(void);

#endif /* INTERRUPS_H_ */