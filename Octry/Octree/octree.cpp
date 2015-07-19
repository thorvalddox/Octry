#include "octree.h"
#include <iostream>
#include <iterator>

template <class T>
oc_node<T>::oc_node(T t, int offset, int depth):offset(offset),depth(depth)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		sub[i].data = t;
		sub[i].next = 0;
	}
}


template<class T>
octree<T>::octree(int depth, T first):depth(depth)
{
	array.push_back(oc_node<T>(first, 0, 0));
}

template <class T>
octree<T>::~octree()
{
	
}

template <class T>
inline void octree<T>::set(T t, int x, int y, int z)
{
	return setblock(t, x, y, z, 0);
}

template <class T>
inline void octree<T>::addnode(node_pos parent, int offset)
{
	array.push_back(oc_node<T>(array[parent].sub[offset].data,
		offset, array[parent].depth + 1));
	array.back().parent = parent;
	array[parent].sub[offset].next = array.size() - 1;
}

template <class T>
void octree<T>::collapsenode(node_pos n)
{
	while (n>0)
	{
		int i;
		for (i = 0; i < 8; i++)
		{
			if (array[n].sub[i].next) return;
			if (array[n].sub[0].data != array[n].sub[i].data) return;
		}
		n = removenode(n);
	}
}

template <class T>
void octree<T>::copy(node_pos dest, node_pos src)
{
	array[dest] = array[src];
	array[array[src].parent].sub[array[src].offset].next = dest;
	int i;
	for (i = 0; i < 8; i++)
	{
		array[array[src].sub[i].next].parent = dest;
	}
} 

template <class T>
node_pos octree<T>::removenode(node_pos n)
{
	//debug
	/*
	int i;
	for (i = 0; i < 8; i++)
	{
		if (array[n].sub[i].next) 
			std::cerr << "WARNING! YOU'RE ABOUT TO DELETE A NODE WITH CHILDREN!\n" ;
	}
	
	if (array[n].parent == 121114) 
	{
		std::cerr << n << "blabla\n";
	}
	*/
	array[array[n].parent].sub[array[n].offset].data = array[n].sub[0].data;
	array[array[n].parent].sub[array[n].offset].next = 0;
	if (n == array.size() - 1)
	{
		n = array[n].parent;
	}
	else if (array[n].parent == array.size() - 1)
	{	
		//std::cerr << "CASE 2\n";
		copy(n, array.size() - 1);
		//check (0);
	}
	else
	{
		//std::cerr << "CASE 3\n";
		node_pos parent = array[n].parent;
		copy(n, array.size() - 1);
		n = parent;
		//check(0);
	}
	array.pop_back();
	return n;
}

template <class T>
node_pos octree<T>::setblock(T t, node_pos pos)
{
	int i;
	for (i = 0; i < 8; i++)
	{
		int n;
		if (n = array[pos].sub[i].next)
		{
			pos = setblock (t, n);
		}
	}
	int offset = array[pos].offset;
	pos = removenode(pos);
	array[pos].sub[offset].data = t;
	return pos;
}

template <class T>
void octree<T>::setblock(T t, int x, int y, int z, int depth)
{
	int size = 1<<this->depth;
	node_pos pos = 0;
	int offset;
	while (size > 1<<depth)
	{
		offset = 0;
		offset += ((x&size/2)?4:0);
		offset += ((y&size/2)?2:0);
		offset += ((z&size/2)?1:0);
		size /= 2;
		if (!array[pos].sub[offset].next)
			{
				if (array[pos].sub[offset].data == t) return;
				addnode(pos, offset);
			}
		pos = array[pos].sub[offset].next;
	}
	pos = setblock (t, pos);
	collapsenode(pos);
}

template <class T>
T octree<T>::get(int x, int y, int z)
{
	int size = 1<<depth;
	node_pos pos = 0;
	while (1)
	{
		int offset = 0;
		offset += ((x&size/2)?4:0);
		offset += ((y&size/2)?2:0);
		offset += ((z&size/2)?1:0);
		size /= 2;
		if (!array[pos].sub[offset].next)
			return array[pos].sub[offset].data;
		pos = array[pos].sub[offset].next;
	}
}

template <class T>
void octree<T>::print()
{
	int k;
	for (k = 0; k < array.size(); k++)
	{
		std::cout << "Node: " << k << "\n";
		int i;
		for (i = 0; i < 8; i++)
			std::cout << "\t" << (array[k].sub[i].next?"Next: ": "Data: \t \t") 
							  << (array[k].sub[i].next?array[k].sub[i].next: array[k].sub[i].data) 
							  << "\n";
		std::cout << std::endl;
	}
}

template <class T>
int octree<T>::getsize()
{
	return array.size();
}

template <class T>
int octree<T>::check(node_pos n)
{
	for (int i = 0; i < 8; i++)
	{
		if (array[n].sub[i].next == 0) continue;
		if (array[array[n].sub[i].next].parent != n)
		{
			std::cerr << "ERROR! Tree not correct anymore.\n";
			return 1;		
		}
		check (array[n].sub[i].next);
	}
	return 0;
}

template<class T>
std::vector<cube<T> > octree<T>::graphify()
{
	std::vector<cube<T> > res;
	for (oc_node<T> node : array)
	{
		cube<T> next;
		unsigned pos = res.size();
		int i;
		for (i = 0; i < 8; i++)
		{
			if (node.sub[i].next) 
				next.data[i] = 9;
			else
				next.data[i] = node.sub[i].data;
		}
		next.x = 0;
		next.y = 0;
		next.z = 0;
		next.depth = node.depth;
		while (pos)
		{
			if (array[pos].offset&4) next.x += 1<<(depth - array[pos].depth);
			if (array[pos].offset&2) next.y += 1<<(depth - array[pos].depth);
			if (array[pos].offset&1) next.z += 1<<(depth - array[pos].depth);
			pos = array[pos].parent;
		}
		res.push_back(next);
		//std::cout << next.x << ' ' << next.y << ' ' << next.z << ' ' << next.depth << '\n';
	}
	return res;
}

// Implementations

template class octree<int>;
