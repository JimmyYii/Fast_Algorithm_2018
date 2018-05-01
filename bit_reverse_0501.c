#include <stdio.h>

int main()
{
	bit_reverse(8);
	return;
}

int bit_reverse(int N)
{
    int m,p,q,k;
    m = N/2;						// Bit-Reverse 每次要進位的數字 
    q = m;							// p = 1, q = m (The first need to swap)
    for(p=1;p<N-1;++p)				// p = N -1 is needless
    {
        printf("%d <-> %d\n", p,q);
        if(p < q)
        {
            //swap p and q
        }
        k = m;						// k, used for checking whether (log_2 k + 1)th digit is 1 
        while(q >= k & k > 0)		// if q >= k, (log_2 k + 1)th digit is 1
        {							
            q = q-k;				// 1 -> 0
            k = k/2;				// Check next digit
        }
        q = q+k;
    }
    return 0;
}
