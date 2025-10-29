CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

TARGET = Q2b Q5b Q6 B1 B2
OBJS = Graph.o Q2b.o Q5b.o Q6.o B1.o B2.o
OUTFILES = Q*_output.txt B*_output.txt 

all: $(TARGET)


Q2b: Graph.o Q2b.o
	$(CXX) $(CXXFLAGS) -o Q2b Graph.o Q2b.o

Q5b: Graph.o Q5b.o
	$(CXX) $(CXXFLAGS) -o Q5b Graph.o Q5b.o

Q6: Graph.o Q6.o
	$(CXX) $(CXXFLAGS) -o Q6 Graph.o Q6.o

B1: Graph.o B1.o
	$(CXX) $(CXXFLAGS) -o B1 Graph.o B1.o

B2: B2.o
	$(CXX) $(CXXFLAGS) -o B2 B2.o

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Graph.cpp



Q2b.o : Q2b.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Q2b.cpp

Q5b.o : Q5b.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Q5b.cpp

Q6.o : Q6.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c Q6.cpp

B1.o: B1.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c B1.cpp

B2.o: B2.cpp
	$(CXX) $(CXXFLAGS) -c B2.cpp

clean:
	rm -f $(OBJS) $(TARGET) $(OUTFILES)

