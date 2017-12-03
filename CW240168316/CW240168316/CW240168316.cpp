// CW240168316.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include "openMP.h"
#include <omp.h>
#include <math.h>

using namespace std;
using namespace std::chrono;

// Code from taken http://www.sanfoundry.com/cpp-program-implement-wheel-sieve-generate-prime-numbers-between-given-range/
// Theory taken from wiki and above web page

// Wheel factorisation works by adding the first 2 prime numbers of 2 and 3
// It then make n = p * c or n = 2* 3 which gives 6 values. From there factors of 2 are removed which have not already been marked as prime - 4 and 6.
// The alogrithm will generate the next 6 numbers ipto 12 and then again up 18, 24.....
// The algorithm will then go back through once again removing all the multiples of 2 and 3. This is then repeated over and over again leaving the prime numbers.
void WheelFactorization(int n)
{
	// Create a billion ints
	int* primes = new int[n];

	// For all elements in array
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
	//ofstream data("data.csv", ofstream::out);
	//// Loop through numbers one to a billion
	//// For i equal zero; while i is less than a billion; increment i
	//for (int i = 0; i < n; i++)
	//{
	//	// If primes[number] equals one then increment c - output 
	//	if (primes[i] == 1)
	//	{
	//		data << i << endl;
	//	}
	//}

	// Delete the prime number bools
	delete[] primes;
}

// Code taken from http://www.geeksforgeeks.org/sieve-of-eratosthenes/
// SieveOfEratosthenes prints all the prime numbers that are smaller or equal to n. n is the number, which in this case will be a billion, which is passed into the method.
// SieveOfEratosthenes works by creating a list of consecutive integers from 2 to n - 1,000,000,000. It then lets p (which stand orime) equal to 2, the first prime number.
// Starting from p, the algorithm counts up in increments of p and mark each of these numbers greater than p itself in the list. For example, 2p, 3p, 4p.... 
// Note that some of these values may have already been marked. Then find the first number greater than p in the list that is not marked. 
// If there was no such number, stop. Otherwise, let p now equal this number (which is the next prime), and repeat from the start of p.

// Note that the code has been slightly modified as a billion booleans need to be made

// Sieve of Eratosthenes which takes in the value of 1 billion
void SieveOfEratosthenes(int n)
{
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	bool* prime = new bool[n + 1];
	// Memset sets a billion bytes of the block of memory pointed by prime to the value of true
	memset(prime, true, sizeof(bool) * (n + 1));

	// Start p at 2 (the first prime numer); while p squared is less than or equal to a billion; increment p
	for (int p = 2; p*p <= n; p++)
	{
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true)
		{
			// Update all multiples of p
			for (int i = p * 2; i <= n; i += p)
			{
				prime[i] = false;
			}
		}
	}

	// Create the output file
	//ofstream data("data.csv", ofstream::out);
	// ////Print all prime numbers
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

// Code taken from http://www.sanfoundry.com/cpp-program-implement-sieve-atkins/
// Theory take from http://www.geeksforgeeks.org/sieve-of-atkin/
// Sieve Of Atkin is a method which takes in the limit - which in this case is 1 billion, creates results lists filled with 2, 3, 5 and finds the prime numbers.
// The full process of Sieve of atkin works by creating a results list, filled with 2, 3, and 5. The algorithm then creates a sieve list with an entry for each positive integer.
// All entries of this list should initially be marked non prime. For each entry number n in the sieve list, with modulo - sixty reaminer r:
// -If r is 1, 13, 17, 29, 37, 41, 49, or 53, flip the entry for each possible solution to 4x2 + y2 = n.
// -If r is 7, 19, 31, or 43, flip the entry for each possible solution to 3x2 + y2 = n.
// -If r is 11, 23, 47, or 59, flip the entry for each possible solution to 3x2 – y2 = n when x > y.
// -If r is something else, ignore it completely..
// Start with the lowest number in the sieve list. Take the next number in the sieve list still marked prime. Include the number in the results list.
// Square the number and mark all multiples of that square as non prime.Note that the multiples that can be factored by 2, 3, or 5 need not be marked,
// as these will be ignored in the final enumeration of primes. Repeat from the lowest number in the sieve list.

// Note that the code has been slightly modified as a billion booleans need to be made

// Sieve of Atkin which takes in the value of 1 billion
void SieveOfAtkin(int n)
{
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
	//ofstream data("data.csv", ofstream::out);
	//for (int i = 2; i <= n; i++)
	//{
	//	if (is_prime[i])
	//	{
	//		data << i << endl;
	//	}
	//}
}

// Code taken from http://bcbutler.com/CPP_Tuts/c_plus_plus_sieve_of_sundaram.php 
// Thoery take from http://www.geeksforgeeks.org/sieve-sundaram-print-primes-smaller-n/
// Sieve Of Sundaram is a method which takes in a number - which in this case is 1 billion and then prints all the prime numbers that are smaller than or equal to n.
// Sieve of Sundaram works by taking n and then halving it as we want primes smaller then the inputNumber. It then marks all the numbers of the form i + j + 2ij as true
// where 1 <= i <= j.

// Note that the code has been slightly modified as a billion booleans need to be made

// Sieve of Sundaram which takes in the value of 1 billion
void SieveOfSundaram(int inputNumber)
{
	// Set the initial variables
	int TheseArePrime = 0; // variable used in the array that stores the prime numbers found
	//int totalPrimes = 0; // total number of prime numbers that are found
	// Get n which is the inout number divided by 2
	int n = inputNumber / 2;

	// Create a billion ints
	int* isPrime = new int[inputNumber];

	// Fill the array with a list of integers up to the inputNumber  
	// For i equals zero; while i is less then 1 billion; increment i
	for (int i = 0; i < inputNumber; i++)
	{
		isPrime[i] = i + 1;
	}

	// For i equals one; while i is less than n (calculated above); increment i
	for (int i = 1; i < n; i++)
	{
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
		 //totalPrimes++;
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
			//totalPrimes++; // the counter of the number of primes found
		}
	}

	// Output Prime Numbers
	// Create the output file for the prime numbers to be stored
	//ofstream data("data.csv", ofstream::out);
	//// For the total number of primes
	//for (int x = 0; x < totalPrimes; x++)
	//{
	//// If the prime number does not equal zero then output - else then break
	//	if (isPrime[x] != 0)
	//	{
	//		data << isPrime[x] << endl;
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}

	// Delete the prime number bools
	delete[] isPrime;
}

int main()
{
	openMP omp;

	// Create the output file
	ofstream times("times.csv", ofstream::out);

	// Initialise the various input numbers 
	int billion = 1000000000;
	int halfBillion = 500000000;
	int hunMillion = 100000000;

	// For the 20 runs - used to get test data to find the average giving more accurate results to evaluate
	for (int i = 0; i < 1; i++)
	{
		// Start timing from this part of the algorithm. This is because some tests require more spheres than others.
		auto start = system_clock::now();

		// Create a billion ints
		int* primes = new int[billion];

		// For all elements in array
		for (int p = 2; p < billion; p++)
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
			for (; mul < billion;)
			{
				// make primes mul equal minus one
				primes[mul] = -1;
				// Increment c
				c++;
				// Reset mul to p multiplied by c as c has now changed
				mul = p * c;
			}
		}

		// Wheel Factorisation
		// Normal algorithm
		//WheelFactorization(billion);
		// OpenMP
		//omp.wheelFactorization(hunMillion);

		// SieveOfAtkin 
		// Normal algorithm
		//SieveOfAtkin(halfBillion);					
		// OpenMP
		//omp.atkinOpenMp(halfBillion);					

		// SieveOfEratosthenes
		// Normal algorithm
		//SieveOfEratosthenes(billion);			
		// OpenMP algorithm
		//omp.eratosthenesOpenMP(billion);		

		// SieveOfSundaram
		// Normal algorithm
		//SieveOfSundaram(billion);				
		// OpenMP algorithm
		//omp.sundaramOpenMP(hunMillion);

		// End timing here as the algorithm has complete. 
		auto end = system_clock::now();

		// Get total time
		auto total = end - start;

		// Output that time to a file
		times << duration_cast<milliseconds>(total).count() << endl;
	}

	return 0;
}