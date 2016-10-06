CXX        = g++
CXXFLAGS   = -O3


BUILD	    = build
SOURCES_CPP = small.cpp
HELPERS     = nsort.h
OBJECTS     = build/small.o
EXECUTABLE  = build/test


default: all

$(OBJECTS): $(SOURCES_CPP) $(HELPERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)


clean:
	rm -f build/*

