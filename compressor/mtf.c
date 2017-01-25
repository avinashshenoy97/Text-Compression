#include "proto.h"
#include "mtf.h"

int* mtf(char *word, int count)
{
 int i=0;
 int j,k,h,f,cpy;
 char asc[128];
/* Storing the ASCII values in a character array asc */
 for(k=0; k<128; k++)
  asc[k]=k;
/* Calculating the length of the string */ 
 /*while(word[i]!='\0')
 {
  count++;
  i++;
 }*/
/* Dynamically creating an array index */
int* index=(int*)(malloc(sizeof(int)*count));
 for(j=0; j<count; j++)
{
 for(h=0; h<128; h++)
 {
  if(word[j]==asc[h])
   {
    index[j]=h;              //Storing the index of the characters in array index
    cpy=asc[h];              //Storing the element at the index position h in cpy
    for(f=h; f>0; f--)
     asc[f]=asc[f-1];        //Moving the characters to the next position from index 0 to the index of the element 
    asc[0]=cpy;              //Moving the element to the front of the array
   }
  }
 }
 return index;               //returning the array index which contains all the indexes of the characters
}


/*void main()
{
 char word[]={'a','p','p','l','e','\0'};
 int* z=mtf(word);
 int i;
 for(i=0; i<5; i++)
 {
 printf("%d",z[i]);
}
}*/
        
char *imtf(int *arr, int len) {
  int i, j;
  int asc[128];
  char *s = (char *)malloc(sizeof(char) * (len+1));
  //printf("Allocated\n");
  int rank;

  for(i = 0 ; i < 128 ; i++)
    asc[i] = i;

  for(i = 0 ; i < len ; i++) {
    //printf("%d\n", arr[i]);
    rank = arr[i];
    //printf("Rank %d %d %c\n", rank, asc[rank], asc[rank]);
    s[i] = asc[rank];

    for(j = rank ; j > 0 ; j--)
      asc[j] = asc[j-1];

    asc[0] = s[i];
  }
  i = 0;
  s[len] = 0;
  while(s[i] != '\0'){
    //printf("%c\t",s[i]);
    i++;
  }
  //getchar();  
  return s;
}
