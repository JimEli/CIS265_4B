/*************************************************************************
* Title: (CIS265_4B) Calendar Printer
* File: main.c
* Author: James Eli
* Date: 8/27/2017
*
* Write a program that prints a one-month calendar. The user specifies the 
* number of days in the month and the day of the week on which the month 
* begins:
*   Enter number of days in month: 31
*   Enter starting day of the week (1=Sun, 7=Sat): 3
*
*          1  2  3  4  5
*    6  7  8  9 10 11 12
*   13 14 15 16 17 18 19
*   20 21 22 23 24 25 26
*   27 28 29 30 31
*
* Hint: This program isn’t as hard as it looks. The most important part 
* is a for statement that uses a variable i to count from 1 to n, where n 
* is the number of days in the month, printing each value of i. Inside the 
* loop, an if statement tests whether i is the last day in a week; if so, 
* it prints a new-line character.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   08/27/2017: Initial release. JME
*************************************************************************/
#include <assert.h> 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constant definitions.
#define MIN_START_DAY          1  // Min input value (float).
#define MAX_START_DAY          7  // Max input value (float).
#define MIN_TOTAL_DAYS         28 // Min input value (float).
#define MAX_TOTAL_DAYS         31 // Max input value (float).
#define MAXIMUM_INPUT_ATTEMPTS 3  // Max acceptable number of user input attempts before aborting.

// Generalized input for total days in month and start day of week.
bool getDay(unsigned int *d, const char *prompt, const unsigned int min, const unsigned int max) {
	char input[4];                         // Holds user input as string.
	unsigned int day;                      // Holds converted string to integer.
	int attempts = MAXIMUM_INPUT_ATTEMPTS; // Input attempt counter.
	bool retVal = false;                   // Function return value, ture==success, assumed false at start.

	assert(attempts > 0); // Assert attempts valid non-zero, positive number.

	// Attempt only so many inputs.
	while (attempts--) {
		// Prompt and grab user input.
		fputs(prompt, stdout);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			exit(EXIT_FAILURE);
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remainder.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;
			// Attempt to convert from string to intger, and validate.
			if (sscanf_s(input, "%d", &day)) {
				if (day >= min && day <= max) {
					*d = day;
					retVal = true;
					break; // Success, so exit.
				}
				else
					fprintf(stdout, "Entry is outside allowable range (%d - %d)\n", min, max);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}
	return retVal;
}

// Program starts here.
int main(void) {
	unsigned int startDay;  // Calendar starting day of week (1=Sun thru 7=Sat).
	unsigned int totalDays; // Total number of days in calendar month (28 thru 31).

	if (getDay(&totalDays, "Enter number of days in month: ", MIN_TOTAL_DAYS, MAX_TOTAL_DAYS) &&
		getDay(&startDay, "Enter starting day of the week (1=Sun, 7=Sat): ", MIN_START_DAY, MAX_START_DAY) ) {
		unsigned int endDay = startDay + totalDays; // Calculate end of printing value.

		fputs("\n", stdout);

		// Displaying the calendar is very simplistic:
		for (unsigned int i = 1, day = 1; i < 38; i++)
			if (i >= startDay && i < endDay)
				fprintf(stdout, "%2d%c", day++, (i % 7) ? ' ' : '\n');
			else
				fputs("   ", stdout);

		fputs("\n", stdout);
	}
}

