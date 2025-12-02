#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& str, const char delimiter)
{
	std::vector<std::string> ranges;
	std::stringstream stream(str);
	std::string s;

	while (std::getline(stream, s, delimiter))
	{
		ranges.push_back(s);
	}
	
	return ranges;
}

int main()
{
	std::ifstream file("input.txt");
	if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

	uint64_t runningTotal1 = 0;
	uint64_t runningTotal2 = 0;

	std::string line;
	if (!std::getline(file, line)) return -1;

	std::vector<std::string> ranges = split(line, ',');

	for (std::string &range : ranges)
	{
		size_t delimiter = range.find('-');
		uint64_t start = std::stoull(range.substr(0, delimiter));
		uint64_t end = std::stoull(range.substr(delimiter + 1));

		for (uint64_t val = start; val <= end; val++)
		{
			std::string id = std::to_string(val);
			if (id.size() % 2 == 1) continue;
			std::string left = id.substr(0, id.size() / 2);
			std::string right = id.substr(id.size() / 2);
			if (!left.compare(right)) runningTotal1 += std::stoull(id);
		}

		for (uint64_t val = start; val <= end; val++)
		{
			std::string id = std::to_string(val);
			for (size_t chuckSize = id.size() / 2; chuckSize > 0; chuckSize--)
			{
				if (id.size() % chuckSize != 0) continue;
				bool matching = true;
				for (size_t j = 0; j + 2 * chuckSize <= id.size(); j += chuckSize)
				{
					std::string a = id.substr(j, chuckSize);
					std::string b = id.substr(j + chuckSize, chuckSize);
					if (a.compare(b))
					{
						matching = false;
						break;
					}
				}
				if (matching)
				{
					runningTotal2 += std::stoull(id);
					break;
				}
			}
		}
	}
	
	std::cout << "Part 1 running total: " << runningTotal1 << std::endl;
	std::cout << "Part 2 running total: " << runningTotal2 << std::endl;

	return 0;
}