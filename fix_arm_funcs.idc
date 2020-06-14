/* Ruben Santamarta www.reversemode.com */
/* Fix functions - Schneider NOE 110 firmware */
  
/* Edited by Harrys Kon Feb. 2015*/
/* Edited by me June. 2020*/
  
/* FixARMfunctions.idc*/
  
#include <idc.idc>
  
static main() {
 auto ae;
 auto funct;
 auto minea;
 auto prolog;
 auto j;
 auto fun_array;
 /* Add here your ARM opcodes that represent function start, comma separated */
 auto opcodes_list = "50 E3,9F E5,A0 E3,A0 E1,90 E5,2D E9,4D E2,";
 auto iteration_num;
  
for (iteration_num=0; iteration_num<(strlen(opcodes_list)/6); iteration_num++){
 print("Executing iteration %d\n", iteration_num);
 minea = MinEA();
 SetStatus(IDA_STATUS_WORK);
 fun_array = CreateArray("ProGos");
  
 if (fun_array == -1) 
   fun_array = GetArrayId("ProGos");
   SetArrayString(fun_array,0, opcodes_list[(0+iteration_num*6):(5+iteration_num*6)]);
  
 for (j=0;j<1;j++){
   ae = minea;
   prolog = GetArrayElement(AR_STR,fun_array,j);
   while (1) {
     funct = FindBinary ( ae, SEARCH_DOWN, prolog); 
     if (funct == BADADDR )
       break; 
     funct = funct - 2;
     MakeCode (funct);
     MakeFunction (funct, BADADDR); 
     ae = funct + 4;
   }
 }
}
 SetStatus(IDA_STATUS_READY); 
}
