#include "task.h"
#include "threadpool.hpp"

#include <chrono>

int main()
{
	std::chrono::high_resolution_clock::time_point start, end;
	const int JOB_NUMBER   = 100000;
	const int THREAD_COUNT = 10;

	start = std::chrono::high_resolution_clock::now();	
	{
		ThreadPool tp;

		tp.create(THREAD_COUNT);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		for (int i = 0; i < JOB_NUMBER; i++)
		{
			tp.addTask(new PrintTask);
		}

		std::cout << "Sleeping for 5 seconds..." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(5));
		std::cout << "Adding another few jobs..." << std::endl;
		for (int i = 0; i < JOB_NUMBER; i++)
		{
			tp.addTask(new PrintTask);
		}

	}
	end = std::chrono::high_resolution_clock::now();

	std::cout << "\nTime for execution: ";
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    return 0;
}

