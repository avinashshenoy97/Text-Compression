#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifndef PROTO_H
#define PROTO_H

#include "bwt.h"
#include "mtf.h"
#include "zerorun.h"
#include "huffman.h"
#include "btd.h"
#include "genint.h"
#include "revzerorun.h"

extern char binstr[9];
extern int bstrlen;

extern int zrlen;
extern int revzrlen;
extern int gintlen;


extern int len;				//to store the length of the string
extern int btdlen;			//length of decimals

#endif