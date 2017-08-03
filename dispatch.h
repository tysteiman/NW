#ifndef NW_DISPATCH_H
#define NW_DISPATCH_H

#include "file.h"

#define NW_KEY_DOWN "^N"
#define NW_KEY_UP "^P"
#define NW_KEY_LEFT "^B"
#define NW_KEY_RIGHT "^F"
#define NW_KEY_END "^E"
#define NW_KEY_BEG "^A"
#define NW_KEY_EXIT "^C"
#define NW_KEY_SAVE "^S"
#define NW_KEY_DEL "^D"
#define NW_DEL_LINE "^K"
#define NW_NEW_LINE "^O"
#define NW_KEY_RET '\n'

void dispatchRight(file_t *file);
void dispatchLeft(file_t *file);
void dispatchEnd(file_t *file);
void dispatchBeg(file_t *file);
void dispatchInsert(char c, file_t *file);
void dispatchDeleteChar(file_t *file);
void dispatchDown(file_t *file);
void dispatchUp(file_t *file);
void dispatchNewLine(file_t *file);

#endif
