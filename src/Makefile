CXX ?= g++

CXXFLAGS ?= -O3 -Wall -Wextra -pedantic -Weffc++ -std=c++17

TARGET := dd-cpp.exe

SRCS := main.cpp argv_parser.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET)
