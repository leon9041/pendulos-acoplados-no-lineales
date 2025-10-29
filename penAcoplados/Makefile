CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = pendulos

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@

clean:
	rm -f src/*.o $(EXEC)
