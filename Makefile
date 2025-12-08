CXX := g++
CXXFLAGS := -Wall -Wextra -g -std=c++11 -Iinclude

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TARGET := $(BIN_DIR)/tp3.out

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

FILE ?= entrada.txt

all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(TARGET)

run: all
	./$(TARGET) < $(FILE)
