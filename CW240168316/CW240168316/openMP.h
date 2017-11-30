#pragma once

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <omp.h>
#include <math.h>


using namespace std;
using namespace std::chrono;

class openMP
{
public:
	openMP();
	~openMP();

	void sundaramOpenMP(int inputNumber);
	void atkinOpenMp(int limit);
	void eratosthenesOpenMP(int n);
};

