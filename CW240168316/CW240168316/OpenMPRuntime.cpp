#include "stdafx.h"
#include "OpenMPRuntime.h"


OpenMPRuntime::OpenMPRuntime()
{
}


OpenMPRuntime::~OpenMPRuntime()
{
}

// Wheel Factorisation OpenMp Parallel Runtime For Method
void OpenMPRuntime::wheelFactorizationOpenMPRuntime(int n)
{
	// Create a billion ints
	int* primes = new int[n];

	// Get the number of threads the hardware can natively support
	auto num_threads = thread::hardware_concurrency();
	// For all elements in array
	// OpenMP statement must be placed here - doesnt work at inner for loop where initial alaysis identied
#pragma omp parallel for schedule(runtime) num_threads(num_threads)
	for (int p = 2; p < n; p++)
	{
		// It is not multiple of any other prime
		if (primes[p] == 0)
		{
			// Mark it as prime
			primes[p] = 1;
		}

		// Mark all multiples of prime selected above as non primes
		// Set c to 2
		int c = 2;
		// Get multiples by multiplying p by c
		int mul = p * c;
		// while mul is less than n
		for (; mul < n;)
		{
			// make primes mul equal minus one
			primes[mul] = -1;
			// Increment c
			c++;
			// Reset mul to p multiplied by c as c has now changed
			mul = p * c;
		}
	}

	// Create the output file for the prime numbers to be stored
	ofstream data("data.csv", ofstream::out);
	// Loop through numbers one to a billion
	// For i equal zero; while i is less than a billion; increment i
	for (int i = 0; i < n; i++)
	{
		// If primes[number] equals one then increment c - output 
		if (primes[i] == 1)
		{
			data << i << endl;
		}
	}

	// Delete the prime number bools
	delete[] primes;
}

// Sieve Sundaram OpenMp Parallel For Runtime Method
void OpenMPRuntime::sundaramOpenMPRuntime(int inputNumber)
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

	// OpenMP parallel For statement must go here has if placed on inner for loop, results are effected 
#pragma omp parallel for schedule(runtime) num_threads(num_threads)
	// For i equals one; while i is less than n (calculated above); increment i
	for (int i = 1; i < n; ++i)
	{
		// for j equals i; while j is less than or equal to n minus 1 divided by 2 times i pluys 1; increment j
		for (int j = i; j <= (n - i) / (2 * i + 1); ++j)
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
	// Create the output file for the prime numbers to be stored
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

// Seive Atkin OpenMp Parallel Runtime For Method
void OpenMPRuntime::atkinOpenMpRuntime(int n)
{
	// Get the number of threads the hardware can natively support
	auto num_threads = thread::hardware_concurrency();

	// Create a boolean of one billion and one prime numbers
	vector<bool> is_prime(n + 1);
	// Set booleans at index two and three to true
	is_prime[2] = true;
	is_prime[3] = true;

	// From 5 to one billion, set all the values to false
	for (int i = 5; i <= n; i++)
	{
		is_prime[i] = false;
	}

	// Get the limit by square rooting n 
	int lim = ceil(sqrt(n));
	// For x equals one; while x is less than or equal to the limit; increment x
	// OpenMP parallel for placed here because it can effect output if placed in inner for loop
#pragma omp parallel for scheduleschedule(runtime) num_threads(num_threads) 
	for (int x = 1; x <= lim; x++)
	{
		// For y equals one; while y is less than or equal to the limit; increment y
		for (int y = 1; y <= lim; y++)
		{
			// Main part of Sieve of Atkin - make n equal to 4 time x squared plus y squared
			int num = (4 * x * x + y * y);
			// If num is less than or equal too 1 billion and if num divided by 12 is remainder 1 or remadiner 5 then make is_prime[num] equal to true
			if (num <= n && (num % 12 == 1 || num % 12 == 5))
			{
				is_prime[num] = true;
			}

			// Make n equal 3 time n squared plus y squared
			num = (3 * x * x + y * y);
			// If num is less than or equal too 1 billion and if num divided by 12 is remainder 7 then make is_prime[num] equal to true
			if (num <= n && (num % 12 == 7))
			{
				is_prime[num] = true;
			}

			// If x is great than y
			if (x > y)
			{
				// Make n equal 3 time n squared plus y squared
				num = (3 * x * x - y * y);
				// If num is less than or equal too 1 billion and if num divided by 12 is remainder 11 then make is_prime[num] equal to true
				if (num <= n && (num % 12 == 11))
				{
					is_prime[num] = true;
				}
			}
		}
	}

	// For i is equal to 5; i is less than or equal to the limit; increment i
	for (int i = 5; i <= lim; i++)
	{
		// If is_prime 5 to a billion is true then
		if (is_prime[i])
		{
			// for j equals i squared; while j is less than or equal to n; j plus equals i make is_prime[j] equal to false 
			for (int j = i * i; j <= n; j += i)
			{
				is_prime[j] = false;
			}
		}
	}

	// Output the data if the values are prime numbers 
	ofstream data("data.csv", ofstream::out);
	for (int i = 2; i <= n; i++)
	{
		if (is_prime[i])
		{
			data << i << endl;
		}
	}
}

// Wheel Factorisation OpenMp Runtime Parallel For Method
void OpenMPRuntime::eratosthenesOpenMPRuntime(int n)
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
			// OpenMp Parallel For loop works fine here as identified in inital analysis
#pragma omp parallel for schedule(runtime) num_threads(num_threads)
			// Update all multiples of p
			for (int i = p * 2; i <= n; i += p)
			{
				prime[i] = false;
			}
		}
	}

	// Create the output file
	ofstream data("data.csv", ofstream::out);
	// Print all prime numbers
	for (int p = 2; p <= n; p++)
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