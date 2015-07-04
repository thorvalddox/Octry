#include "tools.h"


namespace tools

{

	Position::Position(double x, double y, double z) : 
		x(x),
		y(y),
		z(z)
	{
		//
	}

	Position::Position(int x, int y, int z) : 
		x(x+0.5),
		y(y+0.5),
		z(z+0.5)
	{
		//
	}

	Position Position::operator+(Position other)
	{
		return Position(x+other.x,y+other.y,z+other.z);
	}


	Position Position::operator-(Position other)
	{
		return Position(x-other.x,y-other.y,z-other.z);
	}

	ostream * Position::print(ostream * out)
	{
		*out << x << "\t" << y << "\t" << z << "\n";
		return(out);
	}

	Direction::Direction(double x, double y, double z) : 
		x(x),
		y(y),
		z(z)
	{
		//
	}

	bool Direction::operator==(Direction other) 
	{
		return(normalise()==other.normalise());
	}

	double Direction::size()
	{
		return(sqrt(x*x+y*y+z*z));
	}

	Direction Direction::normalise()
	{
		return(Direction(x/size(),y/size(),z/size()));
	}

	double Direction::equi_dist(Position p)
	{
		return((x*p.x + y*p.y+z*p.z)/size()); //inproduct = a*b*cos : b*cos is distance
	}

	double Direction::horiz_dist(Position p)
	{
		Direction horiz_dir(-y,x,0);
		return( horiz_dir.equi_dist(p));
	}

	double Direction::vert_dist(Position p)
	{
		Direction vert_dir(-x*z,-y*z,x*x+y*y);
		return( vert_dir.equi_dist(p));
	}



	Relief::Relief(stringstream * sstream) :
	    data(25, std::vector<double>(25, 0.0))
	{
	    for (int x = 0; x < 5; x++) {
	        for (int y = 0; y < 5; y++) {
	            float value;
	            *sstream >> value;
	            data[4 * x + 4][4 * y + 4] = value;
	        }
	    }
	    for (int d = 0; d < 5; d++) { //d is distance on border, from topleft. Each border restarts counting
	        extrapolate(d, 8, d, 4, d, 0);
	        extrapolate(8, d, 4, d, 0, d);
	        extrapolate(d, 16, d, 20, d, 24);
	        extrapolate(16, d, 20, d, 24, d);
	    }
	    extrapolate(8, 8, 4, 4, 0, 0);
	    extrapolate(8, 16, 4, 20, 0, 24);
	    extrapolate(16, 8, 20, 4, 24, 0);
	    extrapolate(16, 16, 20, 20, 24, 24);
	    for (int x = 0; x < 7; x++) {
	        for (int y = 0; y < 7; y++) {
	            interpolate(x, x + 4, y, y + 4);
	        }
	    }

	}



	void Relief::extrapolate(int x1, int y1, int x2, int y2, int x3, int y3)
	{
	    data[x3][y3] = 2 * data[x2][y2] - data[x1][y1];
	}

	void Relief::extrapolate(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
	{
	    data[x4][y4] = data[x2][y2] + data[x3][y3] - data[x1][y1];
	}

	void Relief::interpolate(int left, int right, int top, int bottom)
	{
	    double start = data[left][top];
	    double xinc = (data[right][top] - start) / (right - left);
	    double yinc = (data[left][bottom] - start) / (bottom - top);
	    double dinc = (start + data[right][bottom] - data[right][top] - data[left][bottom])
	                  / ((right - left)*(bottom - top));
	    for (int x = left; x <= right; x++) {
	        for (int y = top; y <= bottom; y++) {
	            int rx = x - left;
	            int ry = y - top;
	            data[x][y] = start + rx*xinc + ry*yinc + rx*ry*dinc;
	        }
	    }


	}

	bool Relief::check_inside(Position pos,Position origin, Direction dir, double size)
	{
		Position relpos = pos-origin;
		double step = size/25;
		double zunit = size/4;
		double xpos = dir.horiz_dist(relpos)/step; //dir.get_horiz gives the realtive position, /step scales it to the relief
		double ypos = dir.vert_dist(relpos)/step;
		double zsize = dir.equi_dist(relpos)/zunit; 
		int xindex = (int)xpos;
		int yindex = (int)ypos;
		if (xindex < 0 || xindex >= 25 || yindex < 0 || yindex >= 25)
		{
			return(false);
		}
		return(zsize < data[xindex][yindex]);
	} 

Tool::Tool(string name,Relief * relief,double size) :
	name(name),
	relief(relief),
	size(size)
	{
		//
	}



	toolbook loadtools()
	{
		toolbook alltools;
		pugi::xml_document doc;
		doc.load_file("tools.xml");
		for (pugi::xml_node tool :  doc.children("tool"))
		{	
			string name = tool.attribute("name").value();
			Relief *relief = new Relief(new stringstream(tool.child("relief").text().get()));
			for (pugi::xml_node mat :  doc.children("mat"))
			{
				double size = std::stod(mat.attribute("size").value());
				string name = name + " " + mat.attribute("name").value();
				alltools.emplace_back(name,relief,size);
			}
		}

	return alltools;
	}

}