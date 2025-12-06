#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>


void compute(unsigned long long &total, std::string &num, char operand)
{
	size_t start = num.find_first_not_of(' ');
	size_t end = num.find_last_not_of(' ');
	std::string number = num.substr(start, end - start + 1);
	switch (operand)
	{
	case '*':
		total *= std::stoull(number);
		break;
	case '+':
		total += std::stoull(number);
		break;
	}
}

int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	std::vector<std::string> preProcessed;

	std::vector<size_t> offsets;
	std::vector<std::vector<std::string>> problems;
	unsigned long long grandTotal1 = 0;
	unsigned long long grandTotal2 = 0;

	std::string line;
	std::string token;
	bool problemsInitialized = false;
	while (std::getline(file, line))
	{
		if (!problemsInitialized)
		{
			problemsInitialized = true;
			std::istringstream temp(line);
			int numProblems = 0;
			while (temp >> token) numProblems++;
			problems.resize(numProblems);
		}

		preProcessed.push_back(line);
	}

	std::string operands = preProcessed.back();
	size_t len = 0, previous = 0;
	for (size_t i = 1; i < operands.size(); i++)
	{
		if (operands[i] == '*' || operands[i] == '+')
		{
			offsets.push_back(i - previous - 1);
			previous = i;
		}
	}
	offsets.push_back(operands.size() - previous);


	for (auto &&line : preProcessed)
	{
		size_t row = 0;
		for (int j = 0; j < line.size(); j += offsets[row++] + 1)
		{
			problems[row].push_back(line.substr(j, offsets[row]));
		}
	}
	size_t current = 0;
	for (auto &&problem : problems)
	{
		unsigned long long total1 = 0, total2 = 0;
		char operand = problem[problem.size() - 1][0];
		if (operand == '*') { total1 = 1; total2 = 1; }


		for (size_t i = 0; i < problem.size() - 1; i++)
		{
			compute(total1, problem[i], operand);
		}

		for (size_t j = 0; j < offsets[current]; j++)
		{
			std::string str;
			for (size_t i = 0; i < problem.size() - 1; i++)
			{
				str.reserve(offsets[current] - 1);
				char c = problem[i][j];
				if (c == ' ') continue;
				str += c;
			}
			compute(total2, str, operand);
		}
		
		grandTotal1 += total1;
		grandTotal2 += total2;
		current++;
	}
	
	std::cout << "Grand total for task 1: " << grandTotal1 << "\n";
	std::cout << "Grand total for task 2: " << grandTotal2 << "\n";

	return 0;
}