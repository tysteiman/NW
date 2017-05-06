#ifndef NW_LIB
#define NW_LIB

/* CONSTANTS */
#define TRUE 1
#define FALSE 0

/* DECLS */
void err        (char   * msg);
void logint     (char   * name, int    var);
void logstr     (char   * name, char * str);
int  fileExists (char   * path);

#endif
