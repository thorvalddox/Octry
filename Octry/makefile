#The makefile

COMPILER=g++ -Wall -std=c++11
LIBS=-LOctree/
HEADERS=-IOctree/
MODULES=worldgen.o Octree/octree.o
.SUFFIXES:.o

all: testworld.out

%.out : %.o $(MODULES);
	$(COMPILER) $< $(MODULES) -o $@ $(LIBS) $(HEADERS)

%.o : %.cpp %.h;
	$(COMPILER) -c $< $(HEADERS) -o $@
