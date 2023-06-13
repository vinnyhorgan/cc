CXX=g++
CXXFLAGS=-Ideps/include -Wall -Wextra -pedantic -std=c++17 -O2
LDFLAGS=-Ldeps/lib -llua -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCDIR=src
DEPS_DIR=deps/src
SOURCES=$(wildcard $(SRCDIR)/*.cpp $(DEPS_DIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=cc

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
