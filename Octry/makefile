#The makefile

COMPILER=g++ 
OPTIONS=-Wall -std=c++11
LIBS=-LOctree/
HEADERS=-IOctree/
MODULES=worldgen.o Octree/octree.o

<<<<<<< HEAD
all: testworld.out testworldgen.out
=======
all: release testworld.out
>>>>>>> d764507c81ce3df72060e6e958798a3944fc828f

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
