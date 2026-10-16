#include <stdint.h>
#include "io.h"

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile (
        "outb %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;

    __asm__ volatile (
        "inb %1, %0"
        : "=a"(value)
        : "Nd"(port)
    );

    return value;
}

static inline void io_wait(void)
{
    // Wait a very small amount of time (1 to 4 microseconds, generally).
    // Useful for implementing a small delay for PIC remapping on old hardware or generally as a simple but imprecise wait.
    
    // You can do an IO operation on any unused port: the Linux kernel by default uses port 0x80, which is often used 
    // during POST to log information on the motherboard's hex display but almost always unused after boot.

    outb(0x80, 0);
}