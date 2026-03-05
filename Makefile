# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17

# Target Binary Name
TARGET = server

# Build Rules
all: $(TARGET)

$(TARGET): phase1_server.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) phase1_server.cpp

clean:
	rm -f $(TARGET)