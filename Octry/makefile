#The makefile

COMPILER=g++ 
OPTIONS=-Wall -std=c++11
LIBS=-LOctree/
HEADERS=-IOctree/
MODULES=worldgen.o Octree/octree.o

all: release testworld.out testworldgen.out

debug: 
	$(eval OPTIONS+=-g -Og)
profile:
	$(eval OPTIONS+=-g -pg -Ofast)
release: 
	$(eval OPTIONS+=-Ofast -static -s)

clean: 
	rm *.out

doxygen:
	doxygen config
	ln -s html/index.html doc/index.html

%.out: %.o $(MODULES)
	$(COMPILER) $< $(MODULES) -o build/$@ $(LIBS) $(OPTIONS)

%.o: %.cpp
	$(COMPILER) -c $< $(HEADERS) -o $@ $(OPTIONS)
