
#Requires package graphicsmagick-libmagick-dev-compat

# use make mode=debug for compiling with debug flags


TARGET_EXEC = rt
SRC_DIRS = ./src
BUILD_DIR = ./build
CC=g++
CFLAGS=-Werror -Wall -O2 -std=c++11

ifeq ($(mode),debug)
	CXXFLAGS=  $(shell Magick++-config --cppflags) -Werror -Wall -ggdb -pg -std=c++11
	LDFLAGS =  $(shell Magick++-config --ldflags --libs) -lm -lpng -pg -pthread -lGL -lglfw -lGLEW -lglut

else
   mode = release
	 CXXFLAGS= $(shell Magick++-config --cppflags) -Werror -fpic -Wall -O3 -std=c++14
	 LDFLAGS = $(shell Magick++-config --ldflags --libs) -lm -lpng -flto  -pthread -pg -lGL -lglfw -lGLEW -lglut

endif

#INC_DIRS = ./headers

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS = $(INC_FLAGS) -MMD -MP


$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)

	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
