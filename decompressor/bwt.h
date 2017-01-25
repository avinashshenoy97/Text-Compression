#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifndef BWT_H
#define BWT_H

struct lfnode{
	char s;
	int rank;
};

struct circnode {
	char c;
	struct circnode *prev, *next;
};

typedef struct lfnode lfnode;
typedef struct circnode circnode;

extern lfnode **lfmap;
extern circnode *start;
extern circnode **rot , **rot1;
extern lfnode *firchar;

void insert(char c);
void clearAll();
void generateRot();
char *stringify(circnode *p);
void quickSort(int f, int r);
int findrot(circnode **rot, circnode *s);
char *bwt(char *ip, int o);
char *ibwt(char *ip, int len);

#endif