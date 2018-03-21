#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

int main()
{
	int i, j, k, N=100000000;
	double a = 1.234, b = 2.345;
	double ot1, ot2;
	clock_t t1, t2;
	ot1 = omp_get_wtime();
	
	#pragma omp parallel // num_threads(8) // parallelize the following work
	{
		//printf("Hello World (%d,%d,%f) \n",omp_get_thread_num(),omp_get_num_threads(),omp_get_wtime()-ot1);
		//printf("Hello Program (%d,%d,%f)\n",omp_get_thread_num(),omp_get_num_threads(),omp_get_wtime()-ot1);
	}
	
	#pragma omp parallel for // For "#pragma omp parallel for", 8 serials share the i = 0~9 works
	for(i=0;i<10;++i)
	{
		j = i;	// j=0, j=1,...,j=9
		//printf("%d %d\n",i,omp_get_thread_num());
	}
	//printf("j = %d\n",j);	// Not necessarily the last j
	// The print order is not necessarily the order of execution
	
	t1 = clock(); 
	j = 0;
	for(i=0;i<=10;++i)
	{
		j += i;
		//printf("%d %d\n",i);
	}
	printf("sum(1..10) = %d\n",j);
	
	for(k=0;k<100;++k)
	{
		j = 0;	// This line cannot be right under line#40: wrong parallelization
		#pragma omp parallel for
		for(i=0;i<=10;++i)
		{
			j += i;
			//printf("i=%d, j=%d, thread=%d\n",i,j,omp_get_thread_num());
		}
		//printf("sum(1..10) = %d\n",j);	// When sum != correct ans, 2 threads have gotten the same value
											// and one of which fail to update the value
											// So the ans will be lower by the value that fail to upload
		if(j != 55)
		{
			printf("Wrong! %d\n",k);
		}
	}
	
	#pragma omp parallel for private(k)
	for(k=0;k<100;++k)	// To check the correct/incorrect percentage
	{
		j = 0;
		#pragma omp parallel for reduction(+: j)	// To make sure j only be taken 1 time when summing
		for(i=0;i<=10;++i)
		{
			j += i;
			//printf("i=%d, j=%d, thread=%d\n",i,j,omp_get_thread_num());
		}
		//printf("sum(1..10) = %d\n",j); //
		if(j != 55)
		{
			printf("Wrong!Wrong! %d\n",k);
		}
	}
	
	// private: every thread has its own value
	#pragma omp parallel for private(k)	// If inside () is only k, every thread take different k
										// But has same j, if (k,j), every thread has its own k, j
										// Distribute to A=0, B=1,...,H
	for(k=0;k<100;++k) {
		j = 0;
		#pragma omp parallel for reduction(+: j)	// If reduction j is here, there will be some mistakes
													// But! b can take a's value
													// Distribute to C_1, C_2,...,C_10
		for(i=0;i<=10;++i)
		{
			j += i;
			//printf("i=%d, j=%d, thread=%d\n",i,j,omp_get_thread_num());
		}
		//printf("sum(1..10) = %d\n",j);
		//printf("%d thread\n", omp_get_thread_num());
		if(j != 55) {
			printf("The summation is Wrong! %d\n", k);
		}
	}
	
	return 0;
	
	t1 = clock();
	for(i=0;i<N;++i) {
		a = a*b;
		b = a/b;
		a = a/b;
	}
	t2 = clock();
	printf("a = %f, b = %f\n", a, b);
	printf("parallel time:%f\n",(t2-t1)/(double) CLOCKS_PER_SEC);
	
	t1 = clock();
	#pragma omp parallel for num_threads(4)
	for(i=0;i<N;++i) {
		a = a*b;
		b = a/b;
		a = a/b;
	}
	t2 = clock();
	printf("a = %f, b = %f\n", a, b);
	printf("parallel time:%f\n",(t2-t1)/(double) CLOCKS_PER_SEC);
	
	return 0;
}
