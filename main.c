#include <stdio.h>
#include <stdlib.h>
#include "runtime.h"

/***** [Those Tests Will Help You To Implement prod.ml] *****/


void printTest(char* testMessage, MLvalue mlvalue){
	printf("%s : ", testMessage);
	MLvalue_MLprint(mlvalue);
	printf("\n");
}

int main() {			
		MLRuntime MLruntime = New_MLruntime();

		printf("\n-------------TestUNIT-------------\n");						
		
		MLvalue UNIT = MLruntime->MLlrp;
		printTest("Unit", UNIT);
		MLvalue eqUNIT = MLruntime_MLequal(UNIT, UNIT);
		printTest("Unit equal", eqUNIT);		
		
		printf("\n-------------TestBOOL-------------\n");
		
		MLvalue BOOL_true = New_MLbool(true);
		printTest("True", BOOL_true);
		MLvalue BOOL_false = New_MLbool(false);	
		printTest("False", BOOL_false);
		MLvalue tru = MLruntime->MLtrue;
		printTest("True const", tru);
		MLvalue fal = MLruntime->MLfalse;
		printTest("False const", fal);
		MLvalue eqBOOL = MLruntime_MLequal(fal, fal);
		printTest("Bool equal", eqBOOL);
		MLvalue neqBOOL = MLruntime_MLequal(tru, fal);
		printTest("Bool non equal", neqBOOL);
			
		printf("\n-------------TestINT-------------\n");
		
		MLvalue INT_i = New_MLint(99);
		printTest("Int 99", INT_i);
		MLvalue plus = MLruntime_MLaddint(INT_i, INT_i);
		printTest("Add 99 + 99", plus);
		MLvalue moins = MLruntime_MLsubint(INT_i, INT_i);
		printTest("Sub 99 - 99", moins);
		MLvalue etoile = MLruntime_MLmulint(INT_i, INT_i);
		printTest("Mult 99 * 99", etoile);
		MLvalue slash = MLruntime_MLdivint(INT_i, INT_i);
		printTest("Div 99 / 99", slash);
		MLvalue lt = MLruntime_MLltint(INT_i, INT_i);
		printTest("LT 99 < 99", lt);
		MLvalue le = MLruntime_MLleint(INT_i, INT_i);
		printTest("LE 99 <= 99", le);
		MLvalue gt = MLruntime_MLgtint(INT_i, INT_i);#000000
		printTest("GT 99 > 99", gt);
		MLvalue ge = MLruntime_MLgeint(INT_i, INT_i);
		printTest("GE 99 >= 99", ge);
		MLvalue eqINT = MLruntime_ML#000000equal(INT_i, INT_i#000000
		printTest("EQ 99 == 99", eqINT);
		MLvalue neqINT = MLruntime_MLequal(INT_i, New_MLint(17));
		printTest("NEQ 99 != 99", neqINT);
		
		printf("\n-------------TestDOUBLE-------------\n");
		
		MLvalue FLOAT_f = New_MLdouble(88.3);
		printTest("Float 88.3", FLOAT_f);
		MLvalue eqFLOAT = MLruntime_MLequal(FLOAT_f, FLOAT_f);
		printTest("EQ 88.3 == 88.3", eqFLOAT);
		MLvalue neqFLOAT = MLruntime_MLequal(FLOAT_f, New_MLdouble(17));
		printTest("NEQ 88.3 != 88.3", neqFLOAT);
		
		printf("\n-------------TestSTRING-------------\n");
		MLvalue STRING_s = New_MLstring("Why so serious?");
		printTest("STRING", STRING_s);
		MLvalue conc = MLruntime_MLconcat(STRING_s, New_MLstring("?"));
		printTest("CONCAT", conc);
		MLvalue eqSTRING = MLruntime_MLequal(STRING_s, STRING_s);
		printTest("String equal", eqSTRING);
		MLvalue neqSTRING = MLruntime_MLequal(STRING_s, New_MLstring("W"));
		printTest("String non equal", neqSTRING);
			
		printf("\n-------------TestPAIR-------------\n");
		MLvalue paire1 = MLruntime_MLpair(UNIT, BOOL_true);
		printTest("Pair 1", paire1);
		MLvalue paire2 = MLruntime_MLpair(BOOL_false, INT_i);
		printTest("Pair 2", paire2);
		MLvalue paire3 = MLruntime_MLpair(FLOAT_f, STRING_s);
		printTest("Pair 3", paire3);
		MLvalue paire4 = MLruntime_MLpair(paire1, paire2);
		printTest("Pair 4", paire4);
		MLvalue eqPaire = MLruntime_MLequal(paire4, paire4);
		printTest("Pair equal 4 4", eqPaire);
		MLvalue neqPaire = MLruntime_MLequal(paire1, paire4);
		printTest("Pair non equal 1 4", neqPaire);
		MLvalue paire3_fst = MLruntime->MLfst->funValue->invoke(paire3);
		printTest("Pair 3 first", paire3_fst);
		MLvalue paire3_snd = MLruntime->MLsnd->funValue->invoke(paire3);
		printTest("Pair 3 second", paire3_snd);
		
		printf("\n-------------TestLIST-------------\n");
		
		MLvalue list0 = MLruntime->MLnil;
		printTest("List 0", list0);
		MLvalue list1 = MLruntime_MLlist(New_MLint(1) , list0);
		printTest("List 1", list1);
		MLvalue list2 = MLruntime_MLlist(New_MLint(2) , list1);
		printTest("List 2", list2);
		MLvalue list3 = MLruntime_MLlist(New_MLint(3) , list2);
		printTest("List 3", list3);
		MLvalue list4 = MLruntime_MLlist(New_MLint(4) , list3);
		printTest("List 4", list4);
		MLvalue list5 = MLruntime_MLlist(New_MLint(5) , list4);
		printTest("List 5", list5);
		MLvalue list6 = MLruntime_MLlist(New_MLint(6) , list5);
		printTest("List 6", list6);
		
		MLvalue list6_hd = MLruntime->MLhd->funValue->invoke(list6);
		printTest("List 6 head", list6_hd);
		
		MLvalue list6_tl = MLruntime->MLtl->funValue->invoke(list6);
		printTest("List 6 tail", list6_tl);
		
		MLvalue list0_bis = MLruntime->MLnil;
		printTest("List 0 bis", list0_bis);
		
		MLvalue list1_bis = MLruntime_MLlist(New_MLint(1) , list0_bis);
		printTest("List 1 bis", list1_bis);
		
		MLvalue list2_bis = MLruntime_MLlist(New_MLint(2) , list1_bis);
		printTest("List 2 bis", list2_bis);
		
		MLvalue list3_bis = MLruntime_MLlist(New_MLint(3) , list2_bis);
		printTest("List 3 bis", list3_bis);
		
		MLvalue list4_bis = MLruntime_MLlist(New_MLint(4) , list3_bis);
		printTest("List 4 bis", list4_bis);
		
		MLvalue list5_bis = MLruntime_MLlist(New_MLint(5) , list4_bis);
		printTest("List 5 bis", list5_bis);
		
		MLvalue list6_bis = MLruntime_MLlist(New_MLint(6) , list5_bis);
		printTest("List 6 bis", list6_bis);
		
		MLvalue listEqual = MLruntime_MLequal(list6 , list6_bis);
		printTest("List equal 6 6_bis", listEqual);
		
		MLvalue listNeEqual = MLruntime_MLequal(list5 , list6_bis);
		printTest("List non equal 5 6_bis", listNeEqual);
		
		MLvalue listNeEqualTl = MLruntime_MLequal(list5 , list6_tl);
		printTest("List non equal 5 6_tl", listNeEqualTl);
		
        return 0;
}
