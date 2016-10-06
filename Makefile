CXX        = g++
CXXFLAGS   = -O3


BUILD	    = build
SOURCES_CPP = small.cpp
HELPERS     = nsort.h
OBJECTS     = build/small.o
EXECUTABLE  = build/test


default: all

prep:
	mkdir -p build

$(OBJECTS): $(SOURCES_CPP) $(HELPERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


all: prep $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)


clean:
	rm -rf build

