#include "nn.h"

#include <iostream>

int main()
{
	srand(std::time(NULL));

	while (true)
	{
		nn net(3, 2, 2, 1);

		// build XOR table
		net.add_trainset({ 0.0, 0.0 }, { 0.0 });
		net.add_trainset({ 1.0, 0.0 }, { 1.0 });
		net.add_trainset({ 0.0, 1.0 }, { 1.0 });
		net.add_trainset({ 1.0, 1.0 }, { 0.0 });

		net.train(20000);
		
		net.add_testset({ 0.0, 0.0 }, { 0.0 });
		net.add_testset({ 1.0, 0.0 }, { 1.0 });
		net.add_testset({ 0.0, 1.0 }, { 1.0 });
		net.add_testset({ 1.0, 1.0 }, { 0.0 });

		net.set_delta(0.2);
		if (!net.test())
		{
			std::cout << "not success" << std::endl;
			continue;
		}
		std::cout << "test 1^1 " << net.test({ 1.0, 1.0 })[0] << " 0 expecting" << std::endl;
		std::cout << "test 0^1 " << net.test({ 0.0, 1.0 })[0] << " 1 expecting" << std::endl;
		std::cout << "test 1^0 " << net.test({ 1.0, 0.0 })[0] << " 1 expecting" << std::endl;
		std::cout << "test 0^0 " << net.test({ 0.0, 0.0 })[0] << " 0 expecting" << std::endl;
		break;
	}	

    return 0;
}