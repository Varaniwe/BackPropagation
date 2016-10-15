#include "neurone.h"


neurone::neurone()
{
	error_cahced = false;
	output_cahced = false;
	bias = fRand(0, 1);
}


neurone::~neurone()
{
}

neurone::neurone(int p_input_count) 
{
	error_cahced = false;
	output_cahced = false;
	bias = fRand(0, 1);
}


double neurone::calc_output()
{
	if (output_cahced || inputs.size() == 0)
		return output;

	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		inputs[i]->get_source()->calc_output();
	}
	weighted_sum = 0;
	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		weighted_sum += inputs[i]->get_source()->calc_output() * inputs[i]->get_weight();
	}
	weighted_sum += bias;
	output = act_funct(weighted_sum);
	
	output_cahced = true;
	return output;
}

double neurone::get_weighted_sum()
{
	return weighted_sum;
}


void neurone::set_cahced(bool b)
{
	output_cahced = b;
	error_cahced = b;
}

void neurone::add_input_dendrite(dendrite * d)
{
	inputs.push_back(d);
}

void neurone::add_output_dendrite(dendrite * d)
{
	outputs.push_back(d);
}


double neurone::calc_error()
{
	if (error_cahced || outputs.size() == 0  || inputs.size() == 0)
		return error;

	error = 0;
	for (unsigned int i = 0; i < outputs.size(); ++i)
	{
		error += derivativ( output) * outputs[i]->get_dest()->calc_error() *  outputs[i]->get_weight();
	}
	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		inputs[i]->correct_weight (error * inputs[i]->get_source()->calc_output());
	}
	bias += error;
	error_cahced = true;

	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		inputs[i]->get_source()->calc_error();
	}
	
	return error;

}

void neurone::set_error(double d)
{
	error = output * (1 - output) * d;
	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		inputs[i]->correct_weight(error * inputs[i]->get_source()->calc_output());
	}
	bias += error;
	for (unsigned int i = 0; i < inputs.size(); ++i)
	{
		inputs[i]->get_source()->calc_error();
	}
}

void neurone::set_value(double d)
{
	output = d;
}


bool neurone::is_input()
{
	return inputs.size() == 0;
}
