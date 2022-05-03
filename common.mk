#///////////////////////////////////////////////
#//
#//  This file is part of
#//   ____  ____  ___  ____  ___  ____  __  __
#//  (  _ \(_  _)/ __)(_  _)/ __)(_  _)(  \/  )
#//   )(_) )_)(_( (_-. _)(_ \__ \ _)(_  )    (
#//  (____/(____)\___/(____)(___/(____)(_/\/\_)
#//
#//  (c) 2020  A. Terstegge
#//
#///////////////////////////////////////////////
#//
#
# Configuration section
CXX           =  g++  # or clang++
CXXFLAGS      = -std=c++17 -g
LIB_BUILD_DIR = $(DIGISIM_DIR)/BUILD
GTEST_DIR     = /usr/local/gtest-1.10.0

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
NET2SIM_DIR       = $(DIGISIM_DIR)/Net2Sim
NET2SIM_SRCS      = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS      = $(foreach obj, $(NET2SIM_SRCS), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
NET2SIM_BIN       = $(NET2SIM_DIR)/Net2Sim
SRC_DIRS         += $(NET2SIM_DIR)

# KiCad Parts
PARTS_DIR         = $(DIGISIM_DIR)/parts
PARTS_SUBDIRS     = $(wildcard $(PARTS_DIR)/*)
KICAD_NET_FILES   = $(wildcard $(PARTS_DIR)/*/*.net)
KICAD_MODELS      = $(KICAD_NET_FILES:.net=)
MODELS_H_FILES    = $(addsuffix .h,   $(KICAD_MODELS))
MODELS_SRC_FILES  = $(addsuffix .cpp, $(KICAD_MODELS))
MODELS_IMPL_FILES = $(wildcard $(PARTS_DIR)/*/*.cpp)
MODELS_OBJS       = $(foreach obj, $(MODELS_SRC_FILES),  $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
MODELS_OBJS      += $(foreach obj, $(MODELS_IMPL_FILES), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
SRC_DIRS         += $(PARTS_SUBDIRS)

# DigiSim library
DIGISIM_SRC_DIR   = $(DIGISIM_DIR)/src
DIGISIM_INC_DIR   = $(DIGISIM_DIR)/include
DIGISIM_SRC_FILES = $(wildcard $(DIGISIM_SRC_DIR)/*.cpp)
DIGISIM_OBJS      = $(MODELS_OBJS)
DIGISIM_OBJS     += $(foreach obj, $(DIGISIM_SRC_FILES), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
DIGISIM_LIB       = $(DIGISIM_DIR)/libDIGISIM.a
DIGISIM_LIB_OPTS  = -L$(DIGISIM_DIR) -lDIGISIM -pthread
SRC_DIRS         += $(DIGISIM_SRC_DIR)

# Tests
TEST_DIR          = $(DIGISIM_DIR)/tests
TEST_SRCS         = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS         = $(foreach obj, $(TEST_SRCS), $(LIB_BUILD_DIR)/$(notdir $(obj)).o)
TEST_BIN          = $(TEST_DIR)/RunTests
SRC_DIRS         += $(TEST_DIR)

# User target
TARGET_SRC_DIRS  += $(dir $(TARGET_NET_FILE))
TARGET_SRC_FILES  = $(TARGET_NET_FILE:.net=.cpp)
TARGET_SRC_FILES += $(foreach dir, $(TARGET_SRC_DIRS), $(wildcard $(dir)/*.cpp))
TARGET_OBJS       = $(foreach obj, $(TARGET_SRC_FILES), $(BUILD_DIR)/$(notdir $(obj)).o)

# Include files
INC_DIRS  += $(DIGISIM_INC_DIR)
INC_DIRS  += $(PARTS_SUBDIRS)
INC_DIRS  += $(TEST_DIR)
INC_DIRS  += $(GTEST_INC)
INC_DIRS  += $(TARGET_INC_DIRS)

INCLUDES = $(addprefix -I, $(INC_DIRS))

#################
# RULES SECTION #
#################

all: build_dir $(NET2SIM_BIN) $(MODELS_H_FILES) $(DIGISIM_LIB) $(TARGET_BIN_FILE)

tests: all $(TEST_BIN)
	$(TEST_BIN)

# Read the dependency files
-include $(NET2SIM_OBJS:.o=.d)
-include $(MODELS_OBJS:.o=.d)
-include $(DIGISIM_OBJS:.o=.d)
-include $(TEST_OBJS:.o=.d)
-include $(TARGET_OBJS:.o=.d)

# Rule to create build directories
.PHONY: build_dir
build_dir :
	$(HIDE) mkdir -p $(LIB_BUILD_DIR)
ifneq ($(BUILD_DIR),)
	$(HIDE) mkdir -p $(BUILD_DIR)
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

$(TEST_BIN) : $(TEST_OBJS) $(DIGISIM_LIB)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS)  -o $@ $^ $(DIGISIM_LIB_OPTS) $(GTEST_LIB_OPTS)

$(TARGET_BIN_FILE) : $(TARGET_OBJS) $(DIGISIM_LIB)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS)  -o $@ $^ $(DIGISIM_LIB_OPTS) $(GTEST_LIB_OPTS)

# Build rule for DIGISIM library
%.a : $(DIGISIM_OBJS)
	@echo "AR   $@"
	$(HIDE) $(AR) -rc $@ $^

# Build rules for kicad models in DigiSim library
#define modelBuildRule
#.PRECIOUS: $$(GEN_DIR)/%.h
#$$(GEN_DIR)/%.h : $$(GEN_DIR)/$(strip $(1))/%.net
#	@echo "NET  $$(notdir $$<)"
#	$$(HIDE) $$(NET2SIM_BIN) -h $$(GEN_DIR)/$(strip $(1)).h -c $$(GEN_DIR)/$(strip $(1)).cpp  $$^
#.PRECIOUS: $$(GEN_DIR)/%.cpp
#$$(GEN_DIR)/%.cpp : $$(GEN_DIR)/$(strip $(1))/%.net
#	@echo "NET  $$(notdir $$<)"
#	$$(HIDE) $$(NET2SIM_BIN) -h $$(GEN_DIR)/$(strip $(1)).h -c $$(GEN_DIR)/$(strip $(1)).cpp  $$^
#endef
#$(foreach model, $(PARTS_SUBDIRS), $(eval $(call modelBuildRule, $(model))))

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
	$(HIDE) rm -f  $(DIGISIM_LIB)
	$(HIDE) rm -f  $(TEST_BIN)
else
	$(HIDE) rm -rf $(BUILD_DIR)
	$(HIDE) rm -f  $(TARGET_BIN_FILE)
	$(HIDE) rm -f  $(TARGET_NET_FILE:.net=.cpp)
	$(HIDE) rm -f  $(TARGET_NET_FILE:.net=.h)
endif
