#include <iostream>
#include <fstream>
#include "worldgen.h"
#include <ctime>

using std::cout;
using std::cin;

int main()
{
	srand(time(NULL));
	cout << "Testing worldgen\n";
	std::ofstream outfile("worldgen.txt");
	worldgen::HeightMap heightmap(10, 40, 10);
	heightmap.calculate();
	heightmap.landscape.print(&outfile);
	octree<int>* worldmap = heightmap.build_octree();
	cout << "Done\n";
	return 0;
}