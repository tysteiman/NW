/**
 * test.h
 * This is meant to be a hard coded test file to deal with when expecting very specific results
 * in our tests. This is a decent way to have static files for testing to see how our entire
 * file_t object is working throughout the application's functionality
 */

#ifndef NW_LIB
#define NW_LIB

/* CONSTANTS */
#define TRUE 1
#define FALSE 0

#define NOCOLOR "\033[0m"
#define RED "\033[91m"
#define GREEN "\033[92m"
#define YELLOW "\033[93m"
#define BLUE "\033[94m"
#define PURPLE "\033[95m"
#define CYAN "\033[96m"

#define MAX_LINE_LENGTH 300

/* scroll directions */
#define SCRL_UP -1
#define SCRL_DOWN 1

/* DECLS */
void err        (char * msg);
void logint     (char * name, int    var);
void logstr     (char * name, char * str);
void colorStr   (char * str,  char * color);
int  fileExists (char * path);
int  stringEq   (char *str1,  char * str2);
void dumpColors();
void dumpDebug(char *msg);

#endif
