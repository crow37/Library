#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>
#include <mutex>


using namespace std;

#ifdef EXPORTS_EXPORTS
#define EXPORTS_API __declspec(dllexport) 
#else
#define EXPORTS_API __declspec(dllimport) 
#endif
