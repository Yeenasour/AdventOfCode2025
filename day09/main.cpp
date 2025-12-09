#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>


struct Point
{
	int x;
	int y;

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	static unsigned long long rectangleArea(Point p1, Point p2)
	{
		unsigned long long width = abs(p1.x - p2.x) + 1;
		unsigned long long height = abs(p1.y - p2.y) + 1;
		return width * height;
	}
};

unsigned long long pack(int a, int b)
{
	return ((unsigned long long) a) << 32 ^ b;
}

std::unordered_set<unsigned long long> tracePerimeter(std::vector<Point> &points)
{
	std::unordered_set<unsigned long long> side1;
	std::unordered_set<unsigned long long> side2;

	std::unordered_set<unsigned long long> border;
	for (size_t i = 0; i < points.size(); i++)
	{
		Point &start = points[i];
		Point &end = points[(i+1)%points.size()];
		bool positiveDirection;
		if (start.x == end.x)
		{
			int ymin = std::min(start.y, end.y);
			int ymax = std::max(start.y, end.y);
			for (int y = ymin; y <= ymax; y++)
			{
				border.insert(pack(start.x, y));
			}
		}
		else
		{
			int xmin = std::min(start.x, end.x);
			int xmax = std::max(start.x, end.x);
			for (int x = xmin; x <= xmax; x++)
			{
				border.insert(pack(x, start.y));
			}
		}
	}

	for (size_t i = 0; i < points.size(); i++)
	{
		Point &start = points[i];
		Point &end = points[(i+1)%points.size()];
		bool positiveDirection;
		if (start.x == end.x)
		{
			positiveDirection = (end.y > start.y);
			int ymin = std::min(start.y, end.y);
			int ymax = std::max(start.y, end.y);
			for (int y = ymin; y <= ymax; y++)
			{
				unsigned long long res1 = positiveDirection ? pack(start.x+1, y) : pack(start.x-1, y);
				unsigned long long res2 = positiveDirection ? pack(start.x-1, y) : pack(start.x+1, y);
				if (border.find(res1) == border.end()) side1.insert(res1);
				if (border.find(res2) == border.end()) side2.insert(res2);
			}
		}
		else
		{
			positiveDirection = end.x > start.x;
			int xmin = std::min(start.x, end.x);
			int xmax = std::max(start.x, end.x);
			for (int x = xmin; x <= xmax; x++)
			{
				unsigned long long res1 = positiveDirection ? pack(x, start.y-1) : pack(x, start.y+1);
				unsigned long long res2 = positiveDirection ? pack(x, start.y+1) : pack(x, start.y-1);
				if (border.find(res1) == border.end()) side1.insert(res1);
				if (border.find(res2) == border.end()) side2.insert(res2);
			}
		}
	}

	return (side1.size() > side2.size()) ? side1 : side2;
}

bool rectangleIntersection(Point p1, Point p2, std::unordered_set<unsigned long long> &iset)
{
	int xmin = std::min(p1.x, p2.x);
	int xmax = std::max(p1.x, p2.x);
	int ymin = std::min(p1.y, p2.y);
	int ymax = std::max(p1.y, p2.y);
	for (int x = xmin; x < xmax; x++)
		if (iset.find(pack(x, ymin)) != iset.end())
			return true;
	for (int y = ymin; y < ymax; y++)
		if (iset.find(pack(xmax, y)) != iset.end())
			return true;
	for (int x = xmax; x > xmin; x--)
		if (iset.find(pack(x, ymax)) != iset.end())
			return true;
	for (int y = ymax; y > ymin; y--)
		if (iset.find(pack(xmin, y)) != iset.end())
			return true;
	return false;
}

int main()
{
	std::ifstream file("input.txt");
	if (!file)
	{
		std::cerr << "Failed to open file\n";
		return 1;
	}

	unsigned long long largestArea = 0;
	unsigned long long largestNonCollidingArea = 0;
	std::vector<Point> points;

	std::string line;
	while (std::getline(file, line))
	{
		size_t separatorIndex = line.find(',');
		int x = std::stoi(line.substr(0, separatorIndex));
		int y = std::stoi(line.substr(separatorIndex + 1));
		points.emplace_back(x, y);
	}

	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = i + 1; j < points.size(); j++)
		{
			unsigned long long area = Point::rectangleArea(points[i], points[j]);
			if (area > largestArea) largestArea = area;
		}
	}

	std::unordered_set<unsigned long long> perimeter (tracePerimeter(points));

	for (size_t i = 0; i < points.size(); i++)
	{
		for (size_t j = i + 1; j < points.size(); j++)
		{
			unsigned long long area = Point::rectangleArea(points[i], points[j]);
			if (area <= largestNonCollidingArea) continue;
			if (rectangleIntersection(points[i], points[j], perimeter)) continue;
			largestNonCollidingArea = area;
		}
	}
	
	std::cout << "Largest area in task 1: " << largestArea << "\n";
	std::cout << "Largest area in task 2: " << largestNonCollidingArea << "\n";

	return 0;
}