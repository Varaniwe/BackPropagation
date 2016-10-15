#pragma once
#include "utils.h"

double act_funct(double x)
{
	return 1.0 / (1.0 + std::exp(-x));
}


double derivativ(double x)
{
	return x * (1.0 - x);
}

double fRand(double fMin, double fMax)
{
	double f = (double)std::rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}