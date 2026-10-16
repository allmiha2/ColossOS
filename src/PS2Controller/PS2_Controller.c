#include <stdint.h>
#include "io.h"

static bool ps2_output_ready(void)
{
    // Status register bit 0:
    // 1 = output buffer contains data
    return (inb(0x64) & (1 << 0)) != 0;
}

static bool ps2_input_ready(void)
{
    // Status register bit 1:
    // 0 = input buffer empty, controller can accept data
    return (inb(0x64) & (1 << 1)) == 0;
}

static void ps2_wait_for_output(void)
{
    while (!ps2_output_ready())
    {
    }
}

static void ps2_wait_for_input(void)
{
    while (!ps2_input_ready())
    {
    }
}

static void ps2_write_command(uint8_t command)
{
    ps2_wait_for_input();
    outb(0x64, command);
}

static void ps2_write_data(uint8_t data)
{
    ps2_wait_for_input();
    outb(0x60, data);
}

static uint8_t ps2_read_data(void)
{
    // TODO: for interrupts do not wait. you can use the condition in an if instead of while
    // (The PS/2 controller generates IRQ1 because keyboard data has arrived => data already available)
    ps2_wait_for_output();
    return inb(0x60);
}

void ps2_controller_init(void)
{
    // Minimal first-port-only PS/2 controller initialization
    // This skips several of OSDev's full 10 initialization steps

    // Disable first PS/2 port
    ps2_write_command(0xAD);

    // We are not using/detecting a second port yet

    // Flush any byte already sitting in the output buffer (stale)
    if (ps2_output_ready())
    {
        inb(0x60);
    }

    // Read controller configuration byte
    ps2_write_command(0x20);
    uint8_t configByte = ps2_read_data();

    // Bit 0 = first-port IRQ
    // Bit 4 = first-port clock disabled
    // Bit 6 = first-port translation


    // Once your IDT, PIC, and keyboard interrupt handler are ready, you can enable IRQ1 generation in the PS/2 controller, unmask IRQ1 in the PIC, and enable CPU interrupts.

    // Disable IRQ1 and translation
    // and ensure first-port clock is enabled
    configByte &= ~((1 << 0) | (1 << 4) | (1 << 6));

    // Write configuration byte back
    ps2_write_command(0x60);
    ps2_write_data(configByte);

    // Enable first PS/2 port
    ps2_write_command(0xAE);

    // Reset first PS/2 device
    ps2_write_data(0xFF);

    // Device should first ACK the reset command
    uint8_t response = ps2_read_data();

    if (response != 0xFA)
    {
        // Reset command was not acknowledged
        // Handle failure later
        return;
    }

    // After ACK, device performs its built-in self test
    response = ps2_read_data();

    if (response == 0xAA)
    {
        // Device self-test passed
    }
    else if (response == 0xFC || response == 0xFD)
    {
        // Device self-test failed
        return;
    }

    // At this point the first PS/2 device has been reset successfully
    // Should we return boolean depending if success or not?
}