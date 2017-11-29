#include "stdafx.h"
#include "openMP.h"

openMP::openMP()
{
}


openMP::~openMP()
{
}

void openMP::sundaramOpenMP(int inputNumber)
{
	// Set the initial variables
	int TheseArePrime = 0; // variable used in the array that stores the prime numbers found
	int totalPrimes = 0; // total number of prime numbers that are found
	// Get n which is the inout number divided by 2
	int n = inputNumber / 2;

	// Create a billion ints
	int* isPrime = new int[inputNumber];

	// Get the number of threads the hardware can natively support
	auto num_threads = thread::hardware_concurrency();

	// Fill the array with a list of integers up to the inputNumber  
	// For i equals zero; while i is less then 1 billion; increment i
	for (int i = 0; i < inputNumber; i++)
	{
		isPrime[i] = i + 1;
	}

	// For i equals one; while i is less than n (calculated above); increment i
	for (int i = 1; i < n; i++)
	{
//#pragma omp parallel for num_threads(num_threads) 
		// for j equals i; while j is less than or equal to n minus 1 divided by 2 times i pluys 1; increment j
		for (int j = i; j <= (n - i) / (2 * i + 1); j++)
		{
			isPrime[i + j + 2 * i * j] = 0;/*From this list, remove all numbers of the form i + j + 2ij */
		}
	}

	// If the input is greater than or equal to two then 
	if (inputNumber >= 2)
	{
		isPrime[TheseArePrime++] = 2;/*this IF statement adds 2 to the output since 2 is a prime number    */
		totalPrimes++;
	}

	// For i equal 1; while i is less than n; increment i
	for (int i = 1; i < n; i++)
	{
		// If isPrime[i] is not equal to zero then
		if (isPrime[i] != 0)
		{
			//The remaining numbers are doubled and incremented by one, giving a list of the odd prime numbers 
			// (i.e., all primes except the only even prime 2) below 2n + 2.

			isPrime[TheseArePrime++] = i * 2 + 1;
			totalPrimes++; // the counter of the number of primes found
		}
	}

	// Output Prime Numbers
	 //Create the output file for the prime numbers to be stored
	ofstream data("data.csv", ofstream::out);
	// For the total number of primes
	for (int x = 0; x < totalPrimes; x++)
	{
	// If the prime number does not equal zero then output - else then break
		if (isPrime[x] != 0)
		{
			data << isPrime[x] << endl;
		}
		else
		{
			break;
		}
	}

	// Delete the prime number bools
	delete[] isPrime;
}

void openMP::atkinOpenMp(int limit)
{
	// Get the number of threads the hardware can natively support
	auto num_threads = thread::hardware_concurrency();

	// Initialise and set the sieve array with false values
	bool* sieve = new bool[limit];

	int i;

#pragma omp parallel for num_threads(num_threads)
	for (i = 0; i < limit; i++)
	{
		sieve[i] = false;
	}

	// Make sieve[n] true if one of the following coditions is true:
	// a) n = (4*x*x)+(y*y) has odd number of solutions, i.e., there exist odd number of distinct pairs (x, y) that satisfy the equation and n % 12 = 1 or n % 12 = 5.
	// b) n = (3*x*x)+(y*y) has odd number of solutions and n % 12 = 7
	// c) n = (3*x*x)-(y*y) has odd number of solutions, x > y and n % 12 = 11 */
	// For x equal 1; while x squared is less than 1 billion; increment x
	int limitSQRT = sqrt(limit);
#pragma omp parallel for num_threads(num_threads)
	for (int x = 1; x < limitSQRT; x++)
	{
		// For y equal 1; while y squared is less than 1 billion; increment y
		for (int y = 1; y*y < limit; y++)
		{
			// Main part of Sieve of Atkin - make n equal to 4 time x squared plus y squared
			int n = (4 * x*x) + (y*y);
			// If n is less than or equal too 1 billion and if n divided by 12 is remainder 1 or remadiner 5 then make sieve[n] equal to true
			if (n <= limit && (n % 12 == 1 || n % 12 == 5))
			{
				sieve[n] ^= true;
			}

			// Make n equal 3 time n squared plus y squared
			n = (3 * x*x) + (y*y);
			// If n is less than or equal too a billion and if n divided by 12 is remainder 7 then make sieve[n] equal to true
			if (n <= limit && n % 12 == 7)
			{
				sieve[n] ^= true;
			}

			// Make n equal 3 time n squared plus y squared
			n = (3 * x*x) - (y*y);
			// If n is less than or equal too a billion and if n divided by 12 is remainder 11 then make sieve[n] equal to true
			if (x > y && n <= limit && n % 12 == 11)
			{
				sieve[n] ^= true;
			}
		}
	}

	// Mark all multiples of squares as non-prime
	// for r = 5; while r squared is less than a billion; increment r
#pragma omp parallel for num_threads(num_threads)
	for (int r = 5; r < limitSQRT; r++)
	{
		// If sieve[r] is equal to true then
		if (sieve[r])
		{
			// for i = r squared; i is less than 1 billion; i += r squared then make sieve[i] equal to false
			for (int i = r*r; i < limit; i += r*r)
			{
				sieve[i] = false;
			}
		}
	}

	//// Create the output file
	//ofstream data("data.csv", ofstream::out);
	////// Output all the prime numbers 
	////// 2 and 3 are known to be prime so output them first to the file
	//if (limit > 2)  data << 2 << endl;
	//if (limit > 3)  data << 3 << endl;
	////// For a = 5; while a is less than 1 billion; increment a
	//for (int a = 5; a < limit; a++)
	//{
	//	// If sieve[a] is equal to true then output to the data file
	//	if (sieve[a])
	//	{
	//		//cout << a << endl;
	//		data << a << endl;
	//	}
	//}

	// Delete the prime number bools
	delete[] sieve;
}

void openMP::eratosthenesOpenMP(int n)
{
	// Setup 1 billion and one booleans
	bool* prime = new bool[n + 1];
	// Memset sets a billion bytes of the block of memory pointed by prime to the value of true
	memset(prime, true, sizeof(bool) * (n + 1));

	// Get the number of threads the hardware can natively support
	auto num_threads = thread::hardware_concurrency();
	// Start p at 2 (the first prime numer); while p squared is less than or equal to a billion; increment p
	for (int p = 2; p*p < n; p++)
	{
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true)
		{
#pragma omp parallel for num_threads(num_threads)
			// Update all multiples of p
			for (int i = p * 2; i <= n; i += p)
			{
				prime[i] = false;
			}
		}
	}

	// Create the output file
	//ofstream data("data.csv", ofstream::out);
	//// Print all prime numbers
	//for (int p = 2; p <= n; p++)
	//{
	//	// If boolean is true then 
	//	if (prime[p])
	//	{
	//		// Output the prime number to the file
	//		data << p << endl;
	//	}
	//}

	// Delete the prime number bools
	delete[] prime;
}