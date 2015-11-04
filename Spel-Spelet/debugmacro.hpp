/* See the practical applications of these macros in module.c and main.c in testunit_debug_demo */

#ifndef DEBUGMACRO_HPP
#define DEBUGMACRO_HPP

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG

/* empty macros if NDEBUG is defined */
#define debug(level,fmt, ...)
#define check_debug(level,COND,fmt, ...)

#else

/* These macros print to stderr, depending on whether GLOBAL_DEBUG_LEVEL is not less than macro's argument level. */
#define debug(level,fmt, ...) \
	if(GLOBAL_DEBUG_LEVEL>=level) { \
	fprintf(stderr, "DEBUG %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); }

/* This macro addtionally checks the condition (macros' argument) before sending anything to stderr stream (screen, most often). */
#define check_debug(level,COND,fmt, ...) if(!(COND)) { debug(level,fmt, ##__VA_ARGS__); errno=0; }

#endif


/* declaration of a global variable seen in other files - it has to be defined in one of the .c files (here: module.c)*/ 
extern int GLOBAL_DEBUG_LEVEL;	/* this variable will control the DEBUGGING level relevant to debug and check_debug macros above.*/


/* It returns "None" if errno (code error) is 0, and the error message corresponding to the code otherwise. */
#define clean_errno() (errno == 0 ? "None" : strerror(errno))


/* It just prints to the screen [ERROR] (file: line: error message) and additional string provided by the user. */
/* __FILE__ stores information about the current file and __LINE__ about the current line. */
/* This is a programmer who decides when to print this error statement. */

#define log_error(fmt, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " fmt "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

/* As above, but for sending warning to stderr. */
#define log_warning(fmt, ...) fprintf(stderr, "[WARNING] (%s:%d: errno: %s) " fmt "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)


/* As above, but for sending information to stderr. */
#define log_info(fmt, ...) fprintf(stderr, "[INFO] (%s:%d) " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/* If the input argument condition COND is met, the macro prints error message using log_err and sends the program control to the local error_cleanup labelled line, where some cleanup and finalising operations should be performed -> most often exiting from the current function or the program */
#define check(COND, fmt, ...) if(!(COND)) { log_error(fmt, ##__VA_ARGS__); errno=0; goto error_cleanup; }

/* Very similar to chack but without checking any conditions. It should be used whe undesirable condition is already detected.*/
/* Most common in SWITCH-CASE where DEFAULT option is defined or in ELSE blocks of compound IF statements (with many ELSE IF). */
#define unexpected_variant(fmt, ...)  { log_error(fmt, ##__VA_ARGS__); errno=0; goto error_cleanup; }

/* Prints "Out of memory" and behaves like check macro. */
#define check_mem(PTR) check((PTR), "Out of memory.")


#endif
