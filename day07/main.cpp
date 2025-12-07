#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>


int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	unsigned int splits = 0;
	unsigned long long totalTimelines = 0;

	std::string previousLine;
	std::getline(file, previousLine);
	std::vector<unsigned long long> timelines(previousLine.size(), 0);
	for (size_t i = 0; i < previousLine.size(); i++)
	{
		if (previousLine[i] == 'S')
		{
			timelines[i] = 1;
			break;
		}
	}

	std::string line;
	while (std::getline(file, line))
	{
		for (size_t i = 0; i < line.size(); i++)
		{
			char c = line[i];
			char prev = previousLine[i];
			switch (c)
			{
			case '.':
			{
				if (prev == '|' || prev == 'S') line[i] = '|';
				if (prev == '^') line[i] = '.';
				break;
			}
			case '^':
			{
				if (prev == '|')
				{
					line[i-1] = '|';
					line[i+1] = '|';
					timelines[i-1] += timelines[i];
					timelines[i+1] += timelines[i];
					timelines[i] = 0;
					splits++;
				}
				break;
			}
			}
		}
		previousLine = line;
	}

	totalTimelines = std::accumulate(timelines.begin(), timelines.end(), 0ULL);
	
	std::cout << "Number of splits: " << splits << "\n";
	std::cout << "Number of timelines: " << totalTimelines << "\n";

	return 0;
}