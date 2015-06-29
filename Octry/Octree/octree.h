#pragma once
#include <vector>

typedef unsigned node_pos;

template <class T>
class octree;

template <class T>
class oc_node {
	friend octree<T>;
private:
	node_pos parent;
	int offset, depth;
	struct {
		T data;
		node_pos next;
	} sub [8];
public:
	oc_node(T t, int offset, int depth);
};

template <class T>
class octree {
private:
	int depth;
	int size;
	std::vector<oc_node<T> > array;
	
	node_pos setblock(T t, node_pos pos);
	
	void addnode(node_pos parent, int offset);
	node_pos removenode(node_pos n);
	void collapsenode(node_pos node);
	
public:
	int getsize();
	void setblock(T t, int x, int y, int z, int depth);
	
	octree(int depth, T first);
	~octree();
	void set(T t, int x, int y, int z);
	T get(int x, int y, int z);
	void print();
};