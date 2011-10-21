////////////////////////////countdown.c/////////////////////////
/*             Programmed by Michael Nawrocki                 */
/*             Version 0.1 for Linux                          */
/*             Updated 04/23/2011                             */
/*             Licensed under GPL version 3.0                 */
/*             mnawrocki3@gatech.edu                          */
/*////////////////////////////////////////////////////////////*/

#include <countdown.h>
bool verbose = false;
bool specific = false;
/*
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
*/
unsigned long int parseArgs(int *numarg, char **args) //parses the command line arguments
{
	bool secs = true; //default use seconds instead of minutes
	short i; //iterator
	unsigned long int num = 0; //hold the number of seconds
	for(i = 1; i < *numarg; i++) //Check each argument
	{
		if(strcmp(args[i], "-n") == 0) //n is in seconds
			secs = true;
		else if(strcmp(args[i], "-N") == 0) //N is in minutes
			secs = false;
		else if(strcmp(args[i], "-v") == 0) //Enable verbosity
			verbose = true;
		else if(strcmp(args[i], "-t") == 0 && !specific ) //parses a time string, fmt 24:59:59
		{
			if(i+1 <= *numarg)
			{
				num = (unsigned long) mktime(parseTimeString(args[i+1])); //Examine argument after -t
				i++; //We already parsed the next argument, increment count
			}
		}
		else if(strcmp(args[i], "-D")==0) //Specific Date and time, fmt MM/DD/YYYY 24:59:59
		{
			if(i + 2 <= *numarg)
			{
				num = (unsigned long) mktime(parseDateString(args[i+1], args[i+2]));
				i+=2;
			}
		}
		else if(atol(args[i]) != 0 && !specific) 
			num = atol(args[i]);
		else 
		{ 
			printf("INVALID ARGUMENT: %s",args[i]); //What did you just give me? it was not valid.
			return 0;
		} 
	}
	if(!secs) //Minutes = 60 * seconds
		return (60*num);
	else
		return num;
}

struct tm *parseTimeString(char * strtime) //Determine information in time string (e.g. 24:59:59)
{
	int hour, minute, second; //Hold hours, minutes, and seconds
	long *holder = malloc(sizeof(long));
	hour = 0; //Initialize everything
	minute = 0;
	second = 0;
	char *delim = ":"; //Delimiter is the colon
	char * temp; //Temporarily hold the string, used for checking purposes
  
	temp = strtok(strtime, delim); //Look at strtime
	if(temp != NULL)
	{
		*holder = strtol(temp, NULL, 0);
		if(*holder < 24 && *holder > -1)
			hour = *holder;
		else
		{
			printf("RANGE ERROR! %ld is not a valid hour!", *holder);
			exit(1);
		}
  	}
	temp = strtok(NULL, delim); //continue
	if(temp != NULL)
	{
		*holder = strtol(temp, NULL, 0);
		if(*holder < 59 && *holder > -1)
			minute = *holder;
		else
		{
			printf("RANGE ERROR! %ld is not a valid minute!", *holder);
			exit(1);
		}
  	}
  
	temp = strtok(NULL, delim); //continue
	if(temp != NULL)
	{
		*holder = strtol(temp, NULL, 0);
		if(*holder < 59 && *holder > -1)
			second= *holder;
		else
		{
			printf("RANGE ERROR! %ld is not a valid second!", *holder);
			exit(1);
		}
  	}
	specific = true; //We are using specific values now.
	free(holder);

	time_t raw; //Raw, current time. Used for date, etc
	time(&raw); //Get current time.
	struct tm * tim = localtime(&raw); //Convert to a tm struct
	tim->tm_hour = hour; //Set hours to input
	tim->tm_min = minute; //Set minutes to input
	tim->tm_sec = second; //Set seconds to input
	return(tim); //Convert values to the real time
}

struct tm *parseDateString(char * strdate, char * strtime)
{
	int year, month, day;
	struct tm *tempTm = parseTimeString(strtime); //Parse the time argument
	long *holder = malloc(sizeof(long));
	year = 0; //Initialize our vars just in case
	month = 0;
	day = 1;
	char *delim = "/"; //Date fmt MM/DD/YYYY, / delimiter
	char * temp; //holds the string temporarily

	temp = strtok(strdate, delim); //Look at strdate
	if(temp != NULL)
	{
		*holder = strtol(temp, NULL, 0);
		if(*holder < 13 && *holder > 0)
			month = *holder;
		else
		{
			printf("RANGE ERROR! %ld not a valid month!", *holder);
			exit(0);
		}
	}

	temp = strtok(NULL, delim); //continue
	if(temp != NULL)
	{
		*holder = strtol(temp, NULL, 0);
		if(*holder < 32 && *holder > 0)
			day = *holder;
		else
		{
			printf("RANGE ERROR! %ld not a valid day!", *holder);
			exit(1);
		}
	}

	temp = strtok(NULL, delim); //continue
	if(temp != NULL)
	{
		*holder = strtol(temp, NULL, 0);
		if(*holder < 4000 && *holder > 2010)
			year = *holder;
		else
		{
			printf("RANGE ERROR! %ld not a valid year!", *holder);
			exit(1);
		}
	}
	free(holder);
	tempTm->tm_year = year - 1900; //tm_year = years since 1900
	tempTm->tm_mon = month - 1; //tm_mon = months since january, 0-11
	tempTm->tm_mday = day; //tm_mday = day of the month, 1-31
	return(tempTm);
}

void processBooleanOpts(unsigned long int *myTimer)
{
	if(specific)
	{
		int *temp = malloc(sizeof(int)); //Temporarily hold seconds
		time_t seconds;
		time(&seconds);
		*temp = difftime((time_t)*myTimer, seconds); //Difference between future and now.
		if(*temp > 0) //Only care if it is greater than 0.
			*myTimer = *temp;
		else
		{
			printf("TIME HAS GONE\n");
			exit(3);
		}
		free(temp); //Cleaning up.
	}
	if(verbose)
	{
		time_t future;
		time(&future);
		future += *myTimer;
		printf("Counting down to %s\n", ctime((time_t *)&future)); 
	}
}
