#The makefile

COMPILER=g++ 
OPTIONS=-Wall -std=c++11
LIBS=-LOctree/
HEADERS=-IOctree/
MODULES=worldgen.o Octree/octree.o

all: release testworld.out

debug: 
	$(eval OPTIONS+=-g -Og)
profile:
	$(eval OPTIONS+=-g -pg -Ofast)
release: 
	$(eval OPTIONS+=-Ofast -static -s)

clean: 
	rm *.out

%.out: %.o $(MODULES)
	$(COMPILER) $< $(MODULES) -o $@ $(LIBS) $(OPTIONS)

%.o: %.cpp
	$(COMPILER) -c $< $(HEADERS) -o $@ $(OPTIONS)