#ifndef _CONDEF_H
#define _CONDEF_H


#define SAFE_DELETE_OBJ(OBJ) {if(NULL!=OBJ){delete OBJ;OBJ=NULL;}}
#define SAFE_FREE_BUF(OBJ) {if(NULL!=OBJ){free(OBJ);OBJ=NULL;}}

#endif