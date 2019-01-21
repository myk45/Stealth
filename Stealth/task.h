#pragma once

#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <cassert>
#include <condition_variable>

class Task
{
public:
	virtual bool doTask() = 0;
};

class PrintTask : public Task {
public:
	virtual bool doTask()
	{
		//std::cout << "hello\n";

		float a, b;
		for (int i = 0; i < 10000000; i++) {
			a = sin(i) * cos(i) * tan(i);
			b = cos(a) * sin(a) * tan(a);
		}
		std::cout << a*b;

		return true;
	}
};
