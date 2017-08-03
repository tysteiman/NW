#ifndef NW_LINE_H
#define NW_LINE_H

/* STRUCTS */
typedef struct Line {
    int    number;                   /* Line number */
    int    len;                      /* Line's length */
    char   content[MAX_LINE_LENGTH]; /* Line's contents */
    char * contentP;                 /* Pointer to content */
    struct Line * next;              /* Next Line in file */
    struct Line * prev;              /* Previous line in file */
    void (*delete_char)(char * str, int *x, int *lineLength);
    void (*insert_char)(char character, char * str, int *x, int *lineLength);
    void (*move_right)(int len, cursor_t *cursor);
    void (*move_left)(cursor_t * cursor);
    void (*move_end)(int len, cursor_t *cursor);
    void (*move_beg)(cursor_t * cursor);
} line_t;

/* FUNCTION MACROS */
#define NW_MOVE_END()   (lineMoveToLineEnd(file->current->len, &file->cursor))
#define NW_MOVE_BEG()   (lineMoveToLineBeg(&file->cursor))
#define NW_MOVE_RIGHT() (lineMoveRight(file->current->len, &file->cursor))
#define NW_MOVE_LEFT()  (lineMoveLeft(&file->cursor))
#define NW_DEL()        (lineDeleteChar(&file->current->content[0], &file->cursor.x, &file->current->len))
#define NW_INS(c)       (lineInsertChar(c, &file->current->content[0], &file->cursor.x, &file->current->len))
#define NW_CLEAR_LINE() (lineClearLine(file->current, &file->cursor))

/* FUNCTION DECLS */

void   lineDeleteChar    (char * str, int *x, int *lineLength);
void   lineInsertChar    (char character, char * str, int *x, int *lineLength);
char * substr            (int start, int end, char *str);
void   lineMoveRight     (int len, cursor_t *cursor);
void   lineMoveLeft      (cursor_t * cursor);
void   lineMoveToLineEnd (int len, cursor_t *cursor);
void   lineMoveToLineBeg (cursor_t * cursor);
void   lineClearLine     (line_t * line, cursor_t *cursor);
void   freeNodes         (line_t * head);

#endif
