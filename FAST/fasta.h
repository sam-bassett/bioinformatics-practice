#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_BP 1000
#define TRUE 1
#define FALSE 0

typedef struct _fasta *Data;

void countGC(Data d);
Data newData(char *name, char *string);
void freeData(Data d);
char readDNA(FILE *fp, char *string, char *name);
void sortData(Data *data);
void printData(Data *data);
void printFasta(Data fasta);

char *getName(Data d);
char *getString(Data d);
int getTotal(Data d);
int getGC(Data d);
double getPercentGC(Data d);