#include "vga-text-driver.h"

void main() {
    set_frame_with_string_VGAText("Cine are noroc are");
    for (volatile int i = 0; i < 1000000000; i++) {
        // sleep
    }
    set_frame_with_string_VGAText("Welcome, peasant!");
}