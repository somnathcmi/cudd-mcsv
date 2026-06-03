#include<stdio.h>
#include<cudd.h>
#include<cuddInt.h>

DdNode *Apply(DdManager *manager,DdNode *(*op)(DdManager *,DdNode *,DdNode *),DdNode *f,DdNode *g)
{
    DdNode *F = NULL,*ft = f,*fe = f,*G = NULL,*gt = g,*ge = g;
    DdNode *one,*r = NULL,*rt = NULL,*re = NULL;
    int levelf,levelg;
	unsigned int topvar;

    one = Cudd_ReadOne(manager);

    F = Cudd_Regular(f);
    G = Cudd_Regular(g);

// base case
	if(F == G || F == one || G == one)	return (*op)(manager,f,g);	

//inductive case
    levelf = Cudd_ReadPerm(manager,(int)Cudd_NodeReadIndex(F));
    levelg = Cudd_ReadPerm(manager,(int)Cudd_NodeReadIndex(G));

    if(levelf <= levelg) 
	{
		topvar = Cudd_NodeReadIndex(F);
		ft = Cudd_T(F);
		fe = Cudd_E(F);
		if (Cudd_IsComplement(f)) 
		{
		    ft = Cudd_Not(ft);
	    	fe = Cudd_Not(fe);
		}
    }
	else	topvar = Cudd_NodeReadIndex(G);

    if(levelg <= levelf)
	{
		gt = Cudd_T(G);
		ge = Cudd_E(G);
		if (Cudd_IsComplement(g)) 
		{
		    gt = Cudd_Not(gt);
	    	ge = Cudd_Not(ge);
		}
    }

    rt = Apply(manager,op,ft,gt);
    if(rt == NULL) return NULL;
    Cudd_Ref(rt);

    re = Apply(manager,op,fe,ge);
    if(re == NULL) 
	{
		Cudd_IterDerefBdd(manager, rt);
		return NULL;
    }
    Cudd_Ref(re);

    if(rt == re)	r = rt;
    else 
	{
		if(Cudd_IsComplement(rt)) 
		{
		    r = cuddUniqueInter(manager,(int)topvar,Cudd_Not(rt),Cudd_Not(re));
		    if(r == NULL) 
			{
				Cudd_IterDerefBdd(manager, rt);
				Cudd_IterDerefBdd(manager, re);
				return NULL;
	    	}
	    	r = Cudd_Not(r);
		} 
		else 
		{
		    r = cuddUniqueInter(manager,(int)topvar,rt,re);
		    if(r == NULL) 
			{
				Cudd_IterDerefBdd(manager, rt);
				Cudd_IterDerefBdd(manager, re);
				return NULL;
	    	}
		}
    }
    Cudd_Deref(re);
    Cudd_Deref(rt);
    
	return r;
}
