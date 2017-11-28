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

using namespace std;
using namespace std::chrono;

// Create a mutex as a global variable
mutex mut;

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
	// Create the output file
	ofstream data("data.csv", ofstream::out);
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	bool* prime = new bool[n + 1];
	// Memset sets a billion bytes of the block of memory pointed by prime to the value of true
	memset(prime, true, sizeof(bool) * (n+1));

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

	// Print all prime numbers
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

void EratosthenesThreaded(int n, int g, int iterations)
{
	// Create the output file
	ofstream data("data.csv", ofstream::out);
	// Create a boolean array "prime[0..n]" and initialize
	// all entries it as true. A value in prime[i] will
	// finally be false if i is Not a prime, else true.
	bool* prime = new bool[n + 1];
	// Memset sets a billion bytes of the block of memory pointed by prime to the value of true
	memset(prime, true, sizeof(bool) * (n + 1));

	// Start p at 2 (the first prime numer); while p squared is less than or equal to a billion; increment p
	for (int p = 2 * iterations; p*p <= (g + 1) * iterations; ++p)
	{
		// If prime[p] is not changed, then it is a prime
		if (prime[p] == true)
		{
			// Update all multiples of p
			for (int i = p * 2; i <= n; i += p)
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

void SieveOfEratosthenesThreaded(int n)
{
	// Create the output file
	ofstream data("data.csv", ofstream::out);

	// Create number of threads hardware natively supports
	auto num_threads = thread::hardware_concurrency();
	// Create a vector of threads
	vector<thread> threads;

	auto iterations = n / num_threads;
	// Loop through the number of threads minus 1 - i is id/iteration of the thread 
	for (int i = 0; i < num_threads - 1; ++i)
	{
		// Add a thread to the end of the list with multiple paramaters - note a reference has been used to pass in the pixels vector like in the workbook
		threads.push_back(thread(EratosthenesThreaded, n, i, iterations));
	}

	// Join the threads 
	for (auto &t : threads)
	{
		t.join();
	}

	//EratosthenesThreaded(n, prime);

	// Print all prime numbers
	//for (int p = 2; p <= n; p++)
	//{
	//	// If boolean is true then 
	//	if (prime[p])
	//	{
	//		// Output the prime number to the file
	//		data << p << endl;
	//	}
	//}
}

// Code taken from http://www.geeksforgeeks.org/sieve-of-atkin/
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
void SieveOfAtkin(int limit)
{
	// Create the output file for the prime numbers to be stored
	ofstream data("data.csv", ofstream::out);

	// 2 and 3 are known to be prime so output them first to the file
	if (limit > 2)  data << 2 << " ";
	if (limit > 3)  data << 3 << " ";

	// Initialise and set the sieve array with false values
	bool* sieve = new bool[limit];
	for (int i = 0; i < limit; i++)
	{
		sieve[i] = false;
	}

	// Make sieve[n] true if one of the following coditions is true:
	// a) n = (4*x*x)+(y*y) has odd number of solutions, i.e., there exist odd number of distinct pairs (x, y) that satisfy the equation and n % 12 = 1 or n % 12 = 5.
	// b) n = (3*x*x)+(y*y) has odd number of solutions and n % 12 = 7
	// c) n = (3*x*x)-(y*y) has odd number of solutions, x > y and n % 12 = 11 */
	// For x equal 1; while x squared is less than 1 billion; increment x
	for (int x = 1; x*x < limit; x++)
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
	for (int r = 5; r*r < limit; r++)
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

	// Output all the prime numbers 
	// For a = 5;while a is less than 1 billion; increment a
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

// Code taken from http://bcbutler.com/CPP_Tuts/c_plus_plus_sieve_of_sundaram.php 
// Thoery take from http://www.geeksforgeeks.org/sieve-sundaram-print-primes-smaller-n/
// Sieve Of Sundaram is a method which takes in a number - which in this case is 1 billion and then prints all the prime numbers that are smaller than or equal to n.
// Sieve of Sundaram works by taking n and then halving it as we want primes smaller then the inputNumber. It then marks all the numbers of the form i + j + 2ij as true
// where 1 <= i <= j.

// Note that the code has been slightly modified as a billion booleans need to be made

// Sieve of Sundaram which takes in the value of 1 billion
void SieveOfSundaram(int inputNumber)
{
	// Create the output file for the prime numbers to be stored
	ofstream data("data.csv", ofstream::out);

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
		// totalPrimes++;
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
	// For the total number of primes
	//for (int x = 0; x < totalPrimes; x++)
	//{
	// If the prime number does not equal zero then output - else then break
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
	// Create the output file
	ofstream times("times.csv", ofstream::out);
	
	// For the 20 runs
	for (int i = 0; i < 1; i++)
	{
		// Start timing from this part of the algorithm. This is because some tests require more spheres than others.
		auto start = system_clock::now();

		// Call the method which finds prime numbers using the Sieve of Atkin Algorithm
		//int limit = 1000000000;
		//SieveOfAtkin(limit);

		// Call the method which finds prime numbers using the Sieve of Eratosthenes Algorithm
		//SieveOfEratosthenes(1000000000);
		SieveOfEratosthenesThreaded(1000000000);

		// Call the method which finds prime numbers using the Sieve of Sundaram Algorithm
		//int n = 1000000000;
		//SieveOfSundaram(n);

		// End timing here as the algorithm has complete. 
		auto end = system_clock::now();

		// Get total time
		auto total = end - start;

		// Output that time to a file
		times << duration_cast<milliseconds>(total).count() << endl;
		//cout << duration_cast<milliseconds>(total).count() << endl;
	}	

    return 0;
}