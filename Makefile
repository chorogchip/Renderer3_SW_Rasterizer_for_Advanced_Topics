CC = g++
CPPFLAGS = -std=c++2a -Wall -O2 -lm
LDFLAGS = 

TARGET  = main
SRC_DIR = ./src
DEP_DIR = ./dependencies
OBJ_DIR = ./objs

FILES = $(basename $(notdir $(wildcard $(SRC_DIR)/**.cpp)))
SRCS = $(addsuffix .cpp,$(FILES))
DEPS = $(addsuffix .d,$(FILES))
OBJS = $(addsuffix .o,$(FILES))
LIB_OBJS = decoder.o encoder.o image_iterator.o stdio.o
FINAL_OBJS = $(OBJS) $(LIB_OBJS)
SOURCES = $(patsubst %,$(SRC_DIR)/%,$(SRCS))
DEPENDENCIES = $(patsubst %,$(DEP_DIR)/%,$(DEPS))
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(FINAL_OBJS))

all: $(TARGET)

$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	echo -n "$(OBJ_DIR)/" > $@ | $(CC) $(CPPFLAGS) $< -MM >> $@

include $(DEPENDENCIES)

objs/decoder.o: src/tga/decoder.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
objs/encoder.o: src/tga/encoder.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
objs/image_iterator.o: src/tga/image_iterator.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@
objs/stdio.o: src/tga/stdio.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) $(DEPENDENCIES)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(TARGET) | ./main

clean:
	rm -f $(OBJECTS) $(DEPENDENCIES) $(TARGET)