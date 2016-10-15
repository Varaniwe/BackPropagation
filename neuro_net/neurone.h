#pragma once
#include <iostream>
#include <vector>
#include "dendrite.h"
#include "utils.h"

class neurone 
{
private:
	double output;
	double error;
	double bias;

	double weighted_sum;
	bool error_cahced;
	bool output_cahced;
	std::vector<dendrite*> inputs;
	std::vector<dendrite*> outputs;
public:
	neurone();
	~neurone();
	neurone(int p_input_count);
	double calc_output();
	double get_weighted_sum();
	
	void set_cahced(bool);
	void add_input_dendrite(dendrite* d);
	void add_output_dendrite(dendrite* d);
	double calc_error();
	void set_error(double d);
	void set_value(double d);
	bool is_input();
};

