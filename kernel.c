void clear_screen_VGAText();
void set_frame_with_string_VGAText(char *string);
int get_size_of_string(char *string);
void add_string_to_video_memory_VGAText(char *string);

// TODO: no sprintf allowed
void int_to_string(int number, char *buffer);

void main() {
    char str[55] = "Cine are noroc are";
    set_frame_with_string_VGAText("Cine are noroc are");
    for (volatile int i = 0; i < 1000000000; i++) {
    }
    set_frame_with_string_VGAText("Welcome, peasant!");
}

void clear_screen_VGAText() 
{
    char* video_memory = (char*) 0xb8000;
    for(int i = 0; i < 80*25; i += 2) 
    {
        *(video_memory + i) = ' '; // character
        *(video_memory + i + 1) = 0x0F; // color attribute
    }
}

int get_size_of_string(char *string) 
{
    int i = 0;
    while (*(string + i) != '\0') 
    {
        i++;
    }

    return i;
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