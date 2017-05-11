#ifndef NW_SCREEN
#define NW_SCREEN

#include "file.h"

typedef struct {
    int height;
    int width;
} screen_t;

screen_t screen;

/* DECLS */
void initScreen        (file_t * file);
void attachKeyListener (file_t * file);
void handleInput       (char ch, char *input, file_t *file);
void shiftLinesDown    (file_t * file);
void mvdown            (file_t * file);
void mvup              (file_t * file);
void mvright           (file_t * file);
void mvendofln         (file_t * file, int mv);
void mvbegofline       (file_t * file, int mv);
void mvleft            (file_t * file);
void snaptoend         (file_t * file);

#endif
