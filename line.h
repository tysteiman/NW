#ifndef NW_LINE_H
#define NW_LINE_H

typedef struct Line {
    int number;                    /* Line number */
    int len;                       /* Line's length */
    char content[MAX_LINE_LENGTH]; /* Line's contents */
    char *contentP;                /* Pointer to content */
    struct Line *next;             /* Next Line in file */
    struct Line *prev;             /* Previous line in file */
} line_t;

#define NW_MOVE_END()   (moveToLineEnd(file->current->len, &file->cursor))
#define NW_MOVE_BEG()   (moveToLineBeg(&file->cursor))
#define NW_MOVE_RIGHT() (moveRight(file->current->len, &file->cursor))
#define NW_MOVE_LEFT()  (moveLeft(&file->cursor))

/* DECLS */
void   deleteChar (char * str, int index, int *x, int *lineLength);
void   insertChar (char character, char * str, int index, int *x, int *lineLength);
char * substr     (int start, int end, char *str);
void moveRight(int len, cursor_t *cursor);
void moveLeft(cursor_t *cursor);
void moveToLineEnd(int len, cursor_t *cursor);
void moveToLineBeg(cursor_t *cursor);

#endif
