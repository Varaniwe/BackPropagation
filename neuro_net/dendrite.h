#pragma once
#ifndef MYHEADER1_H
#define MYHEADER1_H

#include <ctime>
#include <random>


class neurone;


class dendrite
{
private:
	neurone* source_node;
	neurone*  dest_node;

	double weight;
public:
	dendrite();
	dendrite(neurone* p_i, neurone* p_o);
	~dendrite();

	neurone* get_source();
	neurone* get_dest();
	void set_inp_outp(neurone* p_i, neurone* p_o);
	double get_weight();
	void correct_weight(double d);
};


#endif