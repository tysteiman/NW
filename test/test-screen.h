#ifndef NW_TEST_SCREEN_H
#define NW_TEST_SCREEN_H

#include "../file.h"

#define NW_SCR_TEST() (initScreenTestFile(file))

void initScreenTest(file_t *file);
void screenDeleteCharTest(file_t *file);
void screenMoveDownTest(file_t *file);
void screenMoveLeftTest(file_t *file);
void screenNewLineTest(file_t *file);
void screenMoveEndTest(file_t *file);
void screenMoveBegTest(file_t *file);
void screenMoveRightTest(file_t *file);
void screenInsertCharTest(file_t *file);

#endif
