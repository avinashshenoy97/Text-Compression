#include "proto.h"
#include "genint.h"

int * genint (char *s, int len, int ignore){		//genint is a function that takes a string of 0s and 1s and the length of that string and returns an array of integers
	int i,j=0;
	int *arr = (int *)malloc(sizeof(int));	//dynamically allocate memory for the array of integeres that is to be returned
	treenode *temp = huffroot;

	len -= (ignore + 7);

	for(i = 0 ; i < len ; i++){

		if(s[i] == '0'){
			temp = temp->left;		//if 0 is encountered, traverse the left subtree
			if(temp->left == NULL && temp->right == NULL){	//to check if the node is a leaf node
				arr[j++] = temp->ele;
				arr = (int *)realloc(arr,sizeof(int)*(j+1));	//if yes store the value of the leaf node in the array
				temp = huffroot;			//re-assign temp to the root for finding the next leaf node
			}
		}
		else{
			temp = temp->right;		//if 1 is encountered, traverse to the right subtree
			if(temp->left == NULL && temp->right == NULL){
				arr[j++] = temp->ele;
				arr = (int *)realloc(arr,sizeof(int)*(j+1));
				
				temp = huffroot;			//re-assign temp to the root for finding the next leaf node
			}
		}
	}
	arr = (int *)realloc(arr,sizeof(int)*j);	//reallocate the memory as one extra cell is allocated
	gintlen = j;

	return arr;
}