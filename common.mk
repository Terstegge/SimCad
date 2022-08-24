#/////////////////////////////////////////////////
#//
#//  This file is part of
#//      ___  ____  __  __  ___    __    ____
#//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
#//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
#//     (___/(____)(_/\/\_)\___)(__)(__)(____/
#//
#//  A simulation library for electronic circuits
#//  See also https://github.com/Terstegge/SimCad
#//  (c) Andreas Terstegge
#//
#/////////////////////////////////////////////////
#//

#########################
# Configuration section #
#########################

CXX           =  g++  # or clang++
CXXFLAGS      = -std=c++17 -g
LIB_BUILD_DIR = $(SIMCAD_DIR)/BUILD
GTEST_DIR     = /usr/local/gtest-1.10.0

###################
# VARABLE SECTION #
###################

# Utility to control makefile output
# (detailed output if VERBOSE defined).
ifdef VERBOSE
HIDE :=
else
HIDE := @
endif

# Goole Test
GTEST_INC         = $(GTEST_DIR)/googletest/include/
GTEST_LIB_OPTS    = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

# Net2Sim 
NET2SIM_DIR       = $(SIMCAD_DIR)/Net2Sim
NET2SIM_SRCS      = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS      = $(foreach obj, $(NET2SIM_SRCS), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
NET2SIM_BIN       = $(NET2SIM_DIR)/Net2Sim
SRC_DIRS         += $(NET2SIM_DIR)

# KiCad Parts
PARTS_DIR         = $(SIMCAD_DIR)/parts
PARTS_SUBDIRS     = $(wildcard $(PARTS_DIR)/*)
KICAD_NET_FILES   = $(wildcard $(PARTS_DIR)/*/*.net)
KICAD_MODELS      = $(KICAD_NET_FILES:.net=)
MODELS_H_FILES    = $(addsuffix .h,   $(KICAD_MODELS))
MODELS_SRC_FILES  = $(addsuffix .cpp, $(KICAD_MODELS))
MODELS_IMPL_FILES = $(wildcard $(PARTS_DIR)/*/*.cpp)
MODELS_OBJS       = $(foreach obj, $(MODELS_SRC_FILES),  $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
MODELS_OBJS      += $(foreach obj, $(MODELS_IMPL_FILES), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
SRC_DIRS         += $(PARTS_SUBDIRS)

# SimCad library
SIMCAD_SRC_DIR   = $(SIMCAD_DIR)/src
SIMCAD_INC_DIR   = $(SIMCAD_DIR)/include
SIMCAD_SRC_FILES = $(wildcard $(SIMCAD_SRC_DIR)/*.cpp)
SIMCAD_OBJS      = $(MODELS_OBJS)
SIMCAD_OBJS     += $(foreach obj, $(SIMCAD_SRC_FILES), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
SIMCAD_LIB       = $(SIMCAD_DIR)/libSIMCAD.a
SIMCAD_LIB_OPTS  = -L$(SIMCAD_DIR) -lSIMCAD -lboost_iostreams -pthread
SRC_DIRS         += $(SIMCAD_SRC_DIR)

# Tests
TEST_DIR          = $(SIMCAD_DIR)/tests
TEST_SUBDIRS      = $(wildcard $(TEST_DIR)/*)
TEST_SRCS         = $(wildcard $(TEST_DIR)/*/*.cpp)
TEST_OBJS         = $(foreach obj, $(TEST_SRCS), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
TEST_BIN          = $(SIMCAD_DIR)/RunTests
SRC_DIRS         += $(TEST_SUBDIRS)

# User target
TARGET_SRC_DIRS  += $(dir $(TARGET_NET_FILE))
TARGET_SRC_FILES  = $(TARGET_NET_FILE:.net=.cpp)
TARGET_SRC_FILES += $(foreach dir, $(TARGET_SRC_DIRS), $(wildcard $(dir)/*.cpp))
TARGET_OBJS       = $(foreach obj, $(TARGET_SRC_FILES), $(BUILD_DIR)/$(notdir $(obj)).o)

# Include files
INC_DIRS  += $(SIMCAD_INC_DIR)
INC_DIRS  += $(PARTS_SUBDIRS)
INC_DIRS  += $(TEST_SUBDIRS)
INC_DIRS  += $(GTEST_INC)
INC_DIRS  += $(TARGET_INC_DIRS)

INCLUDES = $(addprefix -I, $(INC_DIRS))

#################
# RULES SECTION #
#################

all: build_dir $(NET2SIM_BIN) $(MODELS_H_FILES) $(SIMCAD_LIB) $(TARGET_BIN_FILE)

tests: all $(TEST_BIN)
	$(TEST_BIN)

# Read the dependency files
-include $(NET2SIM_OBJS:.o=.d)
-include $(MODELS_OBJS:.o=.d)
-include $(SIMCAD_OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)
-include $(TARGET_OBJS:.o=.d)

# Rule to create build directories
.PHONY: build_dir
build_dir :
ifneq ($(BUILD_DIR),)
	$(HIDE) mkdir -p $(BUILD_DIR)
else
	$(HIDE) mkdir -p $(LIB_BUILD_DIR)
endif

# Compile rule for DigiSim library
define compileRulesLib
.PRECIOUS: $(LIB_BUILD_DIR)/%.cpp.o
$(LIB_BUILD_DIR)/%.cpp.o : $(1)/%.cpp
	@echo "C++  $$(notdir $$<)"
	$(HIDE) $$(CXX) $$(CXXFLAGS) $$(INCLUDES) -c -o $$@ $$< -MMD
endef
$(foreach srcdir, $(SRC_DIRS), $(eval $(call compileRulesLib, $(srcdir))))

# Compile rule for user program
define compileRules
.PRECIOUS: $(BUILD_DIR)/%.cpp.o
$(BUILD_DIR)/%.cpp.o : $(1)/%.cpp
	@echo "C++  $$(notdir $$<)"
	$(HIDE) $$(CXX) $$(CXXFLAGS) $$(INCLUDES) -c -o $$@ $$< -MMD
endef
$(foreach srcdir, $(TARGET_SRC_DIRS), $(eval $(call compileRules, $(srcdir))))

# Link rules for binaries
$(NET2SIM_BIN) : $(NET2SIM_OBJS)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_BIN) : $(TEST_OBJS) $(SIMCAD_LIB)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS)  -o $@ $^ $(SIMCAD_LIB_OPTS) $(GTEST_LIB_OPTS)

$(TARGET_BIN_FILE) : $(TARGET_OBJS) $(SIMCAD_LIB)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS)  -o $@ $^ $(SIMCAD_LIB_OPTS)

# Build rule for SIMCAD library
%.a : $(SIMCAD_OBJS)
	@echo "AR   $@"
	$(HIDE) $(AR) -rc $@ $^

# Build rules for user kicad models

.PRECIOUS: %.h
%.h : %.net
	@echo "NET  $(notdir $<)"
	$(HIDE) $(NET2SIM_BIN) $^

.PRECIOUS: %.cpp
%.cpp : %.net
	@echo "NET  $(notdir $<)"
	$(HIDE) $(NET2SIM_BIN)  $^

.PHONY: clean
clean:
ifeq ($(TARGET_BIN_FILE),)
	$(HIDE) rm -rf $(LIB_BUILD_DIR)
	$(HIDE) rm -f  $(NET2SIM_BIN) 
	$(HIDE) rm -f  $(MODELS_H_FILES)
	$(HIDE) rm -f  $(MODELS_SRC_FILES)
	$(HIDE) rm -f  $(SIMCAD_LIB)
	$(HIDE) rm -f  $(TEST_BIN)
else
	$(HIDE) rm -rf $(BUILD_DIR)
	$(HIDE) rm -f  $(TARGET_BIN_FILE)
	$(HIDE) rm -f  $(TARGET_NET_FILE:.net=.cpp)
	$(HIDE) rm -f  $(TARGET_NET_FILE:.net=.h)
endif
