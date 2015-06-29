#include "WorldGen.h"

namespace worldgen
{
	double gauss()
	{
		return(1.0 / RAND_MAX*(rand() - rand()));
	}

	LandScape::LandScape(int layers) :
		size((1<<layers) + 1),
		heights(size, std::vector<double>(size, 0.0))
	{
		//
	}

	double LandScape::get(const point & position) const
	{
		//cout << "get " << position.x << "," << position.y << ":" << heights[position.x][position.y] << "\n";
		return(heights[position.x][position.y]);
	}

	void LandScape::set(const point & position, double value)
	{
		heights[position.x][position.y] = value;

	}

	void LandScape::print(std::ostream * out)
	{
		for (vector<double> row : heights)
		{
			for (double value : row)
			{
				*out << value << "\t";
			}
			*out << std::endl;
		}
	}

	Square::Square(const point & topleft, int layers, bool tilted)
	{
		size = 1<<layers;
		int halfsize = size / 2;
		corners.resize(4);
		if (!tilted)
		{
			corners[0] = point{ topleft.x, topleft.y }; //Same as corners = topleft but written this way for consitancy
			corners[1] = point{ topleft.x + size, topleft.y };
			corners[2] = point{ topleft.x + size, topleft.y + size };
			corners[3] = point{ topleft.x, topleft.y + size };
		}
		else
		{
			corners[0] = point{ topleft.x + size / 2, topleft.y };
			corners[1] = point{ topleft.x + size, topleft.y + size / 2 };
			corners[2] = point{ topleft.x + size / 2, topleft.y + size };
			corners[3] = point{ topleft.x, topleft.y + size / 2 };
		}
		midpoint = point{ topleft.x + size / 2, topleft.y + size / 2 };
	}

	void Square::apply(LandScape & landscape,double noise)
	{
		vector<double> heights;
		for (point i : this->corners)
		{
			heights.push_back(landscape.get(i));
		}
		double newheight = std::accumulate(heights.begin(), heights.end(), 0.0) - 
			*std::min_element(heights.begin(), heights.end());
		landscape.set(midpoint, newheight/3 + noise * size * gauss());

	}

	HeightMap::HeightMap(int layers, double height, double noise) :
		landscape(layers),
		layers(layers),
		height(height), 
		noise(noise*height/landscape.size)
	{
		//
	}

	void HeightMap::calculate_step(int layer)
	{
		cout << "building layer " << layer << std::endl;
		int stepsize = 1 << layer;
		for (int x = 0; x < landscape.size-1; x += stepsize)
		{
			for (int y = 0; y < landscape.size-1; y += stepsize)
			{
				
				Square select_square(point{ x, y }, layer);
				select_square.apply(landscape, noise);
			}
		}

		for (int x = 0; x < landscape.size-1; x += stepsize)
		{
			for (int y = 0; y < landscape.size-1 - stepsize; y += stepsize)
			{
				Square select_square1(point{ x, y + stepsize/2 }, layer, true);
				select_square1.apply(landscape, noise);
				Square select_square2(point{ y + stepsize / 2, x }, layer, true);
				select_square2.apply(landscape, noise);

			}
		}
	}

	void HeightMap::calculate()
	{
		landscape.set(point{ landscape.size / 2, landscape.size / 2 }, height);
		for (int l = layers-1; l > 0; l--)
		{
			calculate_step(l);
		}
	}
	
}