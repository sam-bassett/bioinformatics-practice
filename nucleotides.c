#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void reverse(char *toReverse, char *reversed, int length) {
	int i;
	for (i = 0; i < length; i++) {
		reversed[length - i] = toReverse[i];	
	}
}

int main (int argc, char *argv[]) {
	int adenine = 0;
	int guanine = 0;
	int thymine = 0;
	int cytosine = 0;

	FILE *fp = NULL;
	char buffer[1000];
	char reverseComplement[1000];
	memset(reverseComplement, 0, 10);

	if (argc == 2) {
		char *filename = argv[1];
		fp = fopen(filename, "r");
	} else {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	if (argc == 2 && fp == NULL) {
		fprintf(stderr, "No file found at %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	fscanf(fp, "%s\n", buffer);
	
	char temp = '0';
	int i = 0;
	while (temp != EOF) {
		temp = buffer[i];
		if (temp == 'A') {
			temp = 'T';
		} else if (temp == 'T') {
			temp = 'A';
		} else if (temp == 'C') {
			temp = 'G';
		} else if (temp == 'G') {
			temp = 'C';
		} else if ((int) temp == 0) {
			break;
		}
		buffer[i] = temp;
		i++;
	}
	reverse(buffer, reverseComplement, i);
	fclose(fp);
	int j = 0;
	for (; j <= i; j++) {
		printf("%c", reverseComplement[j]);
	}
	printf(" i: %d\n", i);
	return EXIT_SUCCESS;
}