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
#include "Octree/octree.h"


namespace worldgen
{
	using std::vector;
	using std::map;
	using std::pair;
	using std::deque;
	using std::cout;

	double gauss();

	///Represents a x,y position on the landscape. Used for indexing
	struct point {
		int x;
		int y;
	};

	///Represents a 2d-array of height points
	class LandScape {
	public:
		/// contructor. 
		/// @param[layers] The amount of layers
		LandScape(int layers);
		/// getter method
		double get(const point & position) const;
		/// setter method
		void set(const point & position, double);
		/// will export the Landscape to a given ofstream. If ofstream is a file, it can be read by buildmap.gp
		void print(std::ostream * );
		/// gives a compressed version of the Landscape. Used for building octrees.
		LandScape & compress(int layer);

	public:
		int size;
	private:
		vector < vector<double> > heights;
	};

	/// represents a square on the map. It could be aligned with the map or it could be tilted 45° 
	class Square {
	public:
		/** contructor. If tilted is false, it will create a square aligned with the grid.
		 * @param lefttop is the left top point
		 * @param size size is the lenght of the sides.
		 * @param tilted if tilted is true, the square will have as corners the midpoints of the different
		 * sides the square would have if it wasn't tilted.
		 */
		Square(const point & lefttop, int size,bool tilted=false);
		/** changes the value of the midpoint of the square on the given landscape.
		 * It will use a random-midpoint displacement algoritm.
		 * @param noise guassian variance of midpoint.
		 */
		void apply(LandScape &, double noise);

	private:
		vector<point> corners;
		point midpoint;
		int size;
	};

	/// A class to generate a worldmap. The worldmap itself is saved as a Landscape object in the member .landscape
	class HeightMap {
	public:
		/** Contructor
		 * @param layers layers of the LandScape
		 * @param height initial height. The random-displacement-algoritm will start from a pyramid form and add noise to it
		 * the pyramid froms initial height is given here.
		 * @param noise roughness of the terrain. Note that this scales with the height. 
		 */
		HeightMap(int layers, double height, double noise);
		/// calculates the height of the landscape. After doing this, the results are stored in the landscape member.
		void calculate();
		octree<int> build_octree();


	private:
		void calculate_step(int square_size);

	public:
		/// the landscape.
		LandScape landscape;

	private:
		int layers;
		double height;
		double noise;
	};




};