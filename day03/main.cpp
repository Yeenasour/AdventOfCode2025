#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

int main()
{
	std::ifstream file("input.txt");
	if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

	int runningTotal1 = 0;
	long long runningTotal2 = 0;

	std::string line;
	while (std::getline(file, line))
	{
		int max2 = 0;
		for (size_t i = 0; i < line.size(); i++)
		{
			int val1 = (line.at(i) - '0');
			for (size_t j = i + 1; j < line.size(); j++)
			{
				int val2 = line.at(j) - '0';
				int res = 10 * val1 + val2;
				max2 = res > max2 ? res : max2;
			}
		}
		runningTotal1 += max2;

		long long max12 = 0;
		size_t slack = line.size() - 12;
		size_t lastDigitIndex = 0;
		for (size_t i = 0; i < 12; i++)
		{
			int largestDigit = 0;
			for (size_t j = lastDigitIndex; j < lastDigitIndex + slack + 1; j++)
			{
				int val = line.at(j) - '0';
				if (val > largestDigit)
				{
					slack -= j - lastDigitIndex;
					largestDigit = val;
					lastDigitIndex = j;
				}
			}
			lastDigitIndex += 1;
			max12 += largestDigit * std::pow(10, 11 - i);
		}
		runningTotal2 += max12;
	}

	std::cout << "Running total for task 1: " << runningTotal1 << "\n";
	std::cout << "Running total for task 2: " << runningTotal2 << "\n";


	return 0;
}