#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "runtime.h"

/*********************** [MLunit] ************************/
void MLunit_print() {
	printf("()");
}

MLvalue New_MLunit() {
	MLvalue unitValue = malloc(sizeof(struct MLvalue));
	MLunit this = malloc(sizeof(struct MLunit));
	this->val = 0;
	unitValue->type = MLUNIT; 
	unitValue->unitValue = this;
	return unitValue;
}

/*********************** [MLbool] ************************/
void MLbool_print(MLvalue this) {
	if (this->boolValue->val) 		
	    printf("true");
	else
		printf("false");
}

MLvalue New_MLbool(bool initVal) {
       MLvalue boolValue = malloc(sizeof(struct MLbool));
       MLbool this = malloc(sizeof(struct MLbool));
       this->val = initVal;
       boolValue->type = MLBOOL;
       boolValue->boolValue = this;
       return boolValue;
}

/************************ [MLint] ************************/
void MLint_print(MLvalue this) {
        printf("%d", this->intValue->val);
}

MLvalue New_MLint(int initVal) {
       MLvalue intValue = malloc(sizeof(struct MLvalue));
       MLint this = malloc(sizeof(struct MLint));
       this->val = initVal;       
       intValue->type = MLINT;
       intValue->intValue = this;
       return intValue;
}

/*********************** [MLdouble] ***********************/
void MLdouble_print(MLvalue this) {
        printf("%lf", this->doubleValue->val);
}

MLvalue New_MLdouble(double initVal) {
       MLvalue doubleValue = malloc(sizeof(struct MLdouble));
       MLdouble this = malloc(sizeof(struct MLdouble));
       this->val = initVal;
       doubleValue->type = MLDOUBLE;
       doubleValue->doubleValue = this;
       return doubleValue;
}

/*********************** [MLstring] ***********************/
void MLstring_print(MLvalue this) {
        printf("\"%s\"", this->stringValue->val);
}

MLvalue New_MLstring(char* initVal) {
       MLvalue stringValue = malloc(sizeof(struct MLvalue));
       MLstring this = malloc(sizeof(struct MLstring));
       this->val = initVal;
       stringValue->type = MLSTRING;
       stringValue->stringValue = this;
       return stringValue;
}

/************************ [MLpair] *************************/
void MLpair_print(MLvalue this) {
	printf("(");
	MLvalue_MLprint(this->pairValue->firstValue);
	printf(" , ");
	MLvalue_MLprint(this->pairValue->secondValue);
	printf(")");
}

MLvalue New_MLpair(MLvalue first, MLvalue second) {
	MLvalue pairValue = malloc(sizeof(struct MLvalue));
	MLpair this = malloc(sizeof(struct MLpair));
	this->firstValue = first;
	this->secondValue = second;
	pairValue->type = MLPAIR;
	pairValue->pairValue = this;
	return pairValue;
}

/************************ [MLlist] *************************/
void MLlist_print(MLvalue this) {
	if (this == __nil) {
		printf("[]");
	} else {
		MLvalue_MLprint(this->listValue->MLcar);
		printf("::");
		MLvalue_MLprint(this->listValue->MLcdr);
	}
}

MLvalue New_MLlist(MLvalue first, MLvalue second) {
	MLvalue listValue = malloc(sizeof(struct MLvalue));
	MLlist this = malloc(sizeof(struct MLlist));
	this->MLcar = first;
	this->MLcdr = second;
	listValue->type = MLLIST;
	listValue->listValue = this;
	return listValue;
}

/************************* [MLfun] *************************/

void MLfun_print(MLvalue this){
	 printf("<fun> [");
     int i;
     for (i=0; i< this->funValue->counter; i++)
           MLvalue_MLprint(this->funValue->MLenv[i]);
     printf("]");
}

void MLfun_addenv(MLfun this, MLvalue* env_, MLvalue a){
	int i;
	for (i=0; i< this->counter; i++) 
		this->MLenv[i]=env_[i];
    this->MLenv[this->counter]=a;
    this->counter++;
}

MLvalue New_MLfun(int nbArgs, MLvalue (*invoke)(MLvalue, MLvalue)){
	MLvalue funValue = malloc(sizeof(struct MLvalue));
	MLfun this = malloc(sizeof(struct MLfun));
	this->counter = 0;
	MLvalue* env = malloc(sizeof(MLvalue)*nbArgs);
	this->MLenv = env;
	this->invoke = invoke;
	funValue->type = MLFUN;
	funValue->funValue = this;
	return funValue;
}

/*********************** [MLvalue] ***********************/
MLvalue MLvalue_MLprint(MLvalue this) {
	switch (this->type) {
		case MLUNIT:
			MLunit_print();
			break;
		case MLBOOL:
			MLbool_print(this);
			break;
		case MLINT:
			MLint_print(this);
			break;
		case MLDOUBLE:
			MLdouble_print(this);
			break;
		case MLSTRING:
			MLstring_print(this);
			break;
		case MLPAIR:
			MLpair_print(this);
			break;
		case MLLIST:
			MLlist_print(this);
			break;
		case MLFUN:
			MLfun_print(this);
			break;
	}
	return __rp;
}

MLvalue MLvalue_MLprintln(MLvalue this){
	MLvalue_MLprint(this);
	printf("\n");
	return __rp;
}

/*********************** [MLruntime] ***********************/

MLvalue MLruntime_fst(MLvalue fun, MLvalue p) {
	return p->pairValue->firstValue;
}

MLvalue MLruntime_snd(MLvalue fun, MLvalue p) {
	return p->pairValue->secondValue;
}

MLvalue MLruntime_hd(MLvalue fun, MLvalue l) {
	return l->listValue->MLcar;
}

MLvalue MLruntime_tl(MLvalue fun, MLvalue l) { 
	return l->listValue->MLcdr;
}

MLRuntime New_MLruntime() {	      
    MLRuntime this = malloc(sizeof(struct MLRuntime));  
    __rp = New_MLunit();
    __true = New_MLbool(true);
    __false = New_MLbool(false);
    __nil = New_MLlist(this->MLlrp, this->MLlrp);
    
	this->MLlrp = __rp;
	this->MLtrue = __true;
	this->MLfalse = __false;
	this->MLnil = __nil;
	
	this->MLfst = New_MLfun(1, MLruntime_fst);
	this->MLsnd = New_MLfun(1, MLruntime_snd);
	this->MLhd = New_MLfun(1, MLruntime_hd);
	this->MLtl = New_MLfun(1, MLruntime_tl);
    return this;
}

MLvalue MLruntime_MLaddint(MLvalue x, MLvalue y) {
        return New_MLint(x->intValue->val + y->intValue->val);
}

MLvalue MLruntime_MLsubint(MLvalue x, MLvalue y) {
        return New_MLint(x->intValue->val - y->intValue->val);
}

MLvalue MLruntime_MLmulint(MLvalue x, MLvalue y) {
        return New_MLint(x->intValue->val * y->intValue->val);
}

MLvalue MLruntime_MLdivint(MLvalue x, MLvalue y) {
        return New_MLint(x->intValue->val / y->intValue->val);
}

MLvalue isTrue(int boolean){
	if(boolean){
		return __true;
	}
	return __false;
}

MLvalue MLruntime_MLequal(MLvalue x, MLvalue y) {
	if (x == y) {
		return __true; 
	} else {
		if (x->type == MLUNIT && y->type == MLUNIT){
			return isTrue(x->unitValue->val == y->unitValue->val);
		}
		else if (x->type == MLBOOL && y->type == MLBOOL){
			return isTrue(x->boolValue->val == y->boolValue->val);
		}
		else if (x->type == MLINT && y->type == MLINT){
			return isTrue(x->intValue->val == y->intValue->val);
		}
		else if (x->type == MLDOUBLE && y->type == MLDOUBLE){
			return isTrue(x->doubleValue->val == y->doubleValue->val);
		}
		else if (x->type == MLSTRING && y->type == MLSTRING){
			return isTrue(x->stringValue->val == y->stringValue->val);
		}
		else if (x->type == MLPAIR && y->type == MLPAIR){
			return isTrue(MLruntime_MLequal(x->pairValue->firstValue, 
					  y->pairValue->firstValue)->boolValue->val &&
			                  MLruntime_MLequal(x->pairValue->secondValue, 
					  y->pairValue->secondValue)->boolValue->val);
		}
		else if (x->type == MLLIST && y->type == MLLIST){
			
			if(x == __nil && y == __nil){
				return __true;
			}
			if(x != __nil && y == __nil){
				return __false;
			}
			if(x == __nil && y != __nil){
				return __false;
			}
			else{
				if(MLruntime_MLequal(x->listValue->MLcar, y->listValue->MLcar) == __true){
					return MLruntime_MLequal(x->listValue->MLcdr, y->listValue->MLcdr); 
				}
				return __false;
			}
		}
		else if (x->type == MLFUN && y->type == MLFUN){
			return isTrue(x->funValue->counter == y->funValue->counter
							&& x->funValue->invoke == y->funValue->invoke);
		}
		else 
			return __false;
	}
}

MLvalue MLruntime_MLltint(MLvalue x, MLvalue y) {
	return isTrue(x->intValue->val < y->intValue->val);
}

MLvalue MLruntime_MLleint(MLvalue x, MLvalue y) {
    return isTrue(x->intValue->val <= y->intValue->val);
}

MLvalue MLruntime_MLgtint(MLvalue x, MLvalue y) {
	return isTrue(x->intValue->val > y->intValue->val);
}

MLvalue MLruntime_MLgeint(MLvalue x, MLvalue y) {
	return isTrue(x->intValue->val >= y->intValue->val);
}

MLvalue MLruntime_MLpair(MLvalue x, MLvalue y) {
        return New_MLpair(x,y);
}

/* function to creat a list */
MLvalue MLruntime_MLlist(MLvalue x, MLvalue y) {
	return New_MLlist(x,y);
}

/* function to concatenate two strings */
MLvalue MLruntime_MLconcat(MLvalue x, MLvalue y) {
	char* str = malloc(sizeof(char)*strlen(x->stringValue->val));
	strcpy(str, x->stringValue->val);
	strcat(str, y->stringValue->val);
    return New_MLstring(str);
}

