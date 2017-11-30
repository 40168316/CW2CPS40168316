#include "stdafx.h"
#include "multiThreading.h"

multiThreading::multiThreading()
{
}


multiThreading::~multiThreading()
{
}

void multiThreading::EratosthenesThreaded(int n, int g, int iterations)
{
	// Create a mutex as a global variable
	mutex mut;

	// Create the output file
	ofstream data("data.csv", ofstream::out);
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	bool* prime = new bool[n + 1];
	// Memset sets a billion bytes of the block of memory pointed by prime to the value of true
	memset(prime, true, sizeof(bool) * (n + 1));

	// Start p at 2 (the first prime numer); while p squared is less than or equal to a billion; increment p
	for (unsigned int p = 2 * iterations; p*p <= (g + 1) * iterations; ++p)
	{
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true)
		{
			// Update all multiples of p
			for (unsigned int i = p * 2; i <= n; i += p)
			{
				lock_guard<mutex> lock(mut);
				prime[i] = false;
			}
		}
	}

	// Print all prime numbers
	for (int p = 2; p <= n; ++p)
	{
		// If boolean is true then 
		if (prime[p])
		{
			// Output the prime number to the file
			data << p << endl;
		}
	}

	// Delete the prime number bools
	delete[] prime;
}
