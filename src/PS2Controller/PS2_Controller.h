#include <stdint.h>
// ps2 hardware device(s) -> ps2 controller hardware device -> OS

// 1. receive data (or controller) bytes/commands from ps2 devices to be forwarded to the appropriate (OS)
// to be interpreted (or handled by the controller itself if bytes are controller commands) 

// 2. send data to the ps2 devices (from the drivers/OS)

void ps2_controller_init(void);

/*
1. The keyboard sends a scan code to the PS/2 controller.
2. The controller places that scan code in its output buffer.
3. The controller raises IRQ1.
4. The PIC forwards the interrupt to the CPU.
5. Your keyboard interrupt handler executes.
6. The handler reads the scan code using ps2_read_data().
*/
uint8_t ps2_read_data(void);
void ps2_write_data(uint8_t data);