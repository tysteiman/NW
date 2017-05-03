#ifndef NW_SCREEN
#define NW_SCREEN

#include "file.h"

typedef struct {
    int height;
    int width;
} screen_t;

screen_t screen;

void initScreen(line_t *lines);

#endif
