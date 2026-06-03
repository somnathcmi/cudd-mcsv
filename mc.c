#include<stdio.h>
#include<cudd.h>
#include<cuddInt.h>
#include "blib.h"

#define img(manager,T,X,rename,cube) ExistAndRename(manager,T,X,cube,rename)

int isSafeF(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename)
{
	DdNode *Sc,*Sn,*one,*zero,*tmp;

	one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);
	Sn = S;
	Sc = zero;

	while(Sn != Sc)
	{
		Cudd_IterDerefBdd(manager,Sc);
		Sc = Sn;
		tmp = img(manager,T,Sc,rename,cube);
		Cudd_Ref(tmp);
		Sn = Apply(manager,bOr,Sc,tmp);
		Cudd_Ref(Sn);
		Cudd_IterDerefBdd(manager,tmp);
	}

	tmp = Apply(manager,bAnd,Sn,B);
	Cudd_Ref(tmp);
	Cudd_IterDerefBdd(manager,Sc);
	Cudd_IterDerefBdd(manager,Sn);

	if(tmp == zero)
	{
		Cudd_IterDerefBdd(manager,tmp);
		return 1;
	}

	Cudd_IterDerefBdd(manager,tmp);
	return 0;
}

int isSafeF_OTF(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename)
{
	DdNode *Sc,*Sn,*one,*zero,*tmp;

	one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);
	Sn = S;
	Sc = zero;

	while(Sn != Sc)
	{
		Cudd_IterDerefBdd(manager,Sc);
		Sc = Sn;
		tmp = img(manager,T,Sc,rename,cube);
		Cudd_Ref(tmp);
		Sn = Apply(manager,bOr,Sc,tmp);
		Cudd_Ref(Sn);
		Cudd_IterDerefBdd(manager,tmp);
		tmp = Apply(manager,bAnd,Sn,B);
		Cudd_Ref(tmp);
		if(tmp != zero)
		{
			Cudd_IterDerefBdd(manager,Sc);
			Cudd_IterDerefBdd(manager,Sn);
			Cudd_IterDerefBdd(manager,tmp);
			return 0;
		}
	}

	Cudd_IterDerefBdd(manager,Sc);
	Cudd_IterDerefBdd(manager,Sn);

	return 1;
}

int isSafeF_OTF_Frontier(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename)
{
	DdNode *F,*Sc,*Sn,*one,*zero,*tmp;

	one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);
	Sn = S;	F = S;
	Sc = zero;

	tmp = Apply(manager,bAnd,F,B);
	Cudd_Ref(tmp);
	if(tmp != zero)
	{
		Cudd_IterDerefBdd(manager,tmp);
		return 0;
	}
	
	while(F != zero)
	{
		Sc = Sn;
		tmp = img(manager,T,F,rename,cube);
		Cudd_Ref(tmp);
		Sn = Apply(manager,bOr,Sc,tmp);
		Cudd_Ref(Sn);
		Cudd_IterDerefBdd(manager, tmp);
		Cudd_IterDerefBdd(manager,F);
		F = Apply(manager,bAnd,Sn,Cudd_Not(Sc));
		Cudd_Ref(F);
		tmp = Apply(manager,bAnd,F,B);
		Cudd_Ref(tmp);
		if(tmp != zero)
		{
			Cudd_IterDerefBdd(manager,Sc);
			Cudd_IterDerefBdd(manager,F);
			Cudd_IterDerefBdd(manager,Sn);
			Cudd_IterDerefBdd(manager,tmp);
			return 0;
		}
		Cudd_IterDerefBdd(manager,Sc);
		Cudd_IterDerefBdd(manager,tmp);
	}

	Cudd_IterDerefBdd(manager,F);
	Cudd_IterDerefBdd(manager,Sn);

	return 1;
}

int isSafeB_OTF(DdManager *manager,DdNode *S,DdNode *T,DdNode *B,DdNode *cube, const int *rename)
{
	DdNode *Sc,*Sn,*one,*zero,*tmp;

	one = Cudd_ReadOne(manager);
	zero = Cudd_Not(one);
	Sn = B;
	Sc = zero;

	while(Sn != Sc)
	{
		Cudd_IterDerefBdd(manager,Sc);
		Sc = Sn;
		tmp = img(manager,T,Sc,rename,cube);
		Cudd_Ref(tmp);
		Sn = Apply(manager,bOr,Sc,tmp);
		Cudd_Ref(Sn);
		Cudd_IterDerefBdd(manager,tmp);
		tmp = Apply(manager,bAnd,Sn,S);
		Cudd_Ref(tmp);
		if(tmp != zero)
		{
			Cudd_IterDerefBdd(manager,Sc);
			Cudd_IterDerefBdd(manager,Sn);
			Cudd_IterDerefBdd(manager,tmp);
			return 0;
		}
	}

	Cudd_IterDerefBdd(manager,Sc);
	Cudd_IterDerefBdd(manager,Sn);

	return 1;
}
