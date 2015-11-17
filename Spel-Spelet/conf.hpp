/* Header file containing configurations for the whole game. */

#ifndef CONF_HPP
#define CONF_HPP

#include <string>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <random>


/*Path to were the resources are*/
char const RES_PATH[] = "res/";

/*Splash screen settings*/
const bool SHOW_SPLASH = true;
const int splc = 3; //Amount of splash screens. Note that splash screen files from 0 to (splc-1) must exist if splc is larger than 0;

extern int DAMAGE_VAR_LOW; //Lower bound of variation in damage dealt
extern int DAMAGE_VAR_HIGH; //Higher bound of variation in damage dealt

		/* declaration of a global variable seen in other files - it has to be defined in one of the .c files (here: module.c)*/


#endif
