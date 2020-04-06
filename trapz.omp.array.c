// this is a OMP version of the trapz integral code

#include <stdio.h>
#include <omp.h>

#define NTHREADS 48

float evalmyfun(float x) {
   float y;
   y = 4./(1.+x*x);
   return y;
}

int main(int argc,char* argv[]) {

   unsigned long int i,n; // this was to make n very large over 1e9 to make the calculation run longer and see the effect of parallaliztion
   int num_threads,id;
   double trap,a,b,dn;
   double myfunatn1, res;
   double sum[NTHREADS] = {0.0};

// intput arguments (i'm not chechking if N is an integra)
   if (argc != 4) { 
      printf("ERROR: enter [a b] and N\n");
      return 1;
   }

   n = atoi(argv[3]);  
   a = atoi(argv[1]);
   b = atoi(argv[2]);


   printf("This calculates the integral of 4/(1+x^2) over [%5.3f %5.3f] in %d steps \n",a,b,n);

   dn = (b-a)/n; // step size

   omp_set_num_threads(NTHREADS);  // define the number of threads

// the pragma command is to set the fork  
// reduction makes the sum = sum + X command work

   #pragma omp parallel private(id,i,myfunatn1)
   {
    id = omp_get_thread_num();
    //int numthreads = omp_get_num_threads();
    
    for (i=id+1; i<=(n-1); i+=NTHREADS) {
       myfunatn1=evalmyfun((double)i/n*(b-a)+a);
       sum[id] += myfunatn1;
    }
   } // end parallel
   for (i=0; i<NTHREADS; i++)
       res += sum[i];

   res = (res + (evalmyfun(a)+evalmyfun(b)) * 0.5) * dn;

   printf("The result is %f and it was run on %d threads\n\n",res,NTHREADS);
   return 0;
}


