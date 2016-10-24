CXX        = g++
CXXFLAGS   = -O3 -std=c++11


BUILD	    = build
SOURCES_CPP = test.cpp
HELPERS     = nsort.h test_helpers.h nsort_tests.h fordjohnson.h
OBJECTS     = $(BUILD)/test.o
EXECUTABLE  = $(BUILD)/test

EXPERIMENT_CPP = performance_nsort.cpp
E_HELPERS      = test_helpers.h nsort.h
E_OBJECTS      = $(BUILD)/experiment.o
E_EXECUTABLE   = $(BUILD)/experiment


default: all

prep:
	@mkdir -p build

# Test object
$(OBJECTS): $(SOURCES_CPP) $(HELPERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<


all: prep $(EXECUTABLE)

test: all
	build/test $(ARGS)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)


# Experiment
$(E_OBJECTS): $(EXPERIMENT_CPP) $(E_HELPERS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(E_EXECUTABLE): $(E_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(E_EXECUTABLE) $(E_OBJECTS)

experi: prep $(E_EXECUTABLE)
	$(BUILD)/experiment $(INPUTS) $(RUNS)

clean:
	rm -rf build

