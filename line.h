#ifndef NW_LINE_H
#define NW_LINE_H

typedef struct Line {
    int number;                    /* Line number */
    int len;                       /* Line's length */
    char content[MAX_LINE_LENGTH]; /* Line's contents */
    struct Line *next;             /* Next Line in file */
    struct Line *prev;             /* Previous line in file */
} line_t;

/* DECLS */
void   deleteChar (char * str, int index);
void   insertChar (char character, char * str, int index);
char * substr     (int start, int end, char *str);

#endif