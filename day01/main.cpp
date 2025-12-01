#include <iostream>
#include <fstream>

int main()
{
	std::ifstream file("input.txt");
	if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

	int dial = 50;
	int count_1 = 0;
	int count_2 = 0;

	std::string line;
	while (std::getline(file, line))
	{
		char dir = line.at(0);
		int mag = std::stoi(line.substr(1));

		int fullRotations = mag / 100;
		int nDial = (dir == 'R') ? (dial + mag) : (dial - mag);
		int delta = (dir == 'R') ? (100 - dial) : dial;
		int partialRotation = delta <= (mag % 100) && dial;

		dial = ((nDial) % 100 + 100) % 100;
		int passes = fullRotations + partialRotation;
		if (dial == 0) count_1++;
		count_2 += passes;
	}
	
	std::cout << "Code for part 1: " << count_1 << "\nCode for part 2: " << count_2 << std::endl;

	return 0;
}