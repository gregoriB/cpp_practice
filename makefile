CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20 -pedantic-errors

SRCS = main.cpp lib/linked_list.cpp lib/print.cpp lib/quick_sort.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
