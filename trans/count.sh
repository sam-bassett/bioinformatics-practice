#!/bin/sh

cut -d' ' -f2 codons > prot
cut -d' ' -f1 codons > code

cat prot | sort | uniq | wc

rm prot code
