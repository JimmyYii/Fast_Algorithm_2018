#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#define DEBUG 1
#define DEBUG2 0
int quicksort1(int *x, int left, int right);
int quicksort2(int *x, int left, int right);

int main()
{
	clock_t t1, t2;				// variables for computing clocks 
	int *x, *y, s, p;
	double T1;
	int i, j, N;

	srand( time(NULL) );

	for(N=10;N<=10;N*=2)
	{
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
		#if DEBUG	// if DEBUG == 1, then compile the following codes 
		for(i=0;i<N;++i)
		{
			printf("x[%d]=%d\n",i,x[i]);
		}
		#endif		// end of if block
		return 0;
		// Bubble sort
		t1 = clock();
		for(i=0;i<N;++i) 
		{
			for(j=i+1;j<N;++j)
			{
				if(y[i]<y[j]) 
				{
					s = y[i];
					y[i] = y[j];
					y[j] = s;
				}
			}
		}
		
		t2 = clock();
		T1 = (t2-t1)/(double) CLOCKS_PER_SEC;
		printf("Sorting %d elements: %f\n",N, T1);
		for(i=0;i<N;++i)
		{
			//printf("y[%d]=%f\n",i,y[i]);
		}
		
		for(i=0;i<N;++i) y[i] = x[i];
		
		t1 = clock();
		quicksort1(y,0,N);
		#if DEBUG
		for(i=0;i<N;++i)
		{
			printf("y[%d]=%d\n",i,y[i]);
		}
		#endif
		t2 = clock();
		T1 = (t2-t1)/(double) CLOCKS_PER_SEC;
		printf("(1)Quick Sorting %d elements: %f\n",N, T1);

		for(i=0;i<N;++i) y[i] = x[i];
		
		t1 = clock();
		quicksort2(y,0,N);
		#if DEBUG
		for(i=0;i<N;++i)
		{
			printf("y[%d]=%d\n",i,y[i]);
		}
		#endif
		t2 = clock();
		T1 = (t2-t1)/(double) CLOCKS_PER_SEC;
		printf("(2)Quick Sorting %d elements: %f\n",N, T1);
		
		free(x);
		free(y);
	} 

	return 0;
}

int quicksort1(int *x, int left, int right)
{
	int i, j, k, pivot, pivot_loc, N = right-left; 
	int *y;
	
	if(left < right-1)
	{
		// Find a pivot first, then place the smaller one in front of it and larger back of it
		//  then ?
		// Then do the left and right of the pivot
		// quicksort (x, left, pivot_location)
		// quicksort (x, pivot_location+1, right)
		y = (int *) malloc(N*sizeof(int));
		pivot_loc = left+(rand() % N);	// if we want random pivot
		pivot = x[pivot_loc];			// put it to the 1st one to use the original code below
		x[pivot_loc] = x[left];
		x[left] = pivot;
		i = 0; j = N-1;
		// x: 5(pivot) 4 4 3 2 7 8 9 10 -> y: 4 4 3 2 (i=4=j) 10 9 8 7
		// x: 4(pivot) 4 4 3 2 7 8 9 10 -> "<" :3 2 (i=2=j) 10 9 8 7 4 4
		// x: 4(pivot) 4 4 3 2 7 8 9 10 -> "<=" :4 4 3 2 (i=4=j) 10 9 8 7
		// x: 5 4 4 3 2 7 8 9 10, pivot_loc = 5, pivot = 7
		// x: 7 4 4 3 2 5 8 9 10 -> y:
		
		for(k=1;k<N;++k)	// k start from 1 not 0
		{
			if(x[left+k] < pivot)	// error may be: (x[k] < pivot) or "<" change to "<="
			{
				y[i] = x[left+k];	// Place it from the start
				i = i + 1;
				// or
				// y[i++] = x[left+k];
				// if, i = i + 1;
				// y[i] = x[left+k];
				// then -> y[++i] = x[left+k];
			}
			else
			{
				y[j] = x[left+k];	// Place it from the end
				j = j - 1;
			}
		}
		y[i] = pivot;
		#if DEBUG
		printf("%d %d %d %d %d\n",left,i,j,pivot,N);
		for(k=0;k<N;++k)
		{
			printf("y[%d]=%d\n",k,y[k]);
		}
		system("pause");
		#endif
		for(k=0;k<N;++k)
		{
			x[left+k] = y[k];
		}
		free(y);
		quicksort1(x,left,left+i);
		quicksort1(x,left+i+1,right);	
	}
	else
	{
		return 1;
	}
}


int quicksort2(int *x, int left, int right)
{
	int i, j, k;
	int pivot, t;
	
	//  
	if(left < right-1)
	{
		pivot = x[left];
    	i = left+1;
    	j = right-1;
    	// 
    	while(1)
		{	// x: 5(pivot) 4 8 3 2 7 3 2 10 -> i=2 (find 8>5), j=7 (exchange x[i], x[j])
			//    5(pivot) 4 2 3 2 7 3 8 10 -> i=5, j=6 (exchange x[i], x[j])
			//	  5(pivot) 4 2 3 2 3 7 8 10 -> i=6, j=5 (no need to exchange!)
			//    3                5 (location: j)
			// x: 4(pivot) 4 8 3 2 7 3 4 10 -> i=2 (find 8>4), j=7 (exchange x[i], x[j])
			//    4(pivot) 4 4 3 2 7 3 8 10 -> i=5, j=6 (exchange x[i], x[j])
			//	  4(pivot) 4 4 3 2 3 7 8 10 -> i=6, j=5 (no need to exchange!)
			//    3                4 (location: j)
			
			// if ��no "="
			// x: 8 2 1 8 7 8 9 4 5 8	i=3, j=9 (exchange x[i], x[j])
			//    8 2 1 8 7 8 9 4 5 8 ...
			// So, at least a "=" is needed
			
      		while(i < right && pivot >= x[i]) i++; // search rightward to find 1st  pivot < x[i]
      		while(j >  left && pivot <  x[j]) j--; // search leftward to find 1st  pivot >= x[j]
      		#if DEBUG 
			printf("%d %d %d\n", i,j,pivot);
			#endif
      		if(i>=j) break;
      		t = x[i];
      		x[i] = x[j];
      		x[j] = t;
      		#if DEBUG
			for(k=left;k<right;++k)
			{
				printf("x[%d]=%d\n",k,x[k]);
			}
			system("pause");
			#endif
        }
        //t = x[left];
        x[left] = x[j];
        x[j] = pivot;
        #if DEBUG
        printf("i=%d,j=%d\n",i,j);
		for(k=left;k<right;++k)
		{
			printf("x[%d]=%d\n",k,x[k]);
		}
		system("pause");
        #endif
		quicksort2(x, left, j);		// Change these 2 for median
		quicksort2(x, j+1, right);
    }
    else 
    {
    	return 1;	// and this
	}
}
