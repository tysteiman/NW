#include "test-screen.h"
#include "test.h"

#include "../screen.h"
#include "../dispatch.h"

void
dispatchDownTest(file_t *file)
{
    /* use small file in test/lib */
    NW_SCR_TEST_SMALL();

    dispatchDown(file);
    dispatchEnd(file);
    dispatchDown(file);

    NW_SCR_CLOSE();

    /* curx should be at 20, xSnap at 30 still */
    NW_ASSERT(NW_CURY, 2, "cury is at 2");
    NW_ASSERT(NW_CURX, 20, "curx is at 20");
    NW_ASSERT(file->cursor.x, 20, "Cursor x at 20");
    NW_ASSERT(file->cursor.xSnap, 30, "xSnap is at 30");
}
