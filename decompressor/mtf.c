#include "proto.h"
#include "mtf.h"
				
char *imtf(int *arr, int len) {
	int i, j;
	int asc[128];							//to store ASCII characters
	char *s = (char *)malloc(sizeof(char) * (len+1));	//allocate space to return
	
	int rank;

	for(i = 0 ; i < 128 ; i++)
		asc[i] = i;

	for(i = 0 ; i < len ; i++) {
		rank = arr[i];					//store rank of each ASCII character, i.e, index in MTF
		s[i] = asc[rank];				//store ASCII character itself in string

		for(j = rank ; j > 0 ; j--)
			asc[j] = asc[j-1];			//shift all elements forward

		asc[0] = s[i];					//insert in front of MTF array
	}
	i = 0;
	s[len] = 0;							//add null character to return string

	return s;
}
