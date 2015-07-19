#include <iostream>
#include <fstream>
#include "worldgen.h"
#include <ctime>
#include <mcheck.h>
using std::cout;
using std::cin;

int main()
{
	mtrace();
    srand(time(NULL));
    cout << "Testing worldgen\n";
    std::ofstream outfile("worldgen.txt");
    worldgen::HeightMap heightmap(10, 40, 10);
    heightmap.calculate();
    heightmap.landscape.print(&outfile);
    octree<int>* worldmap = heightmap.build_octree();
    cout << "Done\n";
    cout << "Size: " << (worldmap->getsize() * sizeof(oc_node<int>)) << "\n";
    delete worldmap;
    return 0;
}