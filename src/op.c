#include<stdio.h>
#include<cudd.h>
#include<cuddInt.h>

DdNode *bAnd(DdManager *manager,DdNode *f,DdNode *g)
{
    DdNode *one,*zero,*F,*G;

    one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);

    F = Cudd_Regular(f);
    G = Cudd_Regular(g);

    if(F == G)		{	if(f == g) return f; else return zero;		}
    if(F == one)	{	if(f == one) return g; else	return zero;	}
    if(G == one)	{	if(g == one) return f; else return zero;	}

	return NULL;
}

DdNode *bOr(DdManager *manager,DdNode *f,DdNode *g)
{
    DdNode *one,*F,*G;

    one = Cudd_ReadOne(manager);

    F = Cudd_Regular(f);
    G = Cudd_Regular(g);

    if(F == G)		{	if(f == g) return f; else return one;		}
    if(F == one)	{	if(f == one) return one; else	return g;	}
    if(G == one)	{	if(g == one) return one; else 	return f;	}

	return NULL;
}

DdNode *bXor(DdManager *manager,DdNode *f,DdNode *g)
{
    DdNode *one,*zero,*F,*G;

    one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);

    F = Cudd_Regular(f);
    G = Cudd_Regular(g);

    if(F == G)		{	if(f == g) return zero; else return one;		}
    if(F == one)	{	if(f == one) return Cudd_Not(g); else return g;	}
    if(G == one)	{	if(g == one) return Cudd_Not(f); else return f;	}

	return NULL;
}

DdNode *bXnor(DdManager *manager,DdNode *f,DdNode *g)
{
    DdNode *one,*zero,*F,*G;

    one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);

    F = Cudd_Regular(f);
    G = Cudd_Regular(g);

    if(F == G)		{	if(f == g) return one; else return zero;		}
    if(F == one)	{	if(f == one) return g; else return Cudd_Not(g);	}
    if(G == one)	{	if(g == one) return f; else return Cudd_Not(f);	}

	return NULL;
}

DdNode *RenameVars(DdManager *manager,DdNode *f,const int *rename)
{
    DdNode *F = NULL,*one = NULL,*r = NULL,*rt = NULL,*re = NULL;

    one = Cudd_ReadOne(manager);

    F = Cudd_Regular(f);
// base case
	if(F == one)	return f;	

//inductive case
	rt = RenameVars(manager,Cudd_T(F),rename);
	Cudd_Ref(rt);
	re = RenameVars(manager,Cudd_E(F),rename);
	Cudd_Ref(re);

	r = cuddUniqueInter(manager,(int)rename[F->index],rt,re);

	Cudd_IterDerefBdd(manager,re);
	Cudd_IterDerefBdd(manager,rt);

	if (Cudd_IsComplement(f))
		if(r != NULL)	return Cudd_Not(r);

	return r;
}
