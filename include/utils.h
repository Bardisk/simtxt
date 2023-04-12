#ifndef _UTILS_
#define _UTILS_

#define panic_on(msg, cond) \
  do {\
    if (!(cond)) {puts(msg); assert(0);}\
  }while(0)

#endif