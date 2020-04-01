// this is a OMP version of the trapz integral code

#include <stdio.h>
#include <omp.h>

float evalmyfun(float x) {
   float y;
   y = 4./(1.+x*x);
   return y;
}

int main(int argc,char* argv[]) {

   unsigned long int i,n; // this was to make n very large over 1e9 to make the calculation run longer and see the effect of parallaliztion
   int num_threads;
   double trap,sum,a,b,dn;
   double myfunatn1;

// intput arguments (i'm not chechking if N is an integra)
   if (argc != 4) { 
      printf("ERROR: enter [a b] and N\n");
      return 1;
   }

   n = atoi(argv[3]);  
   a = atoi(argv[1]);
   b = atoi(argv[2]);


   printf("This calculates the integral of 4/(1+x^2) over [%5.3f %5.3f] in %d steps \n",a,b,n);
   sum = 0.0f;

   dn = (b-a)/n; // step size

// the pragma command is to set the fork  
// reduction makes the sum = sum + X command work 
   #pragma omp parallel for private(myfunatn1,i) reduction(+ : sum) 
    for (i=1; i<=(n-1); i++) {
       myfunatn1=evalmyfun((double)i/n*(b-a)+a);
       sum = sum + myfunatn1;
    }
   sum = (sum + (evalmyfun(a)+evalmyfun(b)) * 0.5) * dn;

  #pragma omp parallel
   {
   num_threads = omp_get_num_threads();
   }
  #pragma omp master
   {
   printf("The result is %f and it was run on %d threads\n\n",sum,num_threads);
   }
   return 0;
}


