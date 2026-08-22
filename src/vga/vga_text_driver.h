void clear_screen_VGAText(void);
void add_character_at_VGAText(char c, int row, int column);
void add_string_at_VGAText(char *string, int row, int column);
void set_frame_with_string_VGAText(char *string);

// Maybe TODOs?:
// add a character at cursor
// move cursor left/right/up/down
// move cursor to coordinate 
// unmodifiable buffer, modifiable buffer - cursor only in modifiable

// Conclusion: will first do vga and keyboard drivers, and then terminal, 
// then decide where cursor belongs