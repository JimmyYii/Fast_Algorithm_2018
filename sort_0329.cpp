#include <stdio.h>
#include <stdlib.h>
//#include <omp.h>	// omp_get...
#include <math.h>
#include <time.h>
//#include ""	// Call head file for use

// input a vector x (pointer), left and right boundary of sorting(left, right)
int quicksort(int *x, int left, int right);

int main()
{
	clock_t t1, t2;				// variables for computing clocks 
	int *x, *y, s, p;
	double T1;
	int i, j, N;

	srand( time(NULL) );
	printf("%d\n",function_name(2,100,10));
	printf("%d\n",fractorial(10));
	//return 0;
	
	for(N=10;N<=10;N*=2)
	{
		// To generate random number, the parallel one need more study 
		x = (int *) malloc( N * sizeof(int) );
		y = (int *) malloc( N * sizeof(int) );

		//#pragma omp parallel
		{
			//#pragma omp parallel for
			for(i=0;i<N;++i)
			{
				y[i] = x[i] = rand() % N;
			}
		}

		for(i=0;i<N;++i)
		{
			printf("x[%d]=%d\n",i,x[i]);
		}
		
		t1 = clock();
		
		// Bubble sort: Check two numbers, put larger than x[i] to the back
		// Operation counts: SWAP, COMPARE (N-1)+(N-2)+(N-3)+...+1=
		for(i=0;i<N;++i) // O(N^2)
		{
			// y[i]: elements need checked
			for(j=i+1;j<N;++j)
			{
				if(y[i]<y[j]) // Place larger than y[i] on the location of y[i]
				{
					// exchange y[i] and y[j]
					s = y[i];
					y[i] = y[j];
					y[j] = s;
				}
			}
			// y[i] will be the ith large element
			
		}
		
		t2 = clock();
		T1 = (t2-t1)/(double) CLOCKS_PER_SEC;
		printf("Sorting %d elements: %f\n",N, T1);
		for(i=0;i<N;++i)
		{
			printf("y[%d]=%d\n",i,y[i]);
		}
		return 0;
		
		// Assign y = x again
		for(i=0;i<N;++i) y[i] = x[i];
		
		t1 = clock();
		quicksort(y,0,N);
		t2 = clock();
		T2 = (t2-t1)/(double) CLOCKS_PER_SEC;
		for(i=0;i<N;++i)
		{
			printf("y[%d]=%d\n",i,y[i]);
		}
		
		free(x);
		free(y);
	} 

	return 0;
}

int quicksort(int *x, int left, int right)
{
	int i, j, k;
	int pivot, t;
	
	if(left < right-1)
	{
		pivot = x[left];
    	i = left;
    	j = right;
    	// 56970341
    	while(1)
		{
      		while(i < right && pivot >= x[i]) i++; 
      		while(j > left && pivot <= x[j]) j--; 
      		//printf("%d %d %d\n", i,j,pivot);
      		if(i>=j) break;
      		t = x[i];
      		x[i] = x[j];
      		x[j] = t;
			//for(k=left;k<right;++k)
			{
				//printf("x[%d]=%d\n",k,x[k]);
			}
			//system("pause");
        }
        t = x[left];
        x[left] = x[j];
        x[j] = t;
        //printf("%d\n",j);
		for(k=left;k<right;++k)
		{
			//printf("x[%d]=%d\n",k,x[k]);
		}
		//system("pause");
        
        // The worst case scenario is the same operation as bubble sort
		quicksort(x, left, j);
		quicksort(x, j+1, right);
    }
    else 
    {
    	return 1;
	}
}
