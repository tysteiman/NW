#ifndef NW_LIB
#define NW_LIB

/* CONSTANTS */
#define TRUE 1
#define FALSE 0

#define NOCOLOR "\033[0m"
#define GREY "\033[91m"
#define GREEN "\033[92m"
#define YELLOW "\033[93m"
#define BLUE "\033[94m"
#define PURPLE "\033[95m"
#define CYAN "\033[96m"

/* DECLS */
void err        (char * msg);
void logint     (char * name, int    var);
void logstr     (char * name, char * str);
void colorStr   (char * str,  char * color);
int  fileExists (char * path);
void dumpColors();

#endif
