#pragma once

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

class multiThreading
{
public:
	multiThreading();
	~multiThreading();

	void EratosthenesThreaded(int n, int g, int iterations);
};

