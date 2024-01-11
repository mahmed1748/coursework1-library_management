CXX = g++
CXXFLAGS = -std=c++11
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = library_management_system

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXEC)
