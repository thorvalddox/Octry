#include "octree.h"
#include <iostream>
template <class T>
void print(octree<T> tree, int size)
{
	int x, y, z;
	for (z = 0; z < size; z++)
	{
		for (y = 0; y < size; y++)
		{
			for (x = 0; x < size; x++)
				std::cout << tree.get(x,y,z) << ' ';
			std::cout << "\n";
		}
		std::cout << std::endl;
	}
	std::cout << "Tree size: " << tree.getsize() * sizeof (oc_node<T>) << " / Array size: " << size * size * size * sizeof(T) << std::endl;
}

int main()
{
	octree<int> tree (2, 1);
	tree.print();
	print(tree, 4);
	tree.set (3, 0,0,0);
	tree.setblock (4,2,0,0,1);
	tree.set (5, 3,1,1);
	tree.print();
	print(tree, 4);
	tree.set(1, 0, 0, 0);
	tree.print();
	tree.setblock (1, 3, 0, 0, 1);
	tree.print();
	print(tree, 4);
}