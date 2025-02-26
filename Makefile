CXX:=g++
CXXFLAGS:= -Wall -Wextra -pedantic -std=c++17 -Wconversion -Wshadow -Wunused -Wuninitialized
TARGET:=Longnum
TARGET_TEST:=tests

SRC_DIR:=src
BUILD_DIR:=build
TEST_DIR:=testing
LIB_DIR:=lib


SRCS:=$(wildcard $(SRC_DIR)/*.cpp)

OBJSlib:=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SRCS))

OBJS:=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(SRCS))
OBJS+=$(patsubst ./%.cpp, $(BUILD_DIR)/%.o, ./main.cpp)

OBJStest:=$(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJStest+=$(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_DIR)/test.cpp)

.PHONY: all build debug_build run debug clean test lib


all: build

lib: $(LIB_DIR)/longnum.a

build: $(BUILD_DIR)/$(TARGET)


run: build
	@echo "<Program launch>"
	@$(BUILD_DIR)/$(TARGET).exe


debug_build: CXXFLAGS+= -g
debug_build: clean $(BUILD_DIR)/$(TARGET)


debug: debug_build
	@echo "<Start debugging>"
	@gdb $(BUILD_DIR)/$(TARGET).exe


test: clean $(BUILD_DIR)/$(TARGET_TEST)
	$(BUILD_DIR)/$(TARGET_TEST).exe

clean:
	@echo "<Cleaning>"
ifeq ($(OS),Windows_NT)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(LIB_DIR) rmdir /s /q $(LIB_DIR)
else
	rm -rf $(BUILD_DIR)
	rm -rf $(LIB_DIR)
endif	


$(LIB_DIR)/longnum.a: $(OBJSlib)
ifeq ($(OS),Windows_NT)
	@if not exist $(LIB_DIR) mkdir $(LIB_DIR)
else
	mkdir -p $(LIB_DIR)
endif
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR)/%.o: %.cpp
ifeq ($(OS),Windows_NT)
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
	mkdir -p $(BUILD_DIR)
endif
	$(CXX) $(CXXFLAGS) -c $< -o $@


$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET_TEST): $(OBJStest)
	$(CXX) $(CXXFLAGS) $^ -o $@