#ifndef RUNTIME_H
#define RUNTIME_H

/*-------------------------Data-------------------------*/

/*********************** [MLvalue] **********************/
typedef enum {
	MLUNIT,
	MLBOOL,
	MLINT,
	MLDOUBLE,
	MLSTRING,
	MLPAIR,
	MLLIST,
	MLFUN
} MLType;

typedef struct MLvalue {
	MLType type;
	union {
		struct MLunit*    unitValue;
		struct MLbool*    boolValue;
		struct MLint*     intValue;
		struct MLdouble*  doubleValue;
		struct MLstring*  stringValue;
		struct MLpair*    pairValue;
		struct MLlist*    listValue;
		struct MLfun*     funValue;
	};
} *MLvalue;

/********************** [MLunit] *************************/
typedef struct MLunit {         
	int val;
}*MLunit;

/*********************** [MLbool] ************************/
typedef enum { 
	false = 0, 
	true 
} bool;

typedef struct MLbool {                
	bool val;        	
} *MLbool;

/************************ [MLint] *************************/
typedef struct MLint {                	
	int val;        		
} *MLint;

/*********************** [MLdouble] ***********************/
typedef struct MLdouble {                
	double val;        			
} *MLdouble;

/*********************** [MLstring] ***********************/
typedef struct MLstring {                
	char *val;        		
} *MLstring;

/************************ [MLpair] ************************/

typedef struct MLpair {
	MLvalue firstValue;
	MLvalue secondValue;
} *MLpair;


/************************ [MLlist] ************************/
typedef struct MLlist {
	MLvalue MLcar;
	MLvalue MLcdr;
} *MLlist;

/************************* [MLfun] ************************/
typedef struct MLfun {
	int counter;
	MLvalue* MLenv;	
	MLvalue (*invoke)(MLvalue, MLvalue);
} *MLfun;

/*********************** [MLruntime] **********************/
typedef struct MLRuntime {
	MLvalue MLlrp;
	MLvalue MLtrue;
	MLvalue MLfalse;
	MLvalue MLnil;
	MLvalue MLfst;
	MLvalue MLsnd;
	MLvalue MLhd;
	MLvalue MLtl;
} *MLRuntime;

/*-----------------------Functions-----------------------*/

void MLunit_print();
MLvalue New_MLunit();

void MLbool_print(MLvalue this);
MLvalue New_MLbool(bool initVal);

void MLint_print(MLvalue this);
MLvalue New_MLint(int initVal);

void MLdouble_print(MLvalue this);
MLvalue New_MLdouble(double initVal);

void MLstring_print(MLvalue this);
MLvalue New_MLstring(char *initVal);

void MLpair_print(MLvalue this);
MLvalue New_MLpair(MLvalue first, MLvalue second);

void MLlist_print(MLvalue this);
MLvalue New_MLlist(MLvalue first, MLvalue second);

void MLfun_print(MLvalue this);
void MLfun_addenv(MLfun this, MLvalue* env_, MLvalue a);
MLvalue New_MLfun(int nbArgs, MLvalue (*invoke)(MLvalue, MLvalue));

MLvalue MLvalue_MLprint(MLvalue this);
MLvalue MLvalue_MLprintln(MLvalue this);

MLRuntime New_MLruntime();

MLvalue MLruntime_MLaddint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLsubint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLmulint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLdivint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLequal(MLvalue x, MLvalue y);
MLvalue MLruntime_MLltint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLleint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLgtint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLgeint(MLvalue x, MLvalue y);
MLvalue MLruntime_MLpair(MLvalue x, MLvalue y);
MLvalue MLruntime_MLlist(MLvalue x, MLvalue y);
MLvalue MLruntime_MLconcat(MLvalue x, MLvalue y);
MLvalue MLruntime_fst(MLvalue fun,MLvalue p);
MLvalue MLruntime_snd(MLvalue fun, MLvalue p);
MLvalue MLruntime_hd(MLvalue fun, MLvalue l);
MLvalue MLruntime_tl(MLvalue fun, MLvalue l);

MLvalue __rp;
MLvalue __nil;
MLvalue __true;
MLvalue __false;

#endif
