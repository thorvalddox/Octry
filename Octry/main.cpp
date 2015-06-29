#include <iostream>
#include <fstream>
#include "WorldGen.h"

using std::cout;
using std::cin;

int main()
{
	cout << "Testing worldgen\n";
	std::ofstream outfile("worldgen.txt");
	worldgen::HeightMap heightmap(10, 40, 10);
	heightmap.calculate();
	heightmap.landscape.print(&outfile);
	cout << "Done";
	return 0;
}