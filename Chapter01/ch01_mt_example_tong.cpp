#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>

using namespace std;


// --- Globals
mutex values_mtx;
mutex cout_mtx;

typedef struct result{
	int tid;
	int value;
} result;

vector<result> values;

int randGen(const int& min, const int& max) {
    static thread_local mt19937 generator(hash<thread::id>()(this_thread::get_id()));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

void threadFnc(int tid) {

	result val;
	val.tid = tid;
	val.value = 0;

	// Calculate the result.
	cout_mtx.lock();
	cout << "Starting thread " << tid << ".\n";
	cout_mtx.unlock();
	
	values_mtx.lock();
	val.value = values[0].value;
	values_mtx.unlock();
	
	int rval = randGen(0, 10);
	val.value += rval;
	
	cout_mtx.lock();
	cout << "Thread " << tid << " adding " << rval << ". New value: " << val.value << ".\n";
	cout_mtx.unlock();
	
	values_mtx.lock();
	values.push_back(val);
	values_mtx.unlock();
}


int main() {
	// Set global data in queue.
	// Init Value : 42
	result init;
	init.tid = 0;
	init.value = 42;
	values.push_back(init);
	
	// Start the threads, wait for them to finish.
	thread tr1(threadFnc, 1);
	thread tr2(threadFnc, 2);
	thread tr3(threadFnc, 3);
	thread tr4(threadFnc, 4);
	
	tr1.join();
	tr2.join();
	tr3.join();
	tr4.join();
	
	// Read the calculated values.
	cout << "Input: " << values[0].value 
	<< ", Result" << values[1].tid << ": "<<values[1].value 
	<< ", Result" << values[2].tid << ": "<<values[2].value 
	<< ", Result" << values[3].tid << ": "<<values[3].value 
	<< ", Result" << values[4].tid << ": "<<values[4].value 
	<< "\n";
	
	return 1;
}
