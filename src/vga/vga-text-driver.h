struct Cursor {
    int row;
    int column;
};

void clear_screen_VGAText();
void set_frame_with_string_VGAText(char *string);
void add_string_to_video_memory_VGAText(char *string);

// add a character at cursor
// move cursor left/right/up/down
// move cursor to coordinate 
// unmodifiable buffer, modifiable buffer - cursor only in modifiable