/* See the practical applications of these macros in module.c and main.c in testunit_debug_demo */

#ifndef _TESTMACRO_h
#define _TESTMACRO_h

#include <stdio.h>
#include <stdlib.h>
#include "debugmacro.h"

/* initialisation */
#define TEST_start() char *message = NULL

/* assertion - if the condition is not met, print error message using debugmacro.h */
#define TEST_assert(test, message) if (!(test)) { log_error(message); return message; }
 
/* important macro that helps run test functions */
/* if the test function returns error message, the macro returns it, otherwise does not return anything. */
#define TEST_run(test) debug(0,"\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

#endif

/* declaration of a global variable seen in other files - it has to be defined in one of the .c files (here: module.c)*/ 
extern int tests_run;  /* it holds the number of successful tests */
