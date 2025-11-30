# Compiler and flags
CXX = C:/tools/mingw64/bin/g++.exe
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = namespace.exe
SOURCE = namespace.cpp

# Default target: compile the program
all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean up compiled files
clean:
	del /Q $(TARGET) 2>nul || echo "Nothing to clean"

# Compile and run in one command
exec: all run

.PHONY: all run clean exec
