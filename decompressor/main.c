#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "proto.h"
#include "bwt.h"
#include "mtf.h"
#include "huffman.h"
#include "revzerorun.h"
#include "genint.h"

char binstr[9];
int bstrlen = 0;

int zrlen = 0;
int revzrlen = 0;
int gintlen = 0;


int len;				//to store the length of the string
int btdlen = 0;			//length of decimals


char * merge(char *s1, char *s2) {		//to merge strings s1 and s2
	int len1 = strlen(s1);			//lengths of strings
	int len2 = strlen(s2);
	char *s = (char *)malloc(sizeof(char) * (len1 + len2 + 1));		//allocate space for return string
	strcpy(s,s1);					//copy first string to return string
	strcat(s, s2);					//concatenate second string to return string

	free(s1);						//free original strings known to allocated dynamically
	free(s2);
	s[len1+len2] = 0;				//add null character
	
	return s;
}

int main(void){
	FILE *fdc = fopen("decompi.txt", "w");
	FILE *f = fopen("compi.bin","rb");
	
	char *read;
	char *decomp = (char *)malloc(sizeof(char));
	decomp[0] = 0;
	
	int i, ignore, len = 0;
	unsigned char ch;

	huffman(f);

	int scpos = ftell(f);					//starting position of the file pointer before compressed text
	
	fseek(f, -(sizeof(char)), SEEK_END);		//to place cursor before the last character in the file
	fread(&ignore, sizeof(char), 1, f);
	fseek(f, scpos, SEEK_SET);					//to go back to beginning of compressed data

	int r = 0;

	while(fread(&ch, sizeof(char), 1, f)) {
		++r;
		len++;
		read = dtb(ch, 2);						//convert integer to binary number
		read[7] = 0;
		decomp = merge(decomp, read);			//store all binary numbers to get huffman code
	}
	

	int *nos = genint(decomp, strlen(decomp), ignore);
	for(i = gintlen-1 ; !nos[i] ; i--);
	gintlen = i + 1;									//to find number of integers generated to remove trailing 0s (if any)
	nos = (int *)realloc(nos, sizeof(int) * gintlen);	//realloc to free up the memory not required
	printf("\nGenerated ints %d\n", gintlen);
	
	nos = revzerorun(nos,gintlen);					//reverse zero-running
	printf("Zero Running Reversed\n");
	
	char *snos;
	snos = imtf(nos, revzrlen);						//reverse move-to-front
	printf("MTF Reversed\n");
	
	char * revbw = ibwt(snos, revzrlen);			//Reverse BWT to obtain original string
	printf("BWT reversed\n");

	fprintf(fdc, "%s", revbw);						//write original string to file
	fclose(fdc);								//close file stream
	free(revbw);

	return 0;
	
	//---------------------

	char c1, c2;								//to check if input and original file are same
	FILE *fc1 = fopen("comp.txt", "r");
	FILE *fc2 = fopen("decompi.txt", "r");
	while((c1 = getc(fc1)) != EOF && (c2 = getc(fc2)) != EOF)
		if(c1 != c2) {
			printf("FAILED\n");
			return 0;
		}

	fclose(fc1);
	fclose(fc2);
	printf("SUCCESS!\n");

	return 0;
}