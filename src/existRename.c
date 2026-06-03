#include<stdio.h>
#include<cudd.h>
#include<cuddInt.h>
#include "../blib.h"

DdNode *ExistAndRename(DdManager *manager,DdNode *f,DdNode *g,DdNode *cube,const int *rename)
{
	DdNode *F,*ft = f,*fe = f,*G,*gt = g,*ge = g,*one,*zero,*r,*t,*e;
	int levelf,levelg,toplevel,cubelevel;
	unsigned int topvar;

	one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);
	
	if(f == zero || g == zero || f == Cudd_Not(g)) return(zero);
	if(f == one && g == one)	return(one);
//	if(cube == one)	return Apply(manager,bAnd,f,g);
	if(Cudd_IsComplement(cube))	return NULL;

	F = Cudd_Regular(f);
	G = Cudd_Regular(g);
	levelf = Cudd_ReadPerm(manager,F->index);
	levelg = Cudd_ReadPerm(manager,G->index);
	toplevel = levelf<=levelg?levelf:levelg;
	cubelevel = Cudd_ReadPerm(manager,cube->index);

	while (cubelevel < toplevel) 
	{
		cube = Cudd_T(cube);
		cubelevel = Cudd_ReadPerm(manager,cube->index);
		if (cube == one)	break;	//return Apply(manager,bAnd,f,g);
	}

	if (levelf == toplevel) 
	{
		topvar = F->index;
		ft = Cudd_T(F);
		fe = Cudd_E(F);
		if (Cudd_IsComplement(f))
		{
			ft = Cudd_Not(ft);
			fe = Cudd_Not(fe);
		}
	}
	else
		topvar = G->index;

	if (levelg == toplevel)
	{
		gt = Cudd_T(G);
		ge = Cudd_E(G);
		if (Cudd_IsComplement(g))	
		{
			gt = Cudd_Not(gt);
			ge = Cudd_Not(ge);
		}
	}
	
	if(toplevel == cubelevel)	cube = Cudd_T(cube);

	t = ExistAndRename(manager, ft, gt, cube, rename);
	if(t == NULL) return NULL;
	Cudd_Ref(t);

	e = ExistAndRename(manager, fe, ge, cube, rename);	
	if(e == NULL)
	{ 
		Cudd_IterDerefBdd(manager, t);
		return NULL;
	}
	Cudd_Ref(e);

	if(cubelevel == toplevel)
		r = Apply(manager,bOr,t,e);
	else
	{
		if(Cudd_IsComplement(t))
		{
			r = Cudd_bddIte(manager,manager->vars[(int)rename[topvar]],Cudd_Not(t),Cudd_Not(e));
			if(r == NULL)
			{
				Cudd_IterDerefBdd(manager,t);
				Cudd_IterDerefBdd(manager,e);
				return NULL;
			}
			r = Cudd_Not(r);
		}
		else
			r = Cudd_bddIte(manager,manager->vars[(int)rename[topvar]],t,e);
	}

	Cudd_Deref(t);
	Cudd_Deref(e);

	return r;
}
