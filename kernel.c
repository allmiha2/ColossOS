void clear_screen_VGAText();
void set_frame_with_string_VGAText(char *string);
void add_string_to_video_memory_VGAText(char *string);

//void initialize_cursor();

void int_to_string(int number, char *buffer);

// add a character at cursor
// move cursor left/right/up/down
// move cursor to coordinate 
// unmodifiable buffer, modifiable buffer - cursor only in modifiable


void main() {
    set_frame_with_string_VGAText("Cine are noroc are");
    for (volatile int i = 0; i < 1000000000; i++) {
        // sleep
    }
    set_frame_with_string_VGAText("Welcome, peasant!");
}

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


// TODO: move to a utils.c file or something
void int_to_string(int n, char *buffer) 
{
    // should maybe use a pow method but too lazy

    int ten_to_power_of_digitcount = 1, cn = n;
    while (cn > 0)
    {
        cn = cn / 10;
        ten_to_power_of_digitcount *= 10;
    }

    // start with first digit
    int i = 0;
    ten_to_power_of_digitcount /= 10;
    while (ten_to_power_of_digitcount >= 1)
    {
        *(buffer + i) = (char) (n / ten_to_power_of_digitcount % 10) + '0';
        ten_to_power_of_digitcount /= 10;
        i++;
    }

}