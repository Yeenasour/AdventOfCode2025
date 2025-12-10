#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


struct Machine
{
	unsigned int lightMap;
	std::vector<unsigned int> buttonMasks;
	std::vector<unsigned int> joltages;

	Machine(std::string specification)
	{
		lightMap = 0;
		size_t lightsEnd = specification.find(']');
		std::string lights = specification.substr(1, lightsEnd - 1);
		for (size_t i = 0; i < lights.size(); i++)
		{
			this->lightMap += (lights[i] == '#') << i;
		}
		
		size_t lastButton = 0;
		while (true)
		{
			size_t currentButtonStart = specification.find('(', lastButton + 1);
			if (currentButtonStart == specification.npos) break;
			size_t currentButtonEnd = specification.find(')', currentButtonStart + 1);
			std::string button = specification.substr(currentButtonStart + 1, currentButtonEnd - currentButtonStart - 1);
			unsigned int mask = 0;
			std::string temp("");
			for (char c: button)
			{
				if (c == ',')
				{
					unsigned int val = static_cast<unsigned int>(std::stoul(temp));
					mask |= 1 << val;
					temp.clear();
				}
				else
				{
					temp += c;
				}
			}
			unsigned int val = static_cast<unsigned int>(std::stoul(temp));
			mask |= 1 << val;
			
			this->buttonMasks.push_back(mask);
			
			lastButton = currentButtonEnd + 1;
		}

		size_t joltageStart = specification.find('{');
		size_t joltageEnd = specification.find(')');
		std::string button = specification.substr(joltageStart + 1, joltageEnd - joltageStart - 1);
		unsigned int mask = 0;
		std::string temp("");
		for (char c: button)
		{
			if (c == ',')
			{
				joltages.push_back(static_cast<unsigned int>(std::stoul(temp)));
				temp.clear();
			}
			else
			{
				temp += c;
			}
		}
		joltages.push_back(static_cast<unsigned int>(std::stoul(temp)));
	}
};

unsigned int solveLights(Machine &machine)
{
	std::vector<unsigned int> &masks = machine.buttonMasks;
	for (int nButtons = 1; nButtons <= masks.size(); nButtons++)
	{
		bool foundCombination = false;
		std::vector<unsigned int> bitmask(nButtons, 1);
		bitmask.resize(machine.buttonMasks.size(), 0);
		std::sort(bitmask.begin(), bitmask.end());
		do
		{
			unsigned int lightMap = machine.lightMap;
			for (size_t i = 0; i < masks.size(); i++)
			{
				if (bitmask[i]) lightMap ^= masks[i];
			}
			if (!lightMap)
			{
				return nButtons;
			}
		}
		while (std::next_permutation(bitmask.begin(), bitmask.end()));
	}
	return -1;
}

unsigned int solveJoltage(Machine &Machine)
{
	/*
		To solve I would need to use some linear solver such as Z3.
		
		Example:
		x1		x3	x4		=	7
					x4	x5	=	5
		x1	x2		x4	x5	=	12
		x1	x2			x5	=	7
		x1		x3		x5	=	2
	*/
	return 0;
}

int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	unsigned int totalLightPresses = 0;
	unsigned int totalJoltagePresses = 0;
	std::vector<Machine> machines;

	std::string line;
	while (std::getline(file, line))
	{
		machines.emplace_back(line);
	}

	for (Machine &machine : machines)
	{
		totalLightPresses += solveLights(machine);
		totalJoltagePresses += solveJoltage(machine);
	}
	
	std::cout << "Fewest light presses: " << totalLightPresses << "\n";
	std::cout << "Fewest joltage presses: " << totalJoltagePresses << "\n";

	return 0;
}