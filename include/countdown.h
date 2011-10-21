///////////////////////////countdown.h/////////////////////////
/*             Programmed by Michael Nawrocki                 */
/*             Version 0.1 for Linux                          */
/*             Updated 04/23/2011                             */
/*             Licensed under GPL version 3.0                 */
/*             mnawrocki3@gatech.edu                          */
/*////////////////////////////////////////////////////////////*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //needed for sleep()
#include <stdbool.h> //needed for struct bool
#include <time.h> //Times.
#include <string.h> //Needed for string functions
#include <limits.h>
//Externs
extern bool verbose; 
extern bool specific; 
//Prototypes
struct tm *parseTimeString(char * strtime);
struct tm *parseDateString(char * strdate, char * strtime); 
unsigned long int parseArgs(int *numarg, char **args); 
void processBooleanOpts(unsigned long int *myTimer);
