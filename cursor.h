#ifndef NW_CURSOR_H
#define NW_CURSOR_H

typedef struct Cursor {
    int x;                         /* Current cursor x pos */
    int xSnap;                     /* Value we should snap back to when moving */
    int y;                         /* Current cursor y pos */
} cursor_t;

#endif
