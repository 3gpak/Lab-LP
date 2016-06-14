// LABA7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <Windows.h>
#include <condition_variable>


using namespace std;

mutex f1,f2,f;
condition_variable cv;
bool ready = false;


void VivoB(mutex& m1, mutex& m2)
{
	lock_guard <mutex> l1(m1);
	this_thread::sleep_for(chrono::milliseconds(100));
	lock_guard <mutex> l2(m2);
	cout << "Hello1" << endl;
	}

void VivoA(mutex& m1, mutex& m2)
{
	lock_guard <mutex> l2(m2);
	this_thread::sleep_for(chrono::milliseconds(100));
	lock_guard <mutex> l1(m1);
	cout << "Hello2" << endl;
}
void VivodB()
{
	unique_lock<mutex> lck(f);
	for (int i = 0; i < 10; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "bbbbb";
	}
	ready = true;
	lck.unlock();
	cv.notify_one();
	for (int j = 0; j < 5; j++)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "bbbbb";
	}
}

void VivodA()
{
	unique_lock<mutex> lck(f);
	cv.wait(lck, [] {return ready; });
	for (int i = 0; i < 5; i++)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		cout << "aaaaa";
	}
}


int main()
{
	thread thr1(VivodB);
	thread thr2(VivodA);
	thread thr3(VivoB, f1, f2);
	thread thr4(VivoA, f1, f2);
	thr1.join();
	thr2.join();
	thr3.join();
	thr4.join();
	system("pause");
	return 0;
}

