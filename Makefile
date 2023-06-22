CXX=g++
CXXFLAGS=-Ideps/include -Wall -Wextra -pedantic -std=c++17 -g -Wno-missing-field-initializers # -O2 messes up some error handling
LDFLAGS=-Ldeps/lib -lenet -llua -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lcrypto -lssl # i have no idea how i will link these two on windows...

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
