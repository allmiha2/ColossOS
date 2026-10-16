#include "vga_text_driver.h"

void main() {
    set_frame_with_string_VGAText("Starting ColossOS!");
    for (volatile int i = 0; i < 1000000000; i++) {
        // sleep
    }
    set_frame_with_string_VGAText("Welcome, peasant!");
    add_string_at_VGAText("What are you seeking here?", 1, 0);
    add_character_at_VGAText('>', 2, 0);
}

void kmain(void)
{
    //vga_init();

    //idt_init();

    //pic_remap(0x20, 0x28);

    //ps2_controller_init();
    //keyboard_init();

    // Enable interrupts (sti) when handlers and IRQ masks are ready
}