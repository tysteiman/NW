#include <stdio.h>
#include <string.h>

#include "lib.h"

char * substr(int start, int end, char *str)
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

void deleteChar(char *str, int index)
{
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
}
