#include "octree.h"
#include <iostream>

template class octree<int>;

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
	array.push_back(oc_node<T>(first, 0, depth));
}

template <class T>
octree<T>::~octree()
{
	
}

template <class T>
void octree<T>::set(T t, int x, int y, int z)
{
	return setblock(t, x, y, z, 0);
}

template <class T>
void octree<T>::addnode(node_pos parent, int offset)
{
	array.push_back(oc_node<T>(array[parent].sub[offset].data,
		offset, array[parent].depth + 1));
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
			if (array[n].sub[i].next) 
			{
				std::cerr << "Collapsed node had children!" << std::endl;
				throw;
			}
			if (array[n].sub[0].data != array[n].sub[i].data) return;
		}
		n = removenode(n);
	}
}

template <class T>
node_pos octree<T>::removenode(node_pos n)
{
	if (n == array.size() - 1)
	{
		n = array[n].parent;
	}
	else if (array[n].parent == array.size() - 1)
	{	
		array[array[n].parent].sub[array[n].offset].data = array[n].sub[0].data;
		array[array[n].parent].sub[array[n].offset].next = 0;
		array[n] = array[array.size() - 1];
		array[array[n].parent].sub[array[n].offset].next = n;
	}
	else
	{
		array[array[n].parent].sub[array[n].offset].data = array[n].sub[0].data;
		array[array[n].parent].sub[array[n].offset].next = 0;
		node_pos parent = array[n].parent;
		array[n] = array[array.size() - 1];
		array[array[n].parent].sub[array[n].offset].next = n;
		n = parent;
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
			pos = removenode(array[pos].sub[i].next);
		}
	}
	return array[pos].parent;
}

template <class T>
void octree<T>::setblock(T t, int x, int y, int z, int depth)
{
	int size = 1<<this->depth;
	node_pos pos = 0;
	while (size > 1<<depth)
	{
		int offset = 0;
		offset += ((x&size/2)?4:0);
		offset += ((y&size/2)?2:0);
		offset += ((z&size/2)?1:0);
		size /= 2;
		if (!array[pos].sub[offset].next)
			addnode(pos, offset);
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
void octree<T>::print(node_pos n)
{
	
}