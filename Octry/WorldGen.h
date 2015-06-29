#pragma once

#include <vector>
#include <map>
#include <deque>
#include <utility>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <ostream>
#include <iomanip>


namespace worldgen
{
	using std::vector;
	using std::map;
	using std::pair;
	using std::deque;
	using std::cout;

	double gauss();

	struct point {
		int x;
		int y;
	};

	class LandScape {
	public:
		LandScape(int layers);
		double get(const point & position) const;
		void set(const point & position, double);
		void print(std::ostream * );

	public:
		int size;
	private:
		vector < vector<double> > heights;
	};

	class Square {
	public:
		Square(const point & lefttop, int size,bool tilted=false);
		void apply(LandScape &, double noise);

	public:
		vector<point> corners;
		point midpoint;
		int size;
	};

	class HeightMap {
	public:
		HeightMap(int layers, double height, double noise);
		void calculate();

	private:
		void calculate_step(int square_size);

	public:
		LandScape landscape;

	private:
		int layers;
		double height;
		double noise;
	};

};