#ifndef NW_FILE
#define NW_FILE

typedef struct {
    char *name;
    int totalLines;
} file_t;

file_t newFile  (char *fileName);
void   loadFile (char *fileName);

#endif
