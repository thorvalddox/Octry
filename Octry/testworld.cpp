#include "Octree/octree.h"
#include "worldgen.h"

#include <iostream>

int main(int argc, char * argv [])
{
    int layers;
    if (argc < 2)
        layers = 10;
    else
        layers = atoi(argv[1]);
    worldgen::HeightMap heightmap(layers, 1<<(layers-1), 10);
    heightmap.calculate();
    octree<int> tree (layers, 0);
    int x, y, z;
    std::cout << std::endl;
    /*
    tree.setblock(1,0,0,0,layers - 1);
    tree.setblock(1,0,1<<layers-1,0, layers -1);
    tree.setblock(1,1<<layers-1,0,0, layers -1);
    tree.setblock(1,1<<layers-1,1<<layers-1,0, layers -1);
    */
    std::cout << "Flush\n";
    for (x = 0; x < 1<<layers; x++) {
        std::cout << "Progress: " << 100. * (x)/ (1<<layers) << "\n";
        for (y = 0; y < 1<<layers; y++) {
            for (z = 0; z < (1<<layers - 1) + heightmap.landscape.get(worldgen::point {x,y}); z++) {
                tree.set(1, x, y, z);
            }
            /*
            			for (; z < 64; z++)
            			{
            				tree.set(0, x, y, z);
            			}
            */
        }
    }
    std::cout << tree.getsize() * sizeof(oc_node<int>) << " VS " << (1<<layers) * (1<<layers) * (1<<layers) * sizeof(int) << std::endl;
}

