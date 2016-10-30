CXX         = g++
CXXFLAGS    = -O3 -fopenmp -std=c++11
CXXPARFLAGS = -O3 -pthread -std=c++11


BUILD	    = build
SOURCES_CPP = test.cpp
HELPERS     = nsort.h test_helpers.h nsort_tests.h fordjohnson.h
OBJECTS     = $(BUILD)/test.o
EXECUTABLE  = $(BUILD)/test

EXPERIMENT_CPP = performance_nsort.cpp
E_HELPERS      = test_helpers.h nsort.h fordjohnson.h
E_OBJECTS      = $(BUILD)/experiment.o
E_EXECUTABLE   = $(BUILD)/experiment

# Parallel
PARTEST_CPP   = partest.cpp
PT_EXECUTABLE = partest

INSTEST_CPP   = instest.cpp
IT_EXECUTABLE = instest

BENCH_ALLOC_CPP = benchalloc.cpp
BA_EXECUTABLE   = benchalloc

BENCH_MEM_CONST_CPP = benchmemconst.cpp
BMC_EXECUTABLE    	= benchmemconst

BENCH_MEM_EMPTY_CPP = benchmemempty.cpp
BME_EXECUTABLE 		= benchmemempty

BENCH_MEM_MANAG_CPP = benchmemman.cpp
BMM_EXECUTABLE 		= benchmemman

BENCH_PIVOT_CPP = benchpivot.cpp
BP_EXECUTABLE 	= benchpivot

BENCH_SORT_CPP = benchsort.cpp
BS_EXECUTABLE  = benchsort

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

# Parallel
partest:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(PT_EXECUTABLE) $(PARTEST_CPP)

benchalloc:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(BA_EXECUTABLE) $(BENCH_ALLOC_CPP)

benchmemconst:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(BMC_EXECUTABLE) $(BENCH_MEM_CONST_CPP)

benchmemempty:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(BME_EXECUTABLE) $(BENCH_MEM_EMPTY_CPP)

benchmemman:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(BMM_EXECUTABLE) $(BENCH_MEM_MANAG_CPP)

benchpivot:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(BP_EXECUTABLE) $(BENCH_PIVOT_CPP)

benchsort:
	$(CXX) $(CXXPARFLAGS) -o $(BUILD)/$(BS_EXECUTABLE) $(BENCH_SORT_CPP)

parallel: partest benchalloc benchmemconst benchmemempty benchmemman benchpivot benchsort
	mkdir -p $(BUILD)/results

run_parallel: parallel
	cd $(BUILD)
	./$(PT_EXECUTABLE)
	./$(BA_EXECUTABLE)
	./$(BMC_EXECUTABLE)
	./$(BME_EXECUTABLE)
	./$(BMM_EXECUTABLE)
	./$(BP_EXECUTABLE)
	./$(BS_EXECUTABLE)
