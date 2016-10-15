#include "nn.h"

nn::nn() 
{
}

nn::~nn()
{
}

nn::nn(int count, ...)
{
	va_list v_l;
	std::vector<int> vec_l;

	va_start(v_l, count);

	// allocate memory for all neurones and dendrites
	for (int i = 0; i < count; ++i)
	{
		int layer_num = va_arg(v_l, int);
		neurones.push_back(std::vector<neurone>(layer_num));
		if (i > 0)
		{
			dendrites.push_back(std::vector<dendrite>());
		}
	}		
	for (unsigned int i = 0; i < neurones.size() - 1; ++i)
	{
		for (unsigned int j = 0; j < neurones[i].size(); ++j)
		{
			for (unsigned int k = 0; k < neurones[i + 1].size(); ++k)
			{
				dendrites[i].push_back(dendrite());
			}
		}
	}

	for (unsigned int i = 0; i < neurones.size() - 1; ++i)
	{
		int dend_num = 0;
		for (unsigned int j = 0; j <  neurones[i].size(); ++j)
		{
			for (unsigned int k = 0; k < neurones[i + 1].size(); ++k)
			{				
				neurones[i][j].add_output_dendrite(&dendrites[i][dend_num]);
				neurones[i + 1][k].add_input_dendrite(&dendrites[i][dend_num]);
				dendrites[i][dend_num++].set_inp_outp(&neurones[i][j], &neurones[i + 1][k]);
			}
		}
	}
}

void nn::set_delta(double d)
{
	delta = d;
}

void nn::set_input(std::vector<double> data)
{
	for (unsigned int i = 0; i < data.size() && i < neurones[0].size(); ++i)
		neurones[0][i].set_value(data[i]);
}

void nn::set_error(int count, ...)
{
	if (count > neurones.back().size())
		throw std::exception("Too many values");
	va_list v_l;
	va_start(v_l, count);

	for (int i = 0; i < count; ++i)
	{
		neurones.back()[i].set_error(va_arg(v_l, double));		
	}
}

void nn::set_error(std::vector<double> errors)
{
	if (errors.size() > neurones.back().size())
		throw std::exception("Too many values");
	

	for (unsigned int i = 0; i < errors.size(); ++i)
	{
		neurones.back()[i].set_error(errors[i]);
	}
}

void nn::set_cahced(bool val)
{
	for (unsigned int i = 0; i < neurones.size(); ++i)
	{
		for (unsigned int j = 0; j < neurones[i].size(); ++j)
		{
			neurones[i][j].set_cahced(val);
		}
	}
}

void nn::train(std::vector<double> input, std::vector<double> excepting)
{
	set_input(input);
	std::vector<double> errors;

	set_cahced(false);
	for (unsigned int i = 0; i < neurones.back().size(); ++i)
	{
		double result = neurones.back()[i].calc_output();
		errors.push_back(excepting[i] - result);
	}

	set_error(errors);
}

void nn::train(int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (unsigned int j = 0; j < train_sets.size() && j < train_expectations.size();++j)
		{
			train(train_sets[j], train_expectations[j]);
		}
	}
}

bool nn::test()
{
	bool result = true;
	for (unsigned int i = 0; i< test_sets.size() && i < test_expectations.size(); ++i)
	{
		std::vector<double> temp = test(test_sets[i]);
		for (unsigned int j = 0; j < temp.size() && j < test_expectations[i].size(); ++j)
		{
			if (std::abs(temp[j] - test_expectations[i][j]) > delta)
				result = false;
		}
	}
	return result;
}

std::vector<double> nn::test(std::vector<double> data)
{
		set_input(data);

		set_cahced(false);
		std::vector<double> result;

		for (unsigned int i = 0; i < neurones.back().size(); ++i)
		{
			result.push_back(neurones.back()[i].calc_output());
		}
		return result;
}

void nn::add_trainset(std::vector<double> set, std::vector<double> exp)
{
	train_sets.push_back(set);
	train_expectations.push_back(exp);
}

void nn::add_testset(std::vector<double> set, std::vector<double> exp)
{
	test_sets.push_back(set);
	test_expectations.push_back(exp);
}
