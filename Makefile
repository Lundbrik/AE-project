CXX        = g++
CXXFLAGS   = -O3 -std=c++11


BUILD	    = build
SOURCES_CPP = test.cpp
HELPERS     = nsort.h test_helpers.h nsort_tests.h
OBJECTS     = $(BUILD)/test.o
EXECUTABLE  = $(BUILD)/test


default: all

prep:
	@mkdir -p build

$(OBJECTS): $(SOURCES_CPP) $(HELPERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


all: prep $(EXECUTABLE)

test: all
	build/test $(ARGS)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

clean:
	rm -rf build

