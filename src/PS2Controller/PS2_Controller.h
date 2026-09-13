#include <stdint.h>
// ps2 hardware device(s) -> ps2 controller hardware device -> OS

// 1. receive data (or controller) bytes/commands from ps2 devices to be forwarded to the appropriate (OS)
// to be interpreted (or handled by the controller itself if bytes are controller commands) 

// 2. send data to the ps2 devices (from the drivers/OS)

void ps2_controller_init(void);

uint8_t ps2_read_data(void);
void ps2_write_data(uint8_t data);