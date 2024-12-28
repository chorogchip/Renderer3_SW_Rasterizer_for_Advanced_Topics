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
SOURCES = $(patsubst %,$(SRC_DIR)/%,$(SRCS))
DEPENDENCIES = $(patsubst %,$(DEP_DIR)/%,$(DEPS))
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJS))

all: $(TARGET)

$(DEP_DIR)/%.d: $(SRC_DIR)/%.cpp
	echo -n "$(OBJ_DIR)/" > $@ | $(CC) $(CPPFLAGS) $< -MM >> $@

include $(DEPENDENCIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS) $(DEPENDENCIES)
	$(CC) $(CPPFLAGS) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(OBJECTS) $(DEPENDENCIES) $(TARGET)



