#include "proto.h"
#include "revzerorun.h"

        
int *revzerorun(int *arr, int count)
{
    int len=0;
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
        } 
        
        if((j+1) < count) 
        {
            arr2=(int *)realloc(arr2,sizeof(int)*(++len));
            arr2[i++]=arr[++j];                           //Copying the number at the odd indexed positions of the array,arr to the array,arr2
        }
    }

    revzrlen = len;

    free(arr);

    return arr2;
}