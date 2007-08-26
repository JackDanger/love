#ifndef AMF_FONT_H
#define AMF_FONT_H

#define NUM_CHARACTERS 96

void glSetFont(const char * fontname);
void glPrint(const char * fmt, ...);
void glDeleteFonts();

#endif