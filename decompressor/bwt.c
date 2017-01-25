#include "proto.h"
#include "bwt.h"

lfnode **lfmap = NULL;
circnode *start = NULL;		//start of circularly linked list
circnode **rot = NULL, **rot1 = NULL;		//to store all rotations of the string and for quickSort

lfnode *firchar = NULL;

void insert(char c) {	//to create a circnode in the circularly linked list
	circnode *new = (circnode *)malloc(sizeof(circnode));
	new->c = c;

	if(start == NULL) {
		start = new;
		new->prev = start;
	}
	else {
		circnode *temp = start;
		while(temp->next != start)
			temp = temp->next;

		temp->next = new;
		new->prev = temp;
	}

	new->next = start;
	start->prev = new;
}

void clearAll() {					//clears all dynamically allocated memory in this segment of the program
	circnode *temp = start->next;
	circnode *temp2 = temp->next;

	while(temp2->next != start) {
		free(temp);
		temp = temp2;
		temp2 = temp2->next;
	}

	free(start);
	free(temp);
	free(temp2);

	start = NULL;
}

void generateRot() {		//to generate all rotations of the string
	int i = 1;
	circnode *temp = start->next;
	rot = (circnode **)malloc(sizeof(circnode *) * len);
	rot1 = (circnode **)malloc(sizeof(circnode *) * len);
	rot[0] = start;

	while(temp != start) {
		rot[i++] = temp;
		temp = temp->next;
	}
}

int compare(circnode *p, circnode *nod) {
	int i = 0;
	while(i < len) {
		if(nod->c - p->c)
			return (nod->c - p->c);
		else {
			nod = nod->next;
			p = p->next;
			++i;
		}
	}

	return 0;
}

int scount = 0;
void quickSort(int f, int r) {		//front and rear passed as parameters
	if(f == r || f < 0 || r >= len || r < f)
		return;

	int pivot = r;
	int i = f, j = r, k;						//loop variables
	circnode *p = rot[pivot];				//pivot element

	for(k = f ; k < r ; k++) {
		if( compare(p, rot[k]) > 0 )		//similar to strcmp for circular linked list
			rot1[j--] = rot[k];
		else
			rot1[i++] = rot[k];
	}

	rot1[i] = rot[pivot];

	for(k = f ; k <= r ; k++)
		rot[k] = rot1[k];
	

	quickSort(f, j-1);
	quickSort(j+1, r);
}

int findrot(circnode **rot, circnode *s) {		//to find s in rot
	int i;

	for(i = 0 ; i < len ; i++) {
		if(!compare(rot[i], s))
			return i;
	}

	return 0;
}

char *ibwt(char *ip, int len) {
	int i, j, asc[128] = {0};
	lfmap = (lfnode **)malloc(sizeof(lfnode *) * 2);	//allocate memory for LF map

	for(i = 0 ; i < 2 ; i++){
		lfmap[i] = (lfnode *)malloc(sizeof(lfnode) * len);	
	}

	for(i = 0 ; i < len ; i++) {
		asc[ip[i]]++;				//frequency table
	}

	int k;
	j = 0;
	for(i = 0 ; i < 128 ; i++) {
		for(k = 0 ; k < asc[i] ; k++)
			lfmap[0][j++].s = i;			//generate F of LF map
	}

	for(i = 0 ; i < len ; i++)
		lfmap[1][i].s = ip[i];				//generate L of LF map
	

	for(i = 1 ; i >= 0 ; i--){				//generate ranks in LF map
		for(j = 0; j < 128 ; j++){
			asc[j] = 0;
		}
		for(j = 0 ; j < revzrlen ; j++){
			lfmap[i][j].rank = asc[lfmap[i][j].s]++;
		}
	}
	
	char *s = (char *)malloc(sizeof(char) * revzrlen);		//return string
	lfnode *ch = (lfnode *)malloc(sizeof(lfnode));			//temporary LF node
	int jump = 0, temp, rank;
	lfnode *firstchar = (lfnode *)malloc(sizeof(lfnode));
	firstchar->s = lfmap[0][jump].s;
	firstchar->rank = lfmap[0][jump].rank;
	
	int p = 0;

	ch->s = lfmap[1][0].s;
	ch->rank = lfmap[1][0].rank;
	while(ch) {							//reversing the BWT using LF mapping
		if(ch->s == firstchar->s){		//property of LF map
			break;
		}
		s[p++] = lfmap[0][jump].s;		//obtain next character in string
		ch->s = lfmap[1][jump].s;			//take character from L
		ch->rank = lfmap[1][jump].rank;		//store it's rank

		rank = lfmap[1][jump].rank;			//rank store seperately for jumping

		
		jump = 0;
		for(k = 0 ; k < ch->s ; k++)		//find location of ch->s in F column
			jump += asc[k];
		
		jump += rank;						//add rank to find location of ch->s in F
	}

	for(i = 0 ; i < revzrlen/2 ; i++) {		//reverse the string as it is generated in reverse as per algorithm
		temp = s[i];
		s[i] = s[revzrlen-i-1];
		s[revzrlen-i-1] = temp;
	}
	s[revzrlen] = 0;					//putting null character in return string

	return s;
	
}