CXX:=g++
CXXFLAGS:= -Wall -Wextra -pedantic -std=c++17 -Wconversion -Wshadow -Wunused -Wuninitialized
TARGET:=Longnum_lib_test
SRC_DIR:=src
BUILD_DIR:=build

SRCS:=$(wildcard $(SRC_DIR)/*.cpp)
OBJS:=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all build debug_build run debug clean


all: build


build: $(BUILD_DIR)/$(TARGET)


run: build
	@echo "<Program launch>"
	$(BUILD_DIR)/$(TARGET).exe


debug_build: CXXFLAGS+= -g
debug_build: $(BUILD_DIR)/$(TARGET)


debug: debug_build
	@echo "<Start debugging>"
	@gdb $(BUILD_DIR)/$(TARGET).exe


clean:
	@echo "<Cleaning>"
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@