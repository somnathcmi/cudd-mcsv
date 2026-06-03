#include<stdio.h>
#include "blib.h"
#include "mc.h"

int main()
{
	DdManager *manager;
	DdNode *x,*x0,*x1,*y,*y0,*y1,*T0,*T1,*T2,*T3,*S0,*S1,*S2,*S3,*inc1,*inc2;
	manager = Cudd_Init(4,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
	int rename[4] = {2,3,0,1},xx[2] = {0,1},yy[2] = {2,3};

	x0 = Cudd_bddIthVar(manager,0);
	x1 = Cudd_bddIthVar(manager,1);
	y0 = Cudd_bddIthVar(manager,2);
	y1 = Cudd_bddIthVar(manager,3);

	Cudd_AutodynDisable(manager);

	x = Cudd_IndicesToCube(manager,xx,2);
	y = Cudd_IndicesToCube(manager,yy,2);

	T3 = Apply(manager,bAnd,x0,x1);
	Cudd_Ref(T3);
	T2 = Apply(manager,bAnd,x1,Cudd_Not(x0));
	Cudd_Ref(T2);
	T1 = Apply(manager,bAnd,Cudd_Not(x1),x0);
	Cudd_Ref(T1);
	T0 = Apply(manager,bAnd,Cudd_Not(x0),Cudd_Not(x1));
	Cudd_Ref(T0);

	S1 = Apply(manager,bXnor,y0,Cudd_Not(x0));
	Cudd_Ref(S1);
	S2 = Apply(manager,bXor,x1,x0);
	Cudd_Ref(S2);
	S3 = Apply(manager,bXnor,y1,S2);
	Cudd_Ref(S3);
	inc1 = Apply(manager,bAnd,S1,S3);
	Cudd_Ref(inc1);
	
	Cudd_RecursiveDeref(manager, S1);
	Cudd_RecursiveDeref(manager, S2);
	Cudd_RecursiveDeref(manager, S3);

	S1 = Apply(manager,bXnor,y0,x0);
	Cudd_Ref(S1);
	S2 = Apply(manager,bXnor,y1,Cudd_Not(x1));
	Cudd_Ref(S2);
	inc2 = Apply(manager,bAnd,S1,S2);
	Cudd_Ref(inc2);	
	
	Cudd_RecursiveDeref(manager, S1);
	Cudd_RecursiveDeref(manager, S2);

	S3 = Apply(manager,bAnd,y0,y1);
	Cudd_Ref(S3);
	S2 = Apply(manager,bAnd,y1,Cudd_Not(y0));
	Cudd_Ref(S2);
	S1 = Apply(manager,bAnd,Cudd_Not(y1),y0);
	Cudd_Ref(S1);
	S0 = Apply(manager,bAnd,Cudd_Not(y0),Cudd_Not(y1));
	Cudd_Ref(S0);

	printf("---------isSafeF:inc1--------\n");
	if(isSafeF(manager,T0,inc1,T0,x,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeF(manager,T0,inc1,T1,x,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeF(manager,T0,inc1,T2,x,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeF(manager,T0,inc1,T3,x,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeF:inc2--------\n");
	if(isSafeF(manager,T0,inc2,T0,x,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeF(manager,T0,inc2,T1,x,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeF(manager,T0,inc2,T2,x,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeF(manager,T0,inc2,T3,x,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeF_OTF:inc1--------\n");
	if(isSafeF_OTF(manager,T0,inc1,T0,x,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeF_OTF(manager,T0,inc1,T1,x,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeF_OTF(manager,T0,inc1,T2,x,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeF_OTF(manager,T0,inc1,T3,x,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeF_OTF:inc2--------\n");
	if(isSafeF_OTF(manager,T0,inc2,T0,x,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeF_OTF(manager,T0,inc2,T1,x,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeF_OTF(manager,T0,inc2,T2,x,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeF_OTF(manager,T0,inc2,T3,x,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeF_OTF_Frontier:inc1--------\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc1,T0,x,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc1,T1,x,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc1,T2,x,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc1,T3,x,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeF_OTF_Frontier:inc2--------\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc2,T0,x,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc2,T1,x,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc2,T2,x,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeF_OTF_Frontier(manager,T0,inc2,T3,x,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeB_OTF:inc1--------\n");
	if(isSafeB_OTF(manager,S0,inc1,S0,y,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeB_OTF(manager,S0,inc1,S1,y,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeB_OTF(manager,S0,inc1,S2,y,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeB_OTF(manager,S0,inc1,S3,y,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	printf("---------isSafeB_OTF:inc2--------\n");
	if(isSafeB_OTF(manager,S0,inc2,S0,y,rename))	printf("T0 is safe from T0\n");
	else	printf("T0 is not safe from T0\n");
	if(isSafeB_OTF(manager,S0,inc2,S1,y,rename))	printf("T1 is safe from T0\n");
	else	printf("T1 is not safe from T0\n");
	if(isSafeB_OTF(manager,S0,inc2,S2,y,rename))	printf("T2 is safe from T0\n");
	else	printf("T2 is not safe from T0\n");
	if(isSafeB_OTF(manager,S0,inc2,S3,y,rename))	printf("T3 is safe from T0\n");
	else	printf("T3 is not safe from T0\n");

	if(img(manager,inc1,S1,rename,y) == S0)	printf("pimg(S1,inc1) = S0\n");
	if(img(manager,inc1,S2,rename,y) == S1)	printf("pimg(S2,inc1) = S1\n");
	if(img(manager,inc1,S3,rename,y) == S2)	printf("pimg(S3,inc1) = S2\n");
	if(img(manager,inc1,S0,rename,y) == S3)	printf("pimg(S0,inc1) = S3\n");
/*
	const char *inpnames[4];
	inpnames[0] = "x0";
	inpnames[1] = "x1";
	inpnames[2] = "y0";
	inpnames[3] = "y1";

	const char *outnames[12];
	outnames[0] = "T3";
	outnames[1] = "T2";
	outnames[2] = "T1";
	outnames[3] = "T0";
	outnames[4] = "t3";
	outnames[5] = "t2";
	outnames[6] = "t1";
	outnames[7] = "t0";
	outnames[8] = "S2";
	outnames[9] = "inc2";
	outnames[10] = "inc11";
	outnames[11] = "inc22";

	DdNode *outputs[12];
	outputs[0] = T3;
	outputs[1] = T2;
	outputs[2] = T1;
	outputs[3] = T0;
	outputs[4] = t3;
	outputs[5] = t2;
	outputs[6] = t1;
	outputs[7] = t0;
	outputs[8] = S2;
	outputs[9] = inc2;
	outputs[10] = inc11;
	outputs[11] = inc22;

	FILE *f = fopen("foo_viz.dot", "w");

	Cudd_DumpDot(manager, 4, &outputs[4], inpnames, &outnames[4], f);

	fclose(f);
*/	
	Cudd_RecursiveDeref(manager, inc1);
	Cudd_RecursiveDeref(manager, inc2);
	Cudd_RecursiveDeref(manager, T0);
	Cudd_RecursiveDeref(manager, T1);
	Cudd_RecursiveDeref(manager, T2);
	Cudd_RecursiveDeref(manager, T3);
	Cudd_RecursiveDeref(manager, x);
	Cudd_RecursiveDeref(manager, y);
	Cudd_RecursiveDeref(manager, S0);
	Cudd_RecursiveDeref(manager, S1);
	Cudd_RecursiveDeref(manager, S2);
	Cudd_RecursiveDeref(manager, S3);

	Cudd_Quit(manager);
}
