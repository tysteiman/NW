#ifndef NW_OPT
#define NW_OPT

typedef struct Opt {
    int    debug;          /* debug mode */
    int    test;           /* test mode */
    char * fileName;       /* filename from optind */
    char * fileSaveTarget; /* File name for saving */
} opt_t;

opt_t opts;

void parseOpts(int argc, char **argv);

#endif
