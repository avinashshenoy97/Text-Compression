#include "proto.h"
#include "zerorun.h"

int * zerorun (int * arr,int len){                   //zerorun is a function that takes two parameters, an integer array and the length of the array
	int *arr2 = (int *)malloc(sizeof(int)*(len*2));  //dynamically allocate memory for the final array to be returned
	int i , count , p = 0,j , countzer = 0;
	for(i = 0 ; i < len ;i++){
		count = 0;
		if( arr[i] != 0 ){                           // if a number is non zero , replace the number by the number of zeros preceeding it and the number itself
			for(j = i-1; j >= 0 ; j--){
				if(arr[j] == 0){
					count++;
				}
				else{
					break;
				}
			}
			arr2[p] = count;
			arr2[p+1] = arr[i];
			p += 2;                                 //p is the index of the final array
		}
	}
	count = 0;

	for(i = len-1 ; i >= 0 ; i--){
		if(!arr[i])
			count++;
		else
			break;
	}

	if(count)
		arr2[p++] = count;

	if(p != len*2){									//if all the memory allocated to the final array is not being used, reallocate the array
		arr2 = (int *)realloc(arr2,sizeof(int)*p);
	}

	zrlen = p;				//length of zero run array
	return arr2;
}
