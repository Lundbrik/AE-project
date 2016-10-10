CXX        = g++
CXXFLAGS   = -O3


BUILD	    = build
SOURCES_CPP = test.cpp
HELPERS     = nsort.h test_helpers.h
OBJECTS     = $(BUILD)/test.o
EXECUTABLE  = $(BUILD)/test


default: all

prep:
	@mkdir -p build

$(OBJECTS): $(SOURCES_CPP) $(HELPERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


all: prep $(EXECUTABLE)

test: all
	build/test

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)


clean:
	rm -rf build

