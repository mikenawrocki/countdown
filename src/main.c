////////////////////////////main.c//////////////////////////////
/*             Programmed by Michael Nawrocki                 */
/*             Version 0.1 for Linux                          */
/*             Updated 04/23/2011                             */
/*             Licensed under GPL version 3.0                 */
/*             mnawrocki3@gatech.edu                          */
/*////////////////////////////////////////////////////////////*/

#include <countdown.h>

int main(int argc, char **argv)
{
	if(argc < 2 || argc > 6) //Never more than 4 arguments at a time
	{
		printf("Usage: Countdown <-n -N -v> [time]\n"); 
		return 2;
	}
	unsigned long int timer = parseArgs(&argc, argv); //Look at our arguments! yay!
	processBooleanOpts(&timer);
	while(timer > 0) //The actual countdown
	{
		if(verbose) //Print only when verbosity is turned on
		{
		      printf("%lu..", timer);
		      fflush(stdout);
		}
		timer--; //Decrement the seconds
		sleep(1);//Sleep for 1 second to time.
	  }
	printf("ZERO!\n"); //Countdown is over
	return 0;
}
