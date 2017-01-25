#include "proto.h"
#include "bwt.h"

lfnode **lfmap = NULL;
circnode *start = NULL;		//start of circularly linked list
circnode **rot = NULL, **rot1 = NULL;		//to store all rotations of the string and for quickSort

lfnode *firchar = NULL;

void insert(char c) {	//to create a circnode in the circularly linked list
	circnode *new = (circnode *)malloc(sizeof(circnode));
	new->c = c;

	//printf("insert malloc %c %p\n", c, new);

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

void clearAll() {
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
	//printf("%c\n", rot[0]->c);
	while(temp != start) {
		rot[i++] = temp;
		//printf("%c\n", rot[i-1]->c);
		temp = temp->next;
	}
}

char *stringify(circnode *p) {		//to generate the string from the circularly linked list given the starting circnode
	//printf("stringifying\n");
	circnode *temp = p->next;
	char *ret = (char *)malloc(sizeof(char) * len);
	int i = 1;
	ret[0] = p->c;
	//printf("%c ", p->c);

	while(temp != p) {
		//printf("%c ", temp->c);
		ret[i++] = temp->c;
		temp = temp->next;
	}
	//printf("\n");

	return ret;
}

int compare(circnode *p, circnode *nod) {
	int i = 0;
	while(i < len) {
		//printf("comp %c %c\n", nod->c, p->c);
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
	//printf("%d %d\n", f, r);
	//printf("%d\n", scount++);
	if(f == r || f < 0 || r >= len || r < f)
		return;

	//char *s;		//to compare strings

	int pivot = r;
	int i = f, j = r, k;						//loop variables
	//char *p = stringify(rot[pivot]);	//pivot string
	circnode *p = rot[pivot];

	for(k = f ; k < r ; k++) {
		//s = stringify(rot[k]);
		if( compare(p, rot[k]) > 0 )
			rot1[j--] = rot[k];
		else
			rot1[i++] = rot[k];

		//free(s);
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
		if(!compare(rot[i], s)) {
			//printf("i %d\n", i);
			return i;
		}
	}

	return 0;
}

char *bwt(char *ip, int o) {			//o = 1 for BWT, o = 2 for reverse BWT
	int i, ind;
	circnode **urot = NULL;

	firchar = (lfnode *)malloc(sizeof(lfnode));

	for(i = 0 ; ip[i] ; i++) {
		//printf("%d ip %c\n", i, ip[i]);
		insert(ip[i]);
		//firchar->s = ip[i];
	}

	insert(ip[i]);
	//len--;

	//len = strlen(ip) + 1;
	//printf("LEN %d\n", len);
	//int h=0;
	circnode *tempc = start->next;
	//printf("After inserts : %c\n", start->c);
	while(tempc != start) {
		//printf("%c\n", tempc->c);
		tempc = tempc->next;
		//h++;
	}
	//h++;
	//printf("%d\n",h++ );
	generateRot();
	//printf("DONE gen\n");

/*	char *ttemp = NULL;
	for(i = 0 ; i < len ; i++) {
		printf("i %d\n", i);
		ttemp = stringify(rot[i]);
		for(ind = 0 ; ind < len ; ind++)
			printf("%c", ttemp[ind]);
		printf("\n");
		free(ttemp);
	}*/
	////getchar();
	
	urot = (circnode **)malloc(sizeof(circnode *) * len);

	for(i = 0 ; i < len ; i++)
		urot[i] = rot[i];
	
	quickSort(0, len-1);
	//printf("DONE s\n");

	/*for(i = 0 ; i < len ; i++) {
		ttemp = stringify(rot[i]);
		for(ind = 0 ; ind < len ; ind++)
			printf("%c", ttemp[ind]);
		printf("\n");
		free(ttemp);
	}*/
	////getchar();
		/*for(i = 0 ; i < len ; i++)
		{
			char *s = stringify(rot[i]);
			printf("%s\n", s);
			//free(s);
		}
		printf("\n");*/
	

	free(rot1);

	/*index_list = (int *)malloc(sizeof(int) * len);

	for(i = 0 ; i < len ; i++) {
		ind = findrot(urot, rot[i]);
		ind++;
		printf("ind %d\n", ind);
		if(ind == len)
			ind = 0;

		index_list[i] = findrot(rot, urot[ind]);
	}*/

	char *s = (char *)malloc(sizeof(char) * (len+1));
	char *temp;

	lfmap = (lfnode **)malloc(sizeof(lfnode *) * 2);

	for(i = 0 ; i < 2 ; i++){
		lfmap[i] = (lfnode *)malloc(sizeof(lfnode) * len);	
	}

	//printf("assignming ranks %d\n", rot[0]->c);
	//getchar();

	for(i = 0 ; i < len ; i++) {
		//temp = stringify(rot[i]);
		lfmap[0][i].s = rot[i]->c;
		lfmap[1][i].s = (rot[i]->prev)->c;
		//printf("%c\t",lfmap[0][i].s);
		//printf("%c\n",lfmap[1][i].s);
 		s[i] = (rot[i]->prev)->c;
 		/*if(s[i] == 0) {
 			printf("BWT HAS NULL \a\n");
 			//getchar();
 		}*/
		//free(temp);
	}
	s[len] = 0;

	free(rot);
	clearAll();
	//printf("DONE bwt %s\n", s);
	return s;
}

int scompare(char *s1, char *s2, int len) {
	int i = 0;

	while(i < len) {
		if(s1[i] - s2[i])
			return (s1[i] - s2[i]);
		else
			i++;
	}

	return 0;
}
char **rots;
void sQuickSort(char **tab, int jump, int f, int r, int len) {
	if(f == r || f < 0 || r >= len || r < f)
		return;

	//char *s;		//to compare strings
	

	int pivot = r;
	int i = f, j = r, k;						//loop variables
	//char *p = stringify(rot[pivot]);	//pivot string
	char *p = tab[pivot] + jump;
	char *comp = NULL;

	for(k = 0 ; k < len ; k++)
		rots[k] = tab[k];

	for(k = f ; k < r ; k++) {
		//s = stringify(rot[k]);
		comp = tab[k] + jump;

		if( scompare(p, comp, len-jump) < 0 )
			rots[j--] = tab[k];
		else
			rots[i++] = tab[k];

		//free(s);
	}

	rots[i] = tab[pivot];

	for(k = f ; k <= r ; k++)
		tab[k] = rots[k];
	

	sQuickSort(tab, jump, f, j-1, len);
	sQuickSort(tab, jump, j+1, r, len);

}

char *ibwt(char *ip) {
	//printf("in ibwt %d\n", revzrlen);
	//getchar();
	int i, j, asc[128];
	/*for(i = 0 ; i < revzrlen ; i++){
		printf("%c %c\n",lfmap[0][i].s,lfmap[1][i].s);
	}*/
	//printf("%c %d\n",firchar->s,firchar->rank);
	for(i = 1 ; i >= 0 ; i--){
		for(j = 0; j < 128 ; j++){
			asc[j] = 0;
		}
		for(j = 0 ; j < revzrlen ; j++){
			lfmap[i][j].rank = asc[lfmap[i][j].s]++;
		}
		//printf("\n\nL :\n");
	}/*
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	for(i = 0 ; i < revzrlen ; i++){
		printf("%c %d\n",lfmap[0][i].s,lfmap[0][i].rank);
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	for(i = 0 ; i < revzrlen ; i++){
		printf("%c %d\n",lfmap[1][i].s,lfmap[1][i].rank);
	}
	printf("\n\n\n\n\n\n\n\n\n\n\n");
	*/
	char *s = (char *)malloc(sizeof(char) * revzrlen);
	lfnode *ch = (lfnode *)malloc(sizeof(lfnode));
	int k, jump = 0, temp, rank;
	lfnode *firstchar = (lfnode *)malloc(sizeof(lfnode));
	firstchar->s = lfmap[0][jump].s;
	firstchar->rank = lfmap[0][jump].rank;
	//s[0] = 0 ;
    //printf("ch : %d\n",ch->s);
	//printf("firstchar : %d\n",firstchar->s );

	/*for(i = 0 ; i < 2 ; i++){
		for(j = 0 ; j < revzrlen ; j++){
			printf("%d  %c %d %d\n", j, lfmap[i][j].s, lfmap[i][j].s,lfmap[i][j].rank );
		}
		//getchar();
		printf("HERE\n");
	}*/
	
	int p = 0;

	//getchar();
	//printf("firstchar : %d\n",firstchar->s );
	/*if(ch->s != firstchar->s && ch->rank != firstchar->rank){
		printf("hello\n");
	}*/
	//getchar();
	ch->s = lfmap[1][0].s;
	ch->rank = lfmap[1][0].rank;
	//printf("ch : %c %d\n",ch->s, ch->rank);
	while(ch) {
		if(ch->s == firstchar->s){
			break;
		}
		s[p++] = lfmap[0][jump].s;
		ch->s = lfmap[1][jump].s;
		ch->rank = lfmap[1][jump].rank;
		//printf("c : %d %d\t",ch->s, ch->rank);

		rank = lfmap[1][jump].rank;

		
		jump = 0;
		for(k = 0 ; k < ch->s ; k++)
			jump += asc[k];
		
		jump += rank;
		//printf("%c\n",s[i-1]);
		//printf(" jump : %d\n",jump);
		////getchar();
	}

	for(i = 0 ; i < revzrlen/2 ; i++) {
		temp = s[i];
		//printf("%c\n",s[i]);
		s[i] = s[revzrlen-i-1];
		s[revzrlen-i-1] = temp;
	}
	s[revzrlen] = 0;
	//printf("unbwted string from the function : %s\n", s);
	return s;
	
}