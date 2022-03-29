int date()
{
	static int count = 0;   // initialized only once across all calls
	return ++count;
}