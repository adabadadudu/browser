TARGET ?= awb
SRC_DIRS ?= ./src
CXX = clang++
SRCS :=$(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(addsuffix .o,$(basename $(SRCS)))

LDFLAGS = -lssl -lcrypto -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS ?= -pedantic -g -Wall -Wextra -Isrc/ -Wno-gnu-zero-variadic-macro-arguments

%.o: %.cpp
	@echo [ CXX ] $<
	@$(CXX) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)

	@echo [ BIN ] $<
	@$(CXX) $(LDFLAGS) $(OBJS) -o $@ 
.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) 

