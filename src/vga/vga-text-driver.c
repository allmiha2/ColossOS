#include "vga-text-driver.h"
void clear_screen_VGAText() 
{
    char* video_memory = (char*) 0xb8000;
    for(int i = 0; i < 80*25; i += 2) 
    {
        *(video_memory + i) = ' '; // character
        *(video_memory + i + 1) = 0x0F; // color attribute (white foreground, black background)
    }
}

void set_frame_with_string_VGAText(char *string) 
{
    clear_screen_VGAText();

    add_string_to_video_memory_VGAText(string);
}

// add memory address as param?
void add_string_to_video_memory_VGAText(char *string)
{
    char *video_memory = (char*) 0xb8000;
    int stringBufferIndex = 0;
    for(int i = 0; i < 80*25; i += 2) 
    {
        char charToBePrinted;
        if (string[stringBufferIndex] != '\0')
        {
            charToBePrinted = string[stringBufferIndex];
            stringBufferIndex++;
        }
        else
        {
            charToBePrinted = ' ';
        }

        *(video_memory + i) = charToBePrinted; // character
        *(video_memory + i + 1) = 0x0F; // color attribute
    }
}
