#ifndef _CONDEF_H
#define _CONDEF_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DELETE_OBJ(OBJ) {if(NULL!=OBJ){delete OBJ;OBJ=NULL;}}
#define SAFE_FREE_BUF(OBJ) {if(NULL!=OBJ){free(OBJ);OBJ=NULL;}}

#endif