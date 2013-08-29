#include "fasta.h"


struct _fasta {
	char *name;
	char *string;
	int gc;
	int total;
	double gcPercent;
};

char *getName(Data d) {
	return d->name;
}

char *getString(Data d) {
	return d->string;
}

int getTotal(Data d) {
	return d->total;
}

int getGC(Data d) {
	return d->gc;
}

double getPercentGC(Data d) {
	return d->gcPercent;
}

void printFasta(Data d) {
	printf("Name: %s\nString: %s\nGC: %d\tTotal: %d\nPercent: %0.6f\n", d->name, d->string, d->gc, d->total, d->gcPercent);
}

void countGC(Data d) {
	int i;
	int gcCount = 0;
	int totalCount = 0;
	for (i = 0; d->string[i] != '\0'; i++) {
		if (d->string[i] == 'A' || d->string[i] == 'T') {
			totalCount++;
		} else if (d->string[i] == 'G' || d->string[i] == 'C') {
			totalCount++;
			gcCount++;
		}
	}
	d->total = totalCount;
	d->gc = gcCount;
	if(totalCount == 0) {
		printf("Total = 0, dividing by 0\n");
		printf("Full string here: %s\n", d->string);
	}
	double gcPercent = ((double)gcCount/(double)totalCount)*100;
	d->gcPercent = gcPercent;
}

Data newData(char *name, char *string) {
	Data d = malloc(sizeof(struct _fasta));
	d->name = malloc(sizeof(char)*15);
	d->string = malloc(sizeof(char)*MAX_BP);
	d->gc = 0;
	d->total = 0;
	d->gcPercent = 0.0;
	d->name = name;
	d->string = string;
	countGC(d);
	return d;
}

void freeData(Data d) {
	free(d->name);
	free(d->string);
	free(d);
}

char readDNA (FILE *fp, char *string, char *name) {
	string[0] = '\0';
	if (fgetc(fp) == '>') {
		fscanf(fp, "%s\n", name);
	}
	while(TRUE) {
		char current = fgetc(fp);
		if (current == 'A' || current == 'T' || current == 'C' || current == 'G') {
			int i;
			for (i = 0; string[i] != '\0'; i++) {
				// search forward
			}
			string[i] = current;
		} else if (current == '>') {
			ungetc(current, fp);
			return current;
		}
		if (current == EOF) {
			return current;
		}
	}
}

void sortData (Data *data) {
	int i, j;
	int length = 0;
	// find length of data
	while (data[length] != NULL) {
		length++;
	}
	for (i = 0; i < length - 1; i++) {
		int largestIndex = i;
		for (j = i; j < length; j++) {
			if (data[j]->gcPercent > data[largestIndex]->gcPercent) {
				largestIndex = j;
			}
		}
		// once largest index is found, move it to i and everything behind it up one
		Data temp = data[largestIndex];
		int k;
		for(k = largestIndex; k > i; k--) {
			data[k] = data[k-1];
		}
		data[i] = temp;
	}
}

/*
void sortData (Data *data) {
	int i = 0; 
	int length = 0;
	int min = 0;
	while (data[length] != NULL) {
		length++;
	}
	printf("length: %d\n", length);
	int j;
	for (j = 0; j < length - 1; j++) {
		min = j;
		for (i = 0; i < length; i++) {
			if (data[i]->gcPercent < data[min]->gcPercent) {
				min = i;
			}
		}
		if (min != j) {
			Data temp = data[j];
			data[j] = data[min];
			data[min] = temp;
		}
	}
}
*/

void printData (Data *data) {
	int i = 0;

	for (i = 0; data[i] != NULL; i++) {
		printf("%s\n%0.6f\n", data[i]->name, data[i]->gcPercent);
	}

}

int main (int argc, char *argv[]) {
	FILE *fp = NULL;

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

	Data *database = malloc(sizeof(Data)*11);
	database[10] = NULL;
	int i = 0;
	
	char *currentString;
	char *currentName;

	while (TRUE) {
		currentString = malloc(sizeof(char)*MAX_BP);
		currentName = malloc(sizeof(char)*32);

		char ret = readDNA(fp, currentString, currentName);
		
		database[i] = newData(currentName, currentString);
		i++;
		if (ret == EOF) {
			break;
		}
	}
	database[i] = NULL;

	sortData(database);
	printData(database);

	return EXIT_SUCCESS;
}
