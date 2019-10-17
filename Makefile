IDIR = ./include
SDIR = ./src
TEST = ./tests
CXX = g++
CXXFLAGS = -std=c++11 -w -g -O2 -I $(IDIR)
TESTFLAGS = -lgtest -lgtest_main -pthread

comparison: FORCE
	$(CXX) $(SDIR)/main.cpp $(SDIR)/vEBTree.cpp -o $@ $(CXXFLAGS)

test: FORCE
	$(CXX) $(TEST)/main.cpp $(SDIR)/vEBTree.cpp -o $@ $(CXXFLAGS) $(TESTFLAGS)

graphic: FORCE
	python3 $(SDIR)/graphic.py

FORCE: ;

clean:
	rm comparison
	rm test
