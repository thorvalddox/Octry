#include "worldgen.h"

namespace worldgen
{
    double gauss()
    {
        return(1.0 / RAND_MAX*(rand() - rand()));
    }

    LandScape::LandScape(int layers, bool raise) :
        size((1<<layers) + 1),
        heights(size, std::vector<double>(size, raise?(double)(size/2):0))
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

    void LandScape::add(const point & position, double value)
    {
        heights[position.x][position.y] += value;

    }

    void LandScape::print(std::ostream * out)
    {
        for (vector<double> row : heights) {
            for (double value : row) {
                *out << value << "\t";
            }
            *out << std::endl;
        }
    }

    LandScape * LandScape::compress(int layer)
    {
        int blocksize = 1<<layer;
        LandScape * newls = new LandScape(*this); //make pointer to copy of this
        for (int x=0; x<size; x++) {
            int floorx = (x/blocksize)*blocksize; //rounds x down to multiple of blocksize
            for (int y=0; y<size; y++) {
                int floory = (y/blocksize)*blocksize; //rounds y down to multiple of blocksize)
                int floorval = ((int)get({floorx,floory})/blocksize)*blocksize; /// rounds z down to multiple of blocksize
                newls->set({x,y},floorval);
            }
        }
        //cout << "exiting compression ...\n";
        return(newls);
    }

    Square::Square(const point & topleft, int layers, bool tilted)
    {
        size = 1<<layers;
        corners.resize(4);
        if (!tilted) {
            corners[0] = point { topleft.x, topleft.y }; //Same as corners = topleft but written this way for consitancy
            corners[1] = point { topleft.x + size, topleft.y };
            corners[2] = point { topleft.x + size, topleft.y + size };
            corners[3] = point { topleft.x, topleft.y + size };
        } else {
            corners[0] = point { topleft.x + size / 2, topleft.y };
            corners[1] = point { topleft.x + size, topleft.y + size / 2 };
            corners[2] = point { topleft.x + size / 2, topleft.y + size };
            corners[3] = point { topleft.x, topleft.y + size / 2 };
        }
        midpoint = point { topleft.x + size / 2, topleft.y + size / 2 };
    }

    void Square::apply(LandScape & landscape,double noise)
    {
        double sum = 0.0;
        double min = landscape.get(this->corners[0]);
        for (point i : this->corners) {
            double corner = landscape.get(i);
            if (min > corner) min = corner;
            sum += corner;   
        }
        double newheight = sum - min;
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
        cout << "generation layer " << layer << std::endl;
        int stepsize = 1 << layer;
        for (int x = 0; x < landscape.size-1; x += stepsize) {
            for (int y = 0; y < landscape.size-1; y += stepsize) {

                Square select_square(point { x, y }, layer);
                select_square.apply(landscape, noise);
            }
        }

        for (int x = 0; x < landscape.size-1; x += stepsize) {
            for (int y = 0; y < landscape.size-1 - stepsize; y += stepsize) {
                Square select_square1(point { x, y + stepsize/2 }, layer, true);
                select_square1.apply(landscape, noise);
                Square select_square2(point { y + stepsize / 2, x }, layer, true);
                select_square2.apply(landscape, noise);

            }
        }
    }

    void HeightMap::calculate()
    {
        landscape.add(point { landscape.size / 2, landscape.size / 2 }, height);
        for (int l = layers-1; l > 0; l--) {
            calculate_step(l);
        }
    }

    octree<int> * HeightMap::build_octree()
    {
        calculate();
        LandScape * prev = new LandScape(layers,false);
        octree<int> * wmap = new octree<int>(layers,0);
        cout << "building layer " << layers << "\n";
        for (int layer = layers-1; layer >= 0; layer--) {
            int size = (1<<layer);
            cout << "building layer " << layer << std::endl;
            LandScape * next = landscape.compress(layer);
            //std::stringstream filename;
            //filename << "compress" << layer << ".txt";
            //std::ofstream outfile(filename.str());
            //next->print(&outfile);
            //build octree
            for (int x = 0; x<next->size; x+=size) { //loop over x, but select blocks
                for (int y = 0; y<next->size; y+=size) { // select block
                    point pos {x,y};
                    int newheight = next->get(pos);
                    int oldheight = prev->get(pos);
                    if (oldheight < newheight) {
                        for (int z=oldheight; z<newheight; z+=size) {
                            wmap->setblock(1,x,y,z,layer);
                        }
                    } else {
                        for (int z=newheight; z<oldheight; z+=size) {
                            wmap->setblock(0,x,y,z,layer);
                        }

                    }

                }
            }
            delete prev; // DON'T FORGET TO DELETE YOUR MEMORY plz.
            prev = next;
        }
        delete prev;
        return(wmap);
    }


    octree<int> * HeightMap::build_slow()
    {
        calculate();
        octree<int>* tree = new octree<int>(layers, 0);
        int x, y, z;
        std::cout << std::endl;
        /*
        tree.setblock(1,0,0,0,layers - 1);
        tree.setblock(1,0,1<<layers-1,0, layers -1);
        tree.setblock(1,1<<layers-1,0,0, layers -1);
        tree.setblock(1,1<<layers-1,1<<layers-1,0, layers -1);
        */
        std::cout << "Flush\n";
        for (x = 0; x < 1<<layers; x++) {
            std::cout << "Progress: " << 100. * (x)/ (1<<layers) << "\n";
            for (y = 0; y < 1<<layers; y++) {
                for (z = 0; z < (1<<layers - 1) + this->landscape.get(worldgen::point {x,y}); z++) {
                    tree->set(1, x, y, z);
                }
                /*
                            for (; z < 64; z++)
                            {
                                tree.set(0, x, y, z);
                            }
                */
            }
        }
        return tree;

    }

}