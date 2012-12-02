#include "fasta.h"

/*
void countGC(Data d);
Data newData(char *name, char *string);
void freeData(Data d);
char readDNA(FILE *fp, char *string);
void sortData(Data *data);
void printData(Data *data);
*/

int testNewData(void) {
	int passed = 1;
	char *name = "FASTA_THAN_LIGHT";
	char *string = "ATATATGCGCGC";

	Data d = newData(name, string);
	if (strcmp(name, getName(d))!=0) {
		passed = 0;
	}
	if (strcmp(string, getString(d))!=0) {
		passed = 0;
	}
	return passed;
}

int testCountGC(void) {
	int passed = 1;
	char *name = "FASTA_THAN_LIGHT";
	char *string = "ATATATGCGCGC"; // 3 A's, 3 T's, 3 G's, 3 C's

	Data d = newData(name, string);
	if (getTotal(d) != 12) {
		passed = 0;
	}

	if (getGC(d) != 6) {
		passed = 0;
	}

	if (getPercentGC(d) != 50.0) {
		passed = 0;
	}
	return passed;
}

int testReadDNA(void) {
	int passed = 1;
	FILE *fw = fopen("./test", "w");
	fprintf(fw, ">Monocoque\nAAAAATATATATATATATATATAATT");
	fclose(fw);
	FILE *fp = fopen("./test", "r");
	char *string = malloc(10000);

	if (readDNA(fp, string) != '>') {
		passed = 0;
	}	
	char *buffer = malloc(100);
	fscanf(fp, "%s\n", buffer);

	printf("\n");
	readDNA(fp, string);

	buffer = "AAAAATATATATATATATATATAATT";
	if (strcmp(buffer, string) != 0) {
		printf("%s\n%s\n", buffer, string);
		passed = 0;
	}
	return passed;
}

int testSortDNA(void) {
	int passed = 1;
	char *name1 = "FASTA_THAN_A_SPEEDING_BULLET";
	char *string1 = "ATGCATGCATGCATGC"; // 4 of each
	char *name2 = "FASTA_THAN_LIGHT";
	char *string2 = "GCGCGCGCAT"; //8GC, 2AT
	char *name3 = "NOT_FASTA_AT_ALL";
	char *string3 = "ATATATATATAATATTTTA"; // No GC
	Data *array = malloc(sizeof(Data)*10);
	array[0] = newData(name1, string1);
	array[1] = newData(name2, string2);
	array[2] = newData(name3, string3);
	array[3] = NULL;
	sortData(array);
	if (strcmp(array[0]->name, ))
}

int main (void) {
	if (testNewData() == 0) {
		printf("Failed testNewData\n");
	}
	if (testCountGC() == 0) {
		printf("Failed testCountGC\n");
	}
	if (testReadDNA() == 0) {
		printf("Failed testReadDNA\n");
	}
	if (testSortDNA() == 0) {
		printf("Failed testSortDNA\n");
	}

	else {
		printf("All tests passed! YOU ARE AWESOME!\n");
	}
	return EXIT_SUCCESS;
}