/* Apparently, ISO C does not permit variable arguments in macros so we have to define a function to kind of wrap in a macro. */

#ifndef __DEBUGMACRO_h__
#define __DEBUGMACRO_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>

#ifndef NDEBUG
#  define debug_print(bit, msg) \
    if(GLOBAL_DEBUG_BITS&bit) {\
    stderr_printf msg;}
void stderr_printf(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
}
#else
#  define debug_print(msg)
#endif



/* declaration of a global variable seen in other files - it has to be defined in one of the .c files (here: module.c)*/ 
extern unsigned int GLOBAL_DEBUG_BITS;	/* this variable will control the DEBUGGING bits relevant to debug and check_debug macros above.*/


/* It returns "None" if errno (code error) is 0, and the error message corresponding to the code otherwise. */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))


/* It just prints to the screen [ERROR] (file: line: error message) and additional string provided by the user. */
/* __FILE__ stores information about the current file and __LINE__ about the current line. */
/* This is a programmer who decides when to print this error statement. */


#endif
