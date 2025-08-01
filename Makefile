# Simple Makefile for the C++ API server

# Variables
CXX = g++
CXXFLAGS = -std=c++17 -Wall -I Crow/include
LDFLAGS = -lboost_system -lboost_thread -lpthread
TARGET = api_server
SRC_DIR = src
SRC_FILE = $(SRC_DIR)/main.cpp

.PHONY: all clean compile check distcheck

all: compile

compile: $(TARGET)

$(TARGET): $(SRC_FILE)
	@echo "Compiling the C++ API server..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) $< $(LDFLAGS)

clean:
	@echo "Cleaning up build files..."
	rm -f $(TARGET)

check:
	@echo "Running tests..."
	@echo "No tests are configured yet. This is a placeholder target."
	# Add your test commands here. For example:
	# ./$(TARGET) --test

distcheck:
	@echo "Running distribution check..."
	@echo "This is a placeholder target. Add your packaging and testing logic here."


