CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
# LIB      = -lSDL2
SRC_DIR  = ./src
SOURCES  = $(shell ls $(SRC_DIR)/*.cpp)
OBJS     = $(SOURCES:.cpp=.o)
TARGET   = assembler

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(LIB) $^ -o $@

$(SRC_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/$*.cpp -o $(SRC_DIR)/$*.o

.PHONY : release
release : CXXFLAGS+=-Ofast
release : all

.PHONY : debug
debug : CXXFLAGS+=-O0 -g3
debug : all

.PHONY : clean
clean :
	-rm -f $(TARGET) $(SRC_DIR)/*.o
