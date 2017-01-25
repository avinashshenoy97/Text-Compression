#include "proto.h"
#include "revzerorun.h"

//int count=6;          
int *revzerorun(int *arr, int count)
{
 int len=0;
 //int c=count;
 int j, i;
 int *arr2;
 arr2=(int*)malloc(sizeof(int));
 for(i=0, j=0; j<count; j++)
{
 len += arr[j];
 arr2=(int *)realloc(arr2,sizeof(int)*(len));
 
 while(arr[j]!=0)
  {   
   arr2[i++]=0;    //Replacing the even indexed positions of the array,arr with zeroes in the array,arr2 specified by the number at that position
   arr[j]--;
   //printf("Zeroing %d\n", arr[j]+1);
  } 
  if((j+1) < count) {
   arr2=(int *)realloc(arr2,sizeof(int)*(++len));
   arr2[i++]=arr[++j];                           //Copying the number at the odd indexed positions of the array,arr to the array,arr2
   //printf("Numbering %d\n", arr[j]);
  }

  //printf("%d %d ", arr2[i-1], arr2[i-2]);
}
//rintf("\n%d\n", len);
revzrlen = len;

//for(i = 0 ; i < len ; i++)
	//printf("%d ", arr2[i]);
//printf("\n");

free(arr);

return arr2;
}

/*void main()
{
 int k;
 int *b;
 int a[]={3,4,5,4,1,2};
 b=revzerorun(a);
 for(k=0; k<12; k++)
   printf("%d",b[k]);
}*/
 
