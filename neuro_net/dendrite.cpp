#include "dendrite.h"
#include "neurone.h"

dendrite::dendrite()
{
	weight = fRand(0, 1);
	source_node = nullptr;
	dest_node = nullptr;
}


dendrite::dendrite(neurone* p_input, neurone* p_output)
{
	source_node = p_input;
	dest_node = p_output;

	weight = fRand(0, 1);
}


dendrite::~dendrite()
{
}

neurone * dendrite::get_source()
{
	return source_node;
}

neurone * dendrite::get_dest()
{
	return dest_node;
}


void dendrite::set_inp_outp(neurone * p_i, neurone * p_o)
{
	source_node = p_i;
	dest_node = p_o;
}

double dendrite::get_weight()
{
	return weight;
}

void dendrite::correct_weight(double d)
{
	weight += d;
}

