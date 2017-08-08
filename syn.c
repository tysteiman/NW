#include <string.h>

#include "syn.h"
#include "lib.h"

char * parseExtension(char *fileName)
{
    char *res;
    
    int i = 0;
    int index = -1;

    for (; i < strlen(fileName); i++)
        {
            if (fileName[i] != '.')
                {
                    continue;
                }
            else
                {
                    index = i;
                }
        }

    if (index != -1)
        {
            res = substr(++index, strlen(fileName), fileName);
        }

    return res;
}
