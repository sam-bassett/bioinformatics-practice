#include <stdlib.h>
#include <stdio.h>

int countHammingDistance(char *s, char *t) {
	int i;
	int hamming = 0;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] != t[i]) {
			hamming++;
		}
	}
	return hamming;
}

int main (int argc, char *argv[]) {
	char *s = malloc(sizeof(char)*1000);
	char *t = malloc(sizeof(char)*1000);

	printf("Please enter the first string, s:\n");
	scanf("%s", s);
	printf("Please enter the second string, t:\n");
	scanf("%s", t);

	int hamming = countHammingDistance(s,t);
	printf("Point mutations = %d\n", hamming);
	return EXIT_SUCCESS;
}