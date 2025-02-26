CXX:=g++
CXXFLAGS:= -Wall -Wextra -pedantic -std=c++17 -Wconversion -Wshadow -Wunused -Wuninitialized -g
TARGET_MAIN:=main
TARGET_TEST:=Tests
TARGET_LIB:=liblongnum

SRC_DIR:=src
BUILD_DIR:=build
TEST_DIR:=testing
LIB_DIR:=lib

SRCS:=$(wildcard $(SRC_DIR)/*.cpp)
OBJS:=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all build test_build test run lib clean

all: build

build: lib $(BUILD_DIR)/$(TARGET_MAIN)

test_build: lib $(TEST_DIR)/$(TARGET_TEST)

test: test_build
	./$(TEST_DIR)/$(TARGET_TEST)

run: build
	./$(BUILD_DIR)/$(TARGET_MAIN)

lib: $(LIB_DIR)/$(TARGET_LIB).a

clean:
	@echo "<Cleaning>"
ifeq ($(OS),Windows_NT)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(LIB_DIR) rmdir /s /q $(LIB_DIR)
else
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIR)
endif

$(LIB_DIR)/$(TARGET_LIB).a: $(OBJS)
ifeq ($(OS),Windows_NT)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
else
	mkdir -p $(LIB_DIR)
endif
	ar rcs $@ $^

$(BUILD_DIR)/$(TARGET_MAIN): main.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif
	$(CXX) $(CXXFLAGS) $< -o $@ -Iinclude -Llib -llongnum

$(TEST_DIR)/$(TARGET_TEST): $(TEST_DIR)/test.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -Iinclude -Llib -llongnum

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif
	$(CXX) $(CXXFLAGS) -c $< -o $@