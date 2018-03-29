// return y = x^n mod p; The form of function... about how to use is below
int function_name(int x, int n, int p);
{
	int i, m;
	m = x % p;
	for(i=1;i<n;++i)
	{
		m = (m * x) % p;
	}
	return m;
}
// Compute n!
int fractorial(int n)
{
	if(n==1)
}
