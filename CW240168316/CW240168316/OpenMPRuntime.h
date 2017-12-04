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

class OpenMPRuntime
{
public:
	OpenMPRuntime();
	~OpenMPRuntime();

	// Methods which are called by from main and run the four algorithms using OpenMP Parallel For
	void wheelFactorizationOpenMPRuntime(int n);
	void sundaramOpenMPRuntime(int inputNumber);
	void atkinOpenMpRuntime(int limit);
	void eratosthenesOpenMPRuntime(int n);
};

