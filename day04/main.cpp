#include <iostream>
#include <fstream>
#include <cmath>

int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	std::string grid;
	grid.reserve(100);

	std::string line;
	while (std::getline(file, line)) grid.append(line);

	ssize_t length = std::sqrt(grid.size());

	int count1 = 0;
	int count2 = 0;

	bool removals = false;
	bool canRemove;

	do
	{
		canRemove = false;
		for (ssize_t i = 0; i < length; i++)
		{
			for (ssize_t j = 0; j < length; j++)
			{
				ssize_t cell = i * length + j;
				if (grid.at(cell) != '@') continue;
				int rolls = 0;
				for (ssize_t k = 0; k < 3; k++)
				{
					for (ssize_t l = 0; l < 3; l++)
					{
						ssize_t cx = i + k - 1;
						ssize_t cy = j + l - 1;
						if (cx < 0 || cx >= length) continue;
						if (cy < 0 || cy >= length) continue;
						if (k == 1 && l == 1) continue;
						if (grid.at(cx * length + cy) == '@') rolls++;
					}
				}
				if (rolls < 4)
				{
					if (removals)
					{
						count2++;
						grid.at(cell) = '.';
					}
					else
					{
						count1++;
					}
					canRemove = true;
				}
			}
		}
		removals = true;
	} while (canRemove);

	std::cout << "Count for task 1: " << count1 << "\nCount for task 2: " << count2 << "\n";

	return 0;
}