#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>


class UnionFind {
    std::vector<int> parent;
	int components;
public:
    UnionFind(int size)
	{
		components = size;
        parent.resize(size);
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int i)
	{
        if (parent[i] != i)
        	parent[i] = find(parent[i]);
    	return parent[i];
    }

    void unite(int i, int j)
	{
        int iroot = find(i);
        int jroot = find(j);
        if (iroot != jroot) {
        	parent[iroot] = jroot;
        	components--;
   		}
    }

	int getComponentCount()
	{
		return components;
	}

	long long int largestCircutProduct(int N)
	{
		std::unordered_map<int, int> freq;
		for (size_t i = 0; i < parent.size(); ++i)
		{
			int root = find(i);
			freq[root]++;
		}
		std::vector<std::pair<int,int>> temp(freq.begin(), freq.end());
		std::sort(temp.begin(), temp.end(),
		[](const std::pair<int,int>& a, const std::pair<int,int>& b) {
            return a.second > b.second;
        });
		long long int res = 1;
		for (size_t i = 0; i < N; i++)
		{
			res *= temp[i].second;
		}
		return res;
	}
};

struct JunctionBox
{
	int x;
	int y;
	int z;
};

unsigned long long distance(const JunctionBox &box1, const JunctionBox &box2)
{
	long long a = (box1.x - box2.x);
	long long b = (box1.y - box2.y);
	long long c = (box1.z - box2.z);
	return a*a + b*b + c*c;
}

int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	std::vector<JunctionBox> boxes;
	std::vector<std::tuple<unsigned long long,int,int>> edges;
	std::vector<std::vector<size_t>> circuts;

	std::string line;
	while (std::getline(file, line))
	{
		size_t separator1 = line.find_first_of(',');
		size_t separator2 = line.find_last_of(',');
		int x = std::stoi(line.substr(0, separator1));
		int y = std::stoi(line.substr(separator1 + 1, separator2 - separator1));
		int z = std::stoi(line.substr(separator2 + 1));
		boxes.push_back({x, y, z});
	}

	for (size_t i = 0; i < boxes.size(); i++)
	{
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			edges.emplace_back(distance(boxes[i], boxes[j]), i, j);
		}
	}

	std::sort(edges.begin(), edges.end(), [](const auto &a, const auto &b) { 
        return std::get<0>(a) < std::get<0>(b);
	});

	UnionFind uf(boxes.size());
	int connections = 0;
	unsigned long long total1;
	unsigned long long total2;
	for (auto &[distance, i, j] : edges)
	{
		uf.unite(i, j);
		if (++connections == 1000)
		{
			total1 = uf.largestCircutProduct(3);
		}
		if (uf.getComponentCount() == 1)
		{ 
			total2 = (unsigned long long)boxes[i].x * boxes[j].x;
			break;
		}
	}
	
	std::cout << "Product for task 1: " << total1 << "\n";
	std::cout << "Product for task 2: " << total2 << "\n";

	return 0;
}