CXX      = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra
SRC_DIR = ../src
TESTS = test_assembler.o
OBJS = assembler.o field.o data_processing_field.o multiplication_field.o utility.o
TARGET = run_all_test

all : $(TARGET)

$(TARGET) : $(TESTS) $(OBJS)
	$(CXX) $^ -lgtest -lgtest_main -lpthread -o $(TARGET)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp

%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/$*.cpp

run : $(TARGET)
	./$(TARGET)

.PHONY : release
release : CXXFLAGS+=-Ofast
release : all

.PHONY : debug
debug : CXXFLAGS+=-O0 -g3
debug : all

.PHONY : clean
clean :
	-rm -f $(TARGET) $(OBJS) $(TESTS)
