#The makefile

COMPILER=g++ 
OPTIONS=-Wall -std=c++11
LIBS=-LOctree/
HEADERS=-IOctree/
MODULES=worldgen.o Octree/octree.o tools.o xml/pugixml.o graphics/shaderutil.o

all: release testworld.out testworldgen.out

debug: 
	$(eval OPTIONS+=-g -Og)
profile:
	$(eval OPTIONS+=-g -pg -Ofast)
release: 
	$(eval OPTIONS+=-Ofast -s)

opengl: LIBS+= -lGL -lX11
opengl: testgraph.o graphics/gr_linux.o $(MODULES)
	$(COMPILER) testgraph.o graphics/gr_linux.o $(MODULES) -o build/testgraph.out $(LIBS) $(OPTIONS) -std=c++11;



clean: 
	rm *.out

doxygen:
	doxygen config
	ln -s html/index.html doc/index.html

%.out: %.o $(MODULES)
	$(COMPILER) $< $(MODULES) -o build/$@ $(LIBS) $(OPTIONS)

%.o: %.cpp *.h
	$(COMPILER) -c $< $(HEADERS) -o $@ $(OPTIONS)
