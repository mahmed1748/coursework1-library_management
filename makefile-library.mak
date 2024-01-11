CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = library-system.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = library-system

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)
