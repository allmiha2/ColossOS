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