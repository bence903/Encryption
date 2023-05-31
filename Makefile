CC = g++
CFLAGS = -std=c++11

# List of source files
SOURCES = RSA.cpp Caesar.cpp main.cpp

# List of object files
OBJECTS = $(SOURCES:.cpp=.o)

# Name of the executable
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
