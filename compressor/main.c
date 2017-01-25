#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "proto.h"
#include "bwt.h"
#include "mtf.h"
#include "zerorun.h"
#include "huffman.h"
#include "btd.h"
#include "revzerorun.h"
#include "genint.h"

char binstr[9];
int bstrlen = 0;

int zrlen = 0;
int revzrlen = 0;
int gintlen = 0;


int len;				//to store the length of the string
int btdlen = 0;			//length of decimals


char * merge(char *s1, char *s2) {
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	char *s = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	//printf("hi\n");
	strcpy(s,s1);
	//printf("hi\n");
	strcat(s, s2);
	//printf("hello\n");
	free(s1);
	free(s2);
	s[len1+len2] = 0;
	//printf("freed\n");
	return s;
}

char *charify(int *arr,int len){
	char *s = (char *)malloc(sizeof(char)*(len + 1));
	int i;
	for(i = 0 ; i < len ; i++){
		s[i] = arr[i];
	}
	s[i] = 0;
	free(arr);
	return s;
}	

int main(void){
	//char s[] = "apple\0";
	//slen = strlen(s);
	int i;
	int x, dec;
	char *s = (char *)malloc(sizeof(char));
	int lines = 0;
	char ch = 0;
	unsigned char ch1;
	//char fnam[20];
	//printf("Enter file name : \n");
	//gets(fnam);
	FILE *f = fopen("comp.txt", "r");
	FILE *fop = fopen("compi.bin", "wb");

	//while(ch != EOF) {
		while((ch = getc(f)) != EOF) {
			len++;
			s = (char *)realloc(s, sizeof(char) * len);
			s[len-1] = ch;
			if(ch == '\n')
				lines++;

			if(ch < 0 || ch > 127) {
				printf("read error %d %d %c\n", lines, ch, ch);
				getchar();
			}

			//if(lines == 100) {
			//	lines = 0;
			//	break;
			//}
		}
		s[len++] = '\0';
		//printf("%s\n", s);

		char *bw = bwt(s, 1);
		//printf("BWT %d %s\n", len, bw);

		//for(i = 0 ; i < len ; i++)
			//printf("%c", bw[i]);
		//printf("\n");
		////getchar();
		
		int *mt = mtf(bw, len);

		//free(bw);

		/*for(i = 0 ; i < len ; i++)
			printf("%d ", mt[i]);
		printf("\n");
		getchar();*/

		printf("DONE mtf\n");
		int *zr = zerorun(mt, len);
		//free(mt);
		printf("DONE zr %d\n", zrlen);
		//getchar();
		int loczr[zrlen];

		for(i = 0 ; i < zrlen ; i++) {
			loczr[i] = zr[i];
			//printf("%d ", loczr[i]);
		}
		//printf("\n"); getchar();
		
		/*printf("%d\n", zrlen);*/ //0 101 0 108 0 112 1 100 

		huffman(zr, zrlen, fop);
		//preorder(bstroot);
		printf("Done Huffman\n");
		free(zr);
		char *bstr;
		int w = 0;

		//bstr = (char *)malloc(sizeof(char));

		for(i = 0 ; i < zrlen ; i++) {
			bstr = search(bstroot, loczr[i],bstr);

			for(x = 0 ; bstr[x] ; x++) {
				binstr[bstrlen++] = bstr[x];
				if(bstrlen == 7) {
					binstr[bstrlen] = 0;
					//printf("binstr %s\n", binstr);
					dec = btd(binstr, bstrlen);
					bstrlen = 0;
					printf("%d\n",dec);
					//if(dec == 255) //getchar();
					fwrite(&dec, sizeof(char), 1, fop);
					++w;
				}
			}

			free(bstr);
		}
		printf("done search\n");

		
		//int *nos = btd(bstr);
		printf("DONE btd\n");

		//printf("%s\n", bstr);

		/*for(i = 0 ; i < btdlen ; i++){
			
		}

		blen = 1;
		btdlen = 0;
		zrlen = 0;
		start = NULL;
		rot = NULL;
		rot1 = NULL;
		bstroot = NULL;*/
	//}
	
	if(bstrlen) {
		binstr[bstrlen] = 0;
		//printf("binstr %s\n", binstr);
		dec = btd(binstr, bstrlen);
		printf("%d\n",dec);
		fwrite(&dec, sizeof(char), 1, fop);
		w++;
	}

	//printf("written %d\n", w); //getchar();
	int ignore = ((7-bstrlen) < 7) ? (7-bstrlen) : 0 ;
	fwrite(&ignore, sizeof(char), 1, fop);		//bits to ignore
	printf("IGNORE %d\n", ignore);
	//printf("Ignore %d\n", ((7-bstrlen) < 7) ? (7-bstrlen) : 0);

	fclose(f);
	fclose(fop);

	printf("%d\n", lines);

	//return 0;

	//clearTree(bstroot, 2);
	//clearTree(huffroot, 1);

	return 0;

	FILE *fdc = fopen("decomp.txt", "w");
	f = fopen("Indiacomp.bin","rb");
	
	char *read;
	char *decomp = (char *)malloc(sizeof(char));
	decomp[0] = 0;
	
	len = 0;

	int a;
	node b;
	fread(&a, sizeof(int), 1, f);
	printf("count %d\n", a);
	for(i = 0 ; i < a ; i++)
		fread(&b, sizeof(node), 1, f);

	int scpos = ftell(f);					//starting position of the file pointer before compressed text
	printf("scpos %d\n", scpos);
	fseek(f, -(sizeof(char)), SEEK_END);		//to place cursor before the last character in the file
	fread(&ignore, sizeof(char), 1, f);
	printf("ignore %d\n", ignore);
	fseek(f, scpos, SEEK_SET);					//to go back to beginning of compressed data
	printf("%d\n", ftell(f));
	int r = 0;
	

	while(fread(&ch, sizeof(char), 1, f)) {
		//printf("%ld\n", ftell(f));
		++r;
		ch1 = ch;
		printf("E loop %d\n", ch1);
		printf("%ld\n\n", ftell(f));
		len++;
		read = dtb(ch1, 2);
		read[7] = 0;
		//printf("done dtb : %s\n", read);
		decomp = merge(decomp, read);
		//printf("len %d\n", len);
	}
	//printf("read %d\n", r); //getchar();
	//printf("%c\t%d\t%d\t%d\n",(unsigned char)ch,(unsigned)ch,ch,i++);
	//printf("DECOMP %s\n",decomp);

	//printf("Before gen ints\n");
	int *nos = genint(decomp, strlen(decomp), ignore);
	for(i = gintlen-1 ; !nos[i] ; i--);
	gintlen = i + 1;
	nos = (int *)realloc(nos, sizeof(int) * gintlen);

	printf("\nGenerated ints %d\n", gintlen); //getchar();
	for(i = 0 ; i < gintlen ; i++){
		if(nos[i] != loczr[i]) {
			printf("GINT PROBLEM\n");
			printf("\a\a\a\a\a\a\a\a\a");
			getchar();
		}
		printf("%d ",nos[i]);
	}
	nos = revzerorun(nos,gintlen);
	printf("unZR\n");
	for(i = 0 ; i < revzrlen ; i++){
		if(nos[i] != mt[i]) {
			printf("RZR PROBLEM\n");
			printf("\a\a\a\a\a\a\a\a\a");
			getchar();
		}
		//printf("%d ",nos[i]);
	}
	//printf("\n");
	//char *snos = charify(nos,revzrlen);
	char *snos;
	/*for(i = 0 ; i < revzrlen ; i++){
		printf("%c\t",snos[i]);
	}*/
	//printf("Rev ZR charred\n");
	//free(nos);
	printf("freed nos\n");
	snos = imtf(nos, revzrlen);
	printf("Un MTDed\n");
	for(i = 0 ; i < revzrlen ; i++){
		if(snos[i] != bw[i]) {
			printf("iMTF PROBLEM\n");
			printf("\a\a\a\a\a\a\a\a\a");
			getchar();
		}
		printf("%c ",snos[i]);
	}
	////getchar();
	//printf("\n");
	
	////getchar();
	/*printf("hey" );
	for(i = 0 ; i < revzrlen ; i++){
		printf("%d\t",nos[i]);
	}
	printf("\n");*/
	//snos = charify(nos,revzrlen);
	//printf("MTF ints charred\n");
	//printf("%s\n",snos);
	//free(nos);
	char * revbw = ibwt(snos);
	printf("UnBWTed %s\n", revbw);

	fprintf(fdc, "%s", revbw);
	fclose(fdc);
	free(revbw);

	char c1, c2;
	FILE *fc1 = fopen("India.txt", "r");
	FILE *fc2 = fopen("decomp.txt", "r");
	while((c1 = getc(fc1)) != EOF && (c2 = getc(fc2)) != EOF)
		if(c1 != c2) {
			printf("FLOP\n");
			break;
		}

	fclose(fc1);fclose(fc2);
	printf("show\n");

	return 0;
}