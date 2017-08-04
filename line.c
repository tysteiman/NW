#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib.h"
#include "cursor.h"
#include "line.h"
#include "screen.h"

char 
* 
substr(int start, int end, char *str)
{
    int i = start;
    int newStrIndex = 0;

    char newStr[MAX_LINE_LENGTH];

    for (; i < end + 1; i++)
        {
            newStr[newStrIndex] = str[i];
            newStrIndex++;
        }

    char *ret = strdup(newStr);
    ret[i] = '\0';

    return ret;
}

void 
lineDeleteChar(char *str, int *x, int *lineLength)
{
    int index = *x;
    char *beg = substr(0, (index - 1), str);
    char *end = substr((index + 1), strlen(str), str);

    int len = strlen(beg) + strlen(end);

    char newStr[len];

    int count = 0;
    int iBeg = 0;
    int iEnd = 0;

    for (; iBeg < strlen(beg); iBeg++)
        {
            newStr[count] = beg[iBeg];
            count++;
        }

    for (; iEnd < strlen(end); iEnd++)
        {
            newStr[count] = end[iEnd];
            count++;
        }

    newStr[count] = '\0';

    bzero(str, strlen(str));
    strcpy(str, newStr);

    --*lineLength;
}

void 
lineInsertChar(char character, char *str, int *x, int *lineLength)
{
    int index = *x;
    char *beg = substr(0, index - 1, str);
    char *end = substr(index, strlen(str), str);

    int len = (strlen(beg) + strlen(end)) + 1;

    char newStr[len];

    int count = 0;
    int ibeg = 0;
    int iend = 0;

    for (; ibeg < strlen(beg); ibeg++)
        {
            newStr[count] = beg[ibeg];
            count++;
        }

    newStr[count++] = character;

    for (; iend < strlen(end); iend++)
        {
            newStr[count] = end[iend];
            count++;
        }

    newStr[count] = '\0';

    bzero(str, strlen(str));
    strcpy(str, newStr);

    /* increase x & line length by 1 */
    ++*x;
    ++*lineLength;
}

void
lineMoveRight(int len, cursor_t *cursor)
{
    if (len > 0 && cursor->x != len - 1)
        {
            ++cursor->x;
            cursor->xSnap = cursor->x;

        }
}

void
lineMoveLeft(cursor_t *cursor)
{
    if (cursor->x != 0)
        {
            --cursor->x;
            cursor->xSnap = cursor->x;
        }
}

void
lineMoveToLineEnd(int len, cursor_t *cursor)
{
    if (len > 0)
        {
            cursor->x = len;
            cursor->xSnap = cursor->x;
        }
}

void
lineMoveToLineBeg(cursor_t *cursor)
{
    if (cursor->x > 0)
        {
            cursor->x = 0;
            cursor->xSnap = cursor->x;
        }
}

void
lineClearLine(line_t *line, cursor_t *cursor)
{
    bzero(line->content, strlen(line->content));
    line->len = 0;

    cursor->x = 0;
    cursor->xSnap = 0;
}

void
freeNodes(line_t *head)
{
    line_t *cur;
    line_t *next;

    cur = head;

    /**
     * Free up our line_t nodes from memory. This needs
     * to be a little more agnostic and moved into a
     * good function that can clear any nodes passed
     * instead.
     */
    while (cur->next != NULL)
        {
            next = cur->next;
            free(cur);
            cur = next;
        }

    free(cur);

}
