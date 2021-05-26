#pragma once
#include"Queue.h"
#include <fstream>
#include <stdexcept>
#include <float.h>
#define INF (DBL_MAX) // to declare infinity value for not-existing nodes
using namespace std;
class FB
{
private:
	size_t Size;
	string* towns;
	double** weights;
	void set_size(size_t);
	void set_cities(string*);
	void set_weights(double**);
	FB();
public:
	FB(string); // input file name
	size_t get_size();
	string* get_cities();
	double** get_weights();
	size_t get_city_index(string);
	double FordBellman(string, string); // originating and arriving towns
};