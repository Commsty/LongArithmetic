CXX:=g++
CXXFLAGS:= -Wall -Wextra -pedantic -std=c++17 -Wconversion -Wshadow -Wunused -Wuninitialized
TARGET:=Longnum
TARGET_TEST:=tests

SRC_DIR:=src
BUILD_DIR:=build
TEST_DIR:=testing
LIB_DIR:=lib

SRCS:=$(wildcard $(SRC_DIR)/*.cpp)
OBJS:=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SRCS))

all: build

build: lib $(BUILD_DIR)/$(TARGET)


lib: $(LIB_DIR)/longnum.a


$(LIB_DIR)/liblongnum.a: $(OBJS)
ifeq ($(OS),Windows_NT)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
else
	mkdir -p $(LIB_DIR)
endif
	ar rcs $@ $^

$(BUILD_DIR)/$(TARGET): main.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif
	$(CXX) $(CXXFLAGS) $< -o $@ -Iinclude -Llib -llongnum