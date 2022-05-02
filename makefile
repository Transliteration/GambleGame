# LIBRARY_PATH = /libs/

LDFLAGS_SFML := -lsfml-graphics -lsfml-window -lsfml-system
# LDFLAGS_SFML_ := -L/libs/libsfml-graphics.so.2.5 -L/libs/libsfml-system.so.2.5 -L/libs/libsfml-window.so.2.5
CXXFLAGS :=  -Wall -std=gnu++17 -O3 -fconcepts

LD_LIBRARY_PATH := /libs/

TARGET_EXEC ?= app.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX)  $(OBJS) -o $@ $(LDFLAGS_SFML)

$(BUILD_DIR)/%.cpp.o: %.cpp %.hpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
