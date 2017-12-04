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

class OpenMPStatic
{
public:
	OpenMPStatic();
	~OpenMPStatic();

	// Methods which are called by from main and run the four algorithms using OpenMP Parallel For
	void wheelFactorizationOpenMPStatic(int n);
	void sundaramOpenMPStatic(int inputNumber);
	void atkinOpenMpStatic(int limit);
	void eratosthenesOpenMPStatic(int n);
};

