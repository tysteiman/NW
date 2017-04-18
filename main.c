#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "lib.h"

int main(int argc, char **argv)
{
  int curFlag;
  int poopflag = FALSE;
  while ((curFlag = getopt(argc, argv, "p:")) != -1) {
    switch (curFlag) {
    case 'p':
      /**
       * This is stubbed out right now.
       * All we need to do is set up our arguments
       * and use optarg for actual arguments
       * we need values for.
       */
      poopflag = atoi(optarg);
      break;
    default:
      err("Argument Error");
    }
  }

  /**
   * Get our independent arguments. This again is just for
   * an example since we'll probably need it eventually.
   */
  int index;
  for (index = optind; index < argc; index++) {
    printf("Non opt arg: %s\n", argv[index]);
  }

  logint("POOP FLAG", poopflag);

  return 0;
}
