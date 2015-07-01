#The makefile

COMPILER=g++ 
OPTIONS = -Wall -std=c++11
LIBS=-LOctree/
HEADERS=-IOctree/
MODULES=worldgen.o Octree/octree.o

all: testworld.out

testworld: testworld.out

testtree: Octree/testree.out

%.out : %.o $(MODULES)
	$(COMPILER) $< $(MODULES) -o $@ $(LIBS) $(OPTIONS)

%.o : %.cpp *.h
	$(COMPILER) -c $< $(HEADERS) -o $@ $(OPTIONS)
