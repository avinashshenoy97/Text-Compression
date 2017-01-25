#include "proto.h"
#include "btd.h"

int con[8];			//to store converted to binary		

/*To convert characters into integers*/
int *convert(char *bin)
{
	int h;
	for(h=0; h<8; h++)
	con[h]=bin[h]-'0';
	return con;
}

int btd(char* num, int count)
{
	//int ret;
	int i=0, dec=0;
	int j,k,m,r,z;
	int *n;
	char bin[8];
/*To calculate the length of the string*/
	//count = strlen(num);
	for(j=0; j<count;)
	{
		for(k=0; k<8&&j<count; k++,j++)
			bin[k]=num[j];
		for(;k<8;k++)
			bin[k]='0';                 //Adding zeros to the remaining bits of the byte
		
		n = convert(bin);
		
		for(m=0,z=7; m<8; m++,z--)
			dec+=n[z]*pow(2,m);        //To convert binary number to a decimal number

		//ret = (int *)realloc(ret, sizeof(int) * (btdlen+1));
		//ret[btdlen++] = dec;
		//printf("%d",dec);
		//printf(",");
		//dec=0;
	}

	return dec;
}
/*void main()
{
 char num[]={'0','1','1','0','0','0','1','0','1','1','\0'};
 int *a = btd(num);

 int i;
 for(i = 0 ; i < len ; i++)
 	printf("%d ", a[i]);
}*/