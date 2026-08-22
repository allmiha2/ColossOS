#include "vga_text_driver.h"
// VGA Text mode has 80x25 cells, each cell having 2 bytes

// rows and cols start at 0
const int ROWS = 25;
const int COLUMNS = 80;

// TODO:
// - make a private function that hides the "*(video_memory + (2 * i)) = ' '"
// just make a set_char_at_linear_index_VGAText()
// - same for set_colorCode_at_linear_index_VGAText()
// - make sure the input strings do not exceed the 80x25 grid

void add_string_to_video_memory_VGAText(char *string);

char* video_memory = (char*) 0xb8000;

void clear_screen_VGAText(void)
{
    for(int i = 0; i < ROWS * COLUMNS; i++) 
    {
        *(video_memory + (2 * i)) = ' '; // character
        *(video_memory + (2 * i) + 1) = 0x0F; // color attribute (white foreground, black background)
    }
}

void add_character_at_VGAText(char c, int row, int column)
{
    if (row > ROWS || row < 0 || column > COLUMNS || column < 0) 
    {
        return;
    }

    // find the cell index in the linear memory
    int index = row * COLUMNS + column;

    *(video_memory + (2 * index)) = c;
}

void add_string_at_VGAText(char *string, int row, int column)
{
    // find the cell index in the linear memory
    int startingIndex = row * COLUMNS + column;

    int stringBufferIndex = 0;
    for(int i = startingIndex; i < ROWS * COLUMNS; i++) 
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

        *(video_memory + (2 * i)) = charToBePrinted; // character
        *(video_memory + (2 * i) + 1) = 0x0F; // color attribute
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
    int stringBufferIndex = 0;
    for(int i = 0; i < ROWS * COLUMNS; i++) 
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

        *(video_memory + (2 * i)) = charToBePrinted; // character
        *(video_memory + (2 * i) + 1) = 0x0F; // color attribute
    }
}
