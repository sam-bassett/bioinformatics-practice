#include <stdlib.h>
#include <stdio.h>

int recurse (int f1, int f2, int months, int litterSize) {
    if (months == 0) {
        return f1+f2;
    } else {
        int rabbits = 

int rabbits(int n, int k) {
    if (n > 40 || k > 5) {
        fprintf(stderr, "n or k out of range\n");
        return -1;
    }
    int numRabbits = recurse(1, 1, n, k);
    return numRabbits;
}

int main (int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Usage: %s months litterSize\n", argv[0]);
        exit(0);
    }
    int numRabbits = rabbits(argv[1], argv[2]);
    printf("%d\n", numRabbits);
    exit(1);
}
