WORK_DIR = $(shell pwd)
BUILD_DIR = $(WORK_DIR)/build

$(shell mkdir -p $(BUILD_DIR))

INC_PATH = include
INC_FLAG = $(addprefix -I, $(INC_PATH))

CFLAGS = $(INC_FLAG)
CXXFLAGS = $(INC_FLAG)

SRCS = $(shell find -name *.cpp) $(shell find -name *.c)
OBJS = $(subst ./, $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

CC = gcc
CXX = g++
LD = ld
AS = as

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@) && echo + $(CC) $<
	@$(CC) -std=gnu11 $(CFLAGS) -c -o $@ $(realpath $<)

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@) && echo + $(CXX) $<
	@$(CXX) -std=c++17 $(CXXFLAGS) -c -o $@ $(realpath $<)

# test:
# 	@echo $(OBJS)
# 	@echo $(SRCS)

$(BUILD_DIR)/simtxt: $(OBJS)
	@$(CXX) -o $(BUILD_DIR)/simtxt $(OBJS)

run: $(BUILD_DIR)/simtxt
	@$(BUILD_DIR)/simtxt

clean:
	-@rm -r build
