#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct node {	//for frequency table
	int ele;
	int freq;
};

struct bstnode {			//for bst
	int ele;
	struct bstnode *left;
	struct bstnode *right; 
	char *s;				//for huffman code
};

struct treenode {			//for huffman tree
	int ele;
	int freq;
	int pos;				//0 for left traversal and 1 for right traversal
	struct treenode *left;
	struct treenode *right; 
};


typedef struct node node;
typedef struct treenode treenode;
typedef struct bstnode bstnode;

extern bstnode *bstroot;				//root of BST
extern treenode *huffroot;

void sortpq (node **arr,int len);
void preorder (bstnode *root);
void addtobst (treenode *leaf , bstnode *root);
void addhuffcode (bstnode *root,int e,char *s);
bstnode * createbst (treenode **leaves,bstnode *bstroot,int count);
char * dtb (int s, int o);
void genhuffcode (treenode *root , int s , bstnode *bstroot);
void huffman (FILE *fop);
char * search(bstnode *root, int n,char *bstr);
void clearTree(void *vroot, short o);

#endif