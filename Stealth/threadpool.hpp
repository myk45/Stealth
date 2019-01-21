#ifndef _THREAD_POOL_
#define _THREAD_POOL_

#include "task.h"

class ThreadPool
{
public:
	void workFunction()
	{
		while (!_done)
		{
			Task* t = nullptr;
			{
				std::unique_lock<std::mutex> lk(_taskListMutex);
				_threadCV.wait(lk, [&] { return !_taskList.empty() && !_done; });

				static int count = 0;
				std::cout << count++ << ") TID: " << std::this_thread::get_id() << std::endl;

				t = _taskList.back();
				_taskList.pop_back();
			}
		
			t->doTask();	
		}
	}

	bool create(int numThreads)
	{
		assert(numThreads);

		for (int i = 0; i < numThreads; i++)
		{
			std::thread* threadObj = new std::thread(&ThreadPool::workFunction, this);
			_threads.push_back(threadObj);
		}
		return true;
	}

	bool addTask(Task* t)
	{
		std::lock_guard<std::mutex> guard(_taskListMutex);
		_taskList.push_back(t);

		_threadCV.notify_one();
		return true;
	}

	ThreadPool() :
		_done(false)
	{

	}

	~ThreadPool()
	{
		for (auto& itr : _threads) {
			itr->join();
		}

		_done = true;
	}

private:
	std::vector<Task*>			_taskList;
	std::vector<std::thread*>	_threads;
	int							_numThreads;
	std::mutex					_taskListMutex;
	std::condition_variable		_threadCV;
	bool						_done;
};

#endif // _THREAD_POOL_