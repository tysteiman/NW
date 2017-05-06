#ifndef NW_OPT
#define NW_OPT

typedef struct {
    int    debug;          /* debug mode */
    char * fileName;       /* filename from optind */
    char * fileSaveTarget; /* File name for saving */
} opt_t;

opt_t opts;

void parseOpts(int argc, char **argv);

#endif
