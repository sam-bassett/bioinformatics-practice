#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
	FILE *fp = fopen("./test", "w");
	int i = 0;
	while (1) {
		fprintf(fp, "ab c\n");
		i++;
		if (i == 100) {
			break;
		}
	}
	fclose(fp);
	fp = fopen("./test", "r");
	while (!feof(fp)) {
		char *buffera = malloc(sizeof(char) * 16);
		char *bufferb = malloc(sizeof(char) * 16);
		fscanf(fp, "%s %s\n", buffera, bufferb);
		printf("%s %s\n", buffera, bufferb);
	}
	printf("size of ptr: %lu\n", sizeof(int *));
	return 1;
}