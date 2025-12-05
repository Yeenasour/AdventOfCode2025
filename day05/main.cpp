#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Range
{
	unsigned long long start;
	unsigned long long end;
};

Range strToRange(std::string &range)
{
	size_t delimiter = range.find('-');
	unsigned long long start = std::stoull(range.substr(0, delimiter));
	unsigned long long end = std::stoull(range.substr(delimiter + 1));
	return {start, end};
}

bool inline inRange(unsigned long long i, Range &range)
{
	return range.start <= i && i <= range.end;
}

int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	unsigned int count1 = 0;
	unsigned long long count2 = 0;

	std::vector<Range> ranges;
	std::vector<Range> merged;
	std::vector<unsigned long long> IDs;

	std::string line;
	while (std::getline(file, line) && line != "")
		ranges.push_back(strToRange(line));
	while (std::getline(file, line))
		IDs.push_back(std::stoull(line));

	// because an unordered map would be boring to remove duplicates
	std::sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) { return a.start < b.start; });
	if (!ranges.empty())
	{
		Range current = ranges.at(0);
		for (size_t i = 1; i < ranges.size(); i++)
		{
			const Range& next = ranges.at(i);

			if (next.start <= current.end)
			{
				current.end = std::max(current.end, next.end);
			}
			else
			{
				merged.push_back(current);
				current = next;
			}
		}
		merged.push_back(current);
	}
	
	for (Range &range : merged)
	{
		for (unsigned long long id : IDs)
		{
			if (inRange(id, range)) count1++;
		}
		count2 += range.end - range.start + 1;
	}
	
	std::cout << "Count for task 1: " << count1 << "\nCount for task 2: " << count2 << "\n";

	return 0;
}