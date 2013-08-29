#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define A 0
#define U 1
#define C 2
#define G 3

#define NO_AA 'B'
#define STOP 'Z'

typedef struct _treeNode *Tree;

struct _treeNode {
	char aaCode;
	Tree *leaves;
	int level; // of 3, corresponds to codon location
};

Tree createTree(int level) {
	if (level > 3) {
		return NULL;
	} else {
		Tree node = malloc(sizeof(struct _treeNode));
		node->aaCode = NO_AA;
		node->leaves = malloc(sizeof(Tree)*4);
		node->level = level;
		int i;
		for (i = 0; i < 4; i++) {
			node->leaves[i] = createTree(level+1);
		}
		return node;
	}
}

// maybe put all the protein codes in a tree? read in from a file, 
// store as a tree of max order 4. This makes reading in less hard-coded, 
// and is good to practise - I want to know that I can actually remember 
// a tree. 

// first focus on getting everything in the tree so it works. then optimise,
// so you don't have to traverse all the way down to the 3rd letter to get 
// V from GUx. (for example)

void insertIntoTree (Tree t, char *codon, char *aaCode) {
	// abstract data structures? nah, who uses them?
	if (t->level == 3) {
		t->aaCode = aaCode[0];
	} else if (t->level < 3) {
		char currCodon = codon[t->level];
		if (currCodon == 'A') {
			insertIntoTree(t->leaves[A], codon, aaCode);
		} else if (currCodon == 'U') {
			insertIntoTree(t->leaves[U], codon, aaCode);
		} else if (currCodon == 'C') {
			insertIntoTree(t->leaves[C], codon, aaCode);
		} else if (currCodon == 'G') {
			insertIntoTree(t->leaves[G], codon, aaCode);
		} else {
			printf("Incorrect codon, exiting\n");
			exit(EXIT_FAILURE);
		}
	}
}

Tree createAndPopulateTree (FILE *fp) {
	// requires an infile with format: 
	// CODON AMINOACID (or STOP)\n	
	Tree t = createTree(0);
	if (fp == NULL) {
		fprintf(stderr, "No file found, tree not populated\n");
		exit(EXIT_FAILURE);
	}
	if (t == NULL) {
		fprintf(stderr, "Tree not initialised, stopping...\n");
		exit(EXIT_FAILURE);
	}

	while (!feof(fp)) {
		char *codon = malloc(sizeof(char)*8);
		char *aaCode = malloc(sizeof(char)*8);
		fscanf(fp, "%s %s\n", codon, aaCode);
		if (codon == NULL || aaCode == NULL) {
			printf("Error : codon or aacode == NULL\n");
			exit(EXIT_FAILURE);
		}
		insertIntoTree(t, codon, aaCode);
	}
	return t;
}

char getAACode (Tree t, char *codon) {
	char aa = '~';
	if (t->level == 3) {
		return t->aaCode;
	} else if (t->level < 3) {
		char currCodon = codon[t->level];
		if (currCodon == 'A') {
			aa=getAACode(t->leaves[A], codon);
		} else if (currCodon == 'U') {
			aa=getAACode(t->leaves[U], codon);
		} else if (currCodon == 'C') {
			aa=getAACode(t->leaves[C], codon);
		} else if (currCodon == 'G') {
			aa=getAACode(t->leaves[G], codon);
		} else {
			printf("\nIncorrect codon: %c, exiting\n", currCodon);
			printf("Entire string: %s\n", codon);
			exit(EXIT_FAILURE);
		}
	}
	return aa;
}

void printTree(Tree t, int level, char *codon) {
	if (level == 3) {
		printf("%s = %c\n", codon, t->aaCode);
	} else {
		codon[level] = 'A';
		printTree(t->leaves[A], level+1, codon);
		codon[level] = 'U';
		printTree(t->leaves[U], level+1, codon);
		codon[level] = 'C';
		printTree(t->leaves[C], level+1, codon);
		codon[level] = 'G';
		printTree(t->leaves[G], level+1, codon);
	}
}

int main (int argc, char *argv[]) {
	FILE *fpTree, *fpAcid;
	if (argc == 3) {
		fpTree = fopen(argv[1], "r");
		fpAcid = fopen(argv[2], "r");
	} else {
		printf("Usage: %s codonFile aaFile\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	Tree t = createAndPopulateTree(fpTree);
	
	char *codon = malloc(sizeof(char)*4);
	while (!feof(fpAcid)) {
		int i;
		for (i = 0; i < 3; i++) {
			codon[i] = fgetc(fpAcid);
		}
		codon[3] = '\0';
		char aa = getAACode(t, codon);
		if (aa == STOP) break;
		printf("%c", aa);
	}
	printf("\n");
	return EXIT_SUCCESS;
}



