#ifndef _MC_
#define _MC_

#include<stdio.h>
#include<cudd.h>
#include<cuddInt.h>

#define img(manager,T,X,rename,cube) ExistAndRename(manager,T,X,cube,rename)
/*

	Suppose we have X = {x1, x2, x3, ..., xn} and X' = {x1', x2', x3', ..., xn'}
	out of X and X' only X is the se of actual variables on which state space is defined.
	X' are added becauses of technicle requirment as we all know.

	each of the function takes:
	manager
	S: Start States 
	T: Transition Relation
	B: Bad states, if you are checking property P then B = ~P.
	cube: contains all boolean variables in X set. this can be obtained easily using function Cudd_IndicesToCube().
	rename: is permutation of (X U X'). 
		example: suppose we have 3 bit counter and suppose indices of variables in X are 0,1,2 and that of variables in X' are 3,4,5
		then rename will be array if 6 elements with rename[i] = j implies that i is primed/unprimed variable j

*/
int isSafeF(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename);
int isSafeF_OTF(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename);
int isSafeF_OTF_Frontier(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename);
int isSafeB_OTF(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename);

#endif
