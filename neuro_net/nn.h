#pragma once
#include <stdarg.h>
#include <vector>
#include "neurone.h"

class nn
{
private:
	std::vector<std::vector<double>> train_sets;
	std::vector<std::vector<double>> train_expectations;

	double delta;
	// TODO : measure error
	std::vector<std::vector<double>> test_sets;
	std::vector<std::vector<double>> test_expectations;
public:
	nn();
	~nn();

	nn(int count, ...);
	void set_delta(double d);
	void set_input(std::vector<double>);
	void set_error(int count, ...);
	void set_error(std::vector<double>);
	void set_cahced(bool);
	void train(std::vector<double>, std::vector<double>);
	void train(int n);
	bool test();
	std::vector<double>  test(std::vector<double> data);
	void add_trainset(std::vector<double> set, std::vector<double> exp);
	void add_testset(std::vector<double> set, std::vector<double> exp);

	std::vector<std::vector<neurone>> neurones;
	std::vector<std::vector<dendrite>> dendrites;
};

