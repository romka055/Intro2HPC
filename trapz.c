#include <stdio.h>

float evalmyfun(float x) {
   float y;
   y = 4./(1.+x*x);
   return y;
}

int main(int argc,char* argv[]) {
   int i,n;
   float trap,sum,a,b,dn;
   float myfunatn, myfunatn1;

   n = atoi(argv[3]);  
   a = atoi(argv[1]);
   b = atoi(argv[2]);

   if (n<1) {
      printf("ERROR: enter [a b] and N\n");
      return 1;
   }

   printf("This calculates the integral of 4/(1+x^2) over [%5.3f %5.3f] in %d steps !\n",a,b,n);
   sum = 0.0f;

// This is for less myfun evaluations but maybe not so good for parallelization 
   myfunatn=evalmyfun(a);
   dn = (b-a)/n;
   for (i=1; i<=n; i++) {
       myfunatn1=evalmyfun((float)i/n*(b-a)+a);
       trap = (myfunatn+myfunatn1)/2.0*dn;
       sum = trap + sum;
       myfunatn = myfunatn1;
   }
 
/* this is a "standart version with many myfun evaluations

   for (i=0; i<n; i++) {
       trap = (evalmyfun((float)i/n)+evalmyfun((i+1.0)/n))/2./n;
       sum = trap + sum;
   }
*/

   printf("The result is %f\n",sum);   
   return 0;
}


