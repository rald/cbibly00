#ifndef DIE_H
#define DIE_H

#include <stdlib.h>
#include <stdarg.h>



void die(int code,char* fmt,...);



#ifdef DIE_IMPLEMENTATION

void die(int code,char* fmt,...) {
  va_list args;

  va_start(args,fmt);
    vprintf(fmt,args);
  va_end(args);

  exit(code);
}



#endif /* DIE_IMPLEMENTATION */



#endif /* DIE_H */
