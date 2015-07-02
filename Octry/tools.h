#include "xml/pugixml.hpp"
#include <sstream>
#include <vector>
#include <cmath>

using std::stringstream;
using std::vector;



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
};

class Direction
{
public:
    double x;
    double y;
    double z;
    Direction(double,double,double)
    bool operator==(Direction);
    double size();
    Direction normate();
    /// the equi
    Direction equi_dist(Position);
    Direction horiz_dist(Position);
    Direction vert_distance(Position);
};





class Relief
{
public:
    Relief(stringstream *);



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

};


};