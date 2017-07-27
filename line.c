#include <stdio.h>
#include <string.h>

#include "lib.h"
#include "cursor.h"

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

/**
 * @TODO this function is INCOMPLETE! we need to update file->cursor.x!!
 */
void 
deleteChar(char *str, int *x, int *lineLength)
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

    /**
     * @TODO we should probably make this into a helper function for
     *       erasing & replacing strings!
     */
    bzero(str, strlen(str));
    strcpy(str, newStr);

    /* decrease xpos & line length by 1 */
    --*x;
    --*lineLength;
}

/**
 * @TODO this function is INCOMPLETE! we need to update file->cursor.x!!
 */
void 
insertChar(char character, char *str, int *x, int *lineLength)
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
moveRight(int len, cursor_t *cursor)
{
    if (cursor->x != len - 1)
        {
            ++cursor->x;
        }
}

void
moveLeft(cursor_t *cursor)
{
    if (cursor->x != 0)
        {
            --cursor->x;
        }
}

void
moveToLineEnd(int len, cursor_t *cursor)
{
    if (len > 0)
        {
            cursor->x = len - 1;
        }
}

void
moveToLineBeg(cursor_t *cursor)
{
    if (cursor->x > 0)
        {
            cursor->x = 0;
        }
}
