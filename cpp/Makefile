NAME = ca

SRC_DIR = $(CURDIR)/src
CLI_DIR = $(CURDIR)/cli
TEST_DIR = $(CURDIR)/test
BIN_DIR = $(CURDIR)/bin
LIB_DIR = $(CURDIR)/lib
OBJ_DIR = $(CURDIR)/obj

CXX = clang
CXXFLAGS = -Wall -O3 -std=c++11 -I/usr/include -I$(SRC_DIR)
LDFLAGS = -L/usr/lib -L$(LIB_DIR)
AR = ar rcs
MKDIR_P = mkdir -p
RM_RF = rm -Rf

SHARED_LIB_EXT = .so
STATIC_LIB_EXT = .a
SHARED_LIB_FLAGS = -shared

LIBS = -lstdc++
CLI_LIBS = -lncurses
TEST_LIBS =

ifeq ($(OS),Windows_NT)
	PLATFORM := Windows
else
	PLATFORM := $(shell uname -s)
endif
ifeq ($(PLATFORM),Darwin)
	SHARED_LIB_EXT = .dylib
	SHARED_LIB_FLAGS = -dynamiclib
else
	# TODO
endif

TARGET_CLI = $(BIN_DIR)/$(NAME)
TARGET_TEST = $(BIN_DIR)/$(NAME)-test
TARGET_SHARED_LIB = $(LIB_DIR)/lib$(NAME)$(SHARED_LIB_EXT)
TARGET_STATIC_LIB = $(LIB_DIR)/lib$(NAME)$(STATIC_LIB_EXT)

LIB_SRCS = $(wildcard $(SRC_DIR)/*.cc) $(wildcard $(SRC_DIR)/$(NAME)/*.cc)
LIB_OBJS = $(subst $(CURDIR),$(OBJ_DIR),$(LIB_SRCS:.cc=.o))
CLI_SRCS = $(wildcard $(CLI_DIR)/*.cc)
CLI_OBJS = $(subst $(CURDIR),$(OBJ_DIR),$(CLI_SRCS:.cc=.o))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cc) $(wildcard $(TEST_DIR)/$(NAME)/*.cc)
TEST_OBJS = $(subst $(CURDIR),$(OBJ_DIR),$(TEST_SRCS:.cc=.o))
DEPS = $(LIB_OBJS:%.o=%.d) $(CLI_OBJS:%.o=%.d) $(TEST_OBJS:%.o=%.d)

default: all

all: cli test

cli: $(TARGET_CLI)

shared_lib: $(TARGET_SHARED_LIB)

static_lib: $(TARGET_STATIC_LIB)

test: $(TARGET_TEST)
	$(TARGET_TEST)

clean:
	$(RM_RF) $(BIN_DIR) $(LIB_DIR) $(OBJ_DIR)

$(TARGET_SHARED_LIB): $(LIB_DIR) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(SHARED_LIB_FLAGS) -o $@ $(LIB_OBJS)

$(TARGET_STATIC_LIB): $(LIB_DIR) $(LIB_OBJS)
	$(AR) $@ $(LIB_OBJS)

$(TARGET_CLI): $(TARGET_STATIC_LIB) $(BIN_DIR) $(CLI_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(CLI_LIBS) -o $@ $(CLI_OBJS) $(TARGET_STATIC_LIB)

$(TARGET_TEST): $(TARGET_SHARED_LIB) $(BIN_DIR) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(TEST_LIBS) -o $@ $(TEST_OBJS) $(TARGET_SHARED_LIB)

$(OBJ_DIR)/%.o: $(CURDIR)/%.cc
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -o $@ -c $<

$(BIN_DIR):
	@$(MKDIR_P) $(BIN_DIR)

$(LIB_DIR):
	@$(MKDIR_P) $(LIB_DIR)

-include $(DEPS)
.PHONY: all cli shared_lib test clean
