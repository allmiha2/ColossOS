#ifndef IO_H  // If PIC_H is NOT defined
#define IO_H   // Define PIC_H

#include<stdint.h>

static inline void outb(uint16_t port, uint8_t value);
static inline uint8_t inb(uint16_t port);
static inline void io_wait(void);

#endif        // End the conditional