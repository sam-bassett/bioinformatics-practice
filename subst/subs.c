#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BP 1000
#define MIN_STRING 3
#define MIN_SUBSTRING 2
#define STOP -99

// s is the string, t is the substring to match.
void findSubstrings (char *s, char *t, int *locationArray);
void printLocations (int *locationArray);

int main (int argc, char *argv[]) {
	// this could be done with some sort of finite state automata, right?
	// honestly, why would you? This has a maxBP of 1000.

	char *string = malloc(sizeof(char)*MAX_BP);
	char *substring = malloc(sizeof(char)*MAX_BP);

	printf("Please enter the string: ");
	scanf("%s", string);
	printf("Now enter the substring to match: ");
	scanf("%s", substring);

	// if every element of substrings is a repeat, this is the max.
	int maxSubstrings = strlen(string)/strlen(substring) + 1;
	int *substringLocations = malloc(sizeof(int)*maxSubstrings);

	findSubstrings(string, substring, substringLocations);
	printLocations(substringLocations);

	return EXIT_SUCCESS;
}

void findSubstrings (char *s, char *t, int *locationArray) {
	int i, j, k;
	int sLength = strlen(s);
	int tLength = strlen(t);
	k = 0;
	for (i = 0; i <= sLength - tLength; i++) {
		if (s[i] == t[0]) {
			int match = 1;
			for (j = 1; j < tLength; j++) {
				if (s[i+j] != t[j]) {
					match = 0;
					break;
				}
			}
			if (match == 1) {
				locationArray[k] = i;
				k++;
			}
		}
	}
	locationArray[k] = STOP;
}

void printLocations (int *locationArray) {
	int i = 0;
	while (locationArray[i] != STOP) {
		printf("%d ", locationArray[i++] + 1);
	}
	printf("\n");
}
