#include "xml/pugixml.hpp"
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>


using std::stringstream;
using std::vector;
using std::ostream;
using std::string;

namespace tools
{

class Position
{
public:
    double x;
    double y;
    double z;
    /// free position
    Position(double,double,double);
    /// block midpoint.
    Position(int,int,int);
    Position operator+(Position);
    Position operator-(Position);
    ostream * print(ostream *);
};

class Direction
{
public:
    double x;
    double y;
    double z;
    Direction(double,double,double);
    bool operator==(Direction);
    double size();
    Direction normalise();
    /// the equi
    double equi_dist(Position);
    double horiz_dist(Position);
    double vert_dist(Position);
};





class Relief
{
public:
    Relief(stringstream *);

    bool check_inside(Position pos,Position origin, Direction dir, double size);

private:
    /**lineair extrapolation
     * near is the midpoint between far and new in 3d.
     */
    void extrapolate(int x_far, int y_far, int x_near, int y_near, int x, int y);
    /**square extrapolation
     * the for points form a square which is flat in 3d.
     */
    void extrapolate(int x_far, int y_far, int x_near, int y_near, int x_near2, int y_near2, int x, int y);
    /// bilineair interpolation
    void interpolate(int left, int right, int top, int bottom);

private:
    vector<vector<double>> data;

};

class Tool
{
public:
	Tool(string name,Relief *,double);
private:
	string name;
	Relief * relief;
	double size;
};

typedef vector<Tool> toolbook;
toolbook loadtools();
	
};