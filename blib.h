#ifndef _BDD_LIB_

#define _BDD_LIB_

#include<cudd.h>


/*Only Apply function can be used from this header file. Dont use any other functions from this header file */

/*This function takes three arguments:
op: operations are bAnd, bOr, bXor, bXnor
f, g are operands*/
DdNode *Apply(DdManager *manager,DdNode *(*op)(DdManager *,DdNode *,DdNode *),DdNode *f,DdNode *g);

/*this should not be used other than while calling Apply function above. 
this is used to perform AND operation by Apply function in base case. 
so this is custimezed for that operation only.*/
DdNode *bAnd(DdManager *manager,DdNode *f,DdNode *g);

/*this should not be used other than while calling Apply function above. 
this is used to perform OR operation by Apply function in base case. 
so this is custimezed for that operation only.*/
DdNode *bOr(DdManager *manager,DdNode *f,DdNode *g);

/*this should not be used other than while calling Apply function above. 
this is used to perform XOR operation by Apply function in base case. 
so this is custimezed for that operation only.*/
DdNode *bXor(DdManager *manager,DdNode *f,DdNode *g);

/*this should not be used other than while calling Apply function above. 
this is used to perform XNOR operation by Apply function in base case. 
so this is custimezed for that operation only.*/
DdNode *bXnor(DdManager *manager,DdNode *f,DdNode *g);
DdNode *ExistAnd(DdManager *manager,DdNode *f,DdNode *g,DdNode *cube);
DdNode *ExistAndRename(DdManager *manager,DdNode *f,DdNode *g,DdNode *cube,const int *rename);


#endif
