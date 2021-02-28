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
# Configuration
DIGISIM_DIR = .
BUILD_DIR   = BUILD

# Goole Test
GTEST_DIR  = /usr/local/gtest-1.10.0
GTEST_INC  = $(GTEST_DIR)/googletest/include/
GTEST_LIBS = -L. -L$(GTEST_DIR)/lib -lgtest -lgtest_main -lDIGISIM

# Utility to control output (detailed if VERBOSE defined).
ifdef VERBOSE
HIDE :=
else
HIDE := @
endif


# Net2Sim 
NET2SIM_DIR       = $(DIGISIM_DIR)/Net2Sim
NET2SIM_SRCS      = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS      = $(foreach obj, $(NET2SIM_SRCS), $(BUILD_DIR)/$(notdir $(obj)).o)
NET2SIM_BIN       = $(NET2SIM_DIR)/Net2Sim
NET2SIM_DEPS      = $(NET2SIM_OBJS:.o=.d)
SRC_DIRS         += $(NET2SIM_DIR)

# KiCad models
KICAD_DIR         = $(DIGISIM_DIR)/kicad
KICAD_GEN_DIR     = $(KICAD_DIR)/gen
KICAD_IMPL_DIR    = $(KICAD_DIR)/impl
KICAD_NET_FILES   = $(wildcard $(KICAD_DIR)/*/*.net)
KICAD_NET_DIRS    = $(dir $(KICAD_NET_FILES))
KICAD_MODELS      = $(notdir $(KICAD_NET_FILES:.net=))
KICAD_H_FILES     = $(addsuffix .h,   $(addprefix $(KICAD_GEN_DIR)/, $(KICAD_MODELS)))
KICAD_SRC_FILES   = $(addsuffix .cpp, $(addprefix $(KICAD_GEN_DIR)/, $(KICAD_MODELS)))
KICAD_IMPL_FILES  = $(wildcard $(KICAD_IMPL_DIR)/*.cpp)
KICAD_OBJS        = $(foreach obj, $(KICAD_SRC_FILES),  $(BUILD_DIR)/$(notdir $(obj)).o)
KICAD_OBJS       += $(foreach obj, $(KICAD_IMPL_FILES), $(BUILD_DIR)/$(notdir $(obj)).o)
KICAD_DEPS        = $(KICAD_OBJS:.o=.d)
SRC_DIRS         += $(KICAD_GEN_DIR) $(KICAD_IMPL_DIR)

# DigiSim library
DIGISIM_SRC_DIR   = $(DIGISIM_DIR)/src
DIGISIM_INC_DIR   = $(DIGISIM_DIR)/include
DIGISIM_SRC_FILES = $(wildcard $(DIGISIM_SRC_DIR)/*.cpp)
DIGISIM_OBJS      = $(KICAD_OBJS)
DIGISIM_OBJS     += $(foreach obj, $(DIGISIM_SRC_FILES), $(BUILD_DIR)/$(notdir $(obj)).o)
DIGISIM_DEPS      = $(DIGISIM_OBJS:.o=.d)
DIGISIM_LIB       = $(DIGISIM_DIR)/libDIGISIM.a
SRC_DIRS         += $(DIGISIM_SRC_DIR)

# Tests
TEST_DIR          = $(DIGISIM_DIR)/tests
TEST_SRCS         = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS         = $(foreach obj, $(TEST_SRCS), $(BUILD_DIR)/$(notdir $(obj)).o)
TEST_BIN          = $(TEST_DIR)/RunTests
TEST_DEPS         = $(TEST_OBJS:.o=.d)
SRC_DIRS         += $(TEST_DIR)

# Compiler options
CXX        =  g++-8  # or clang++
CXXFLAGS   = -std=c++2a -g
INCLUDES   = -I$(KICAD_GEN_DIR)
INCLUDES  += -I$(KICAD_IMPL_DIR)
INCLUDES  += -I$(DIGISIM_INC_DIR)/core
INCLUDES  += -I$(DIGISIM_INC_DIR)/gates
INCLUDES  += -I$(DIGISIM_INC_DIR)/twopoles
INCLUDES  += -I$(DIGISIM_INC_DIR)/threepoles
INCLUDES  += -I$(TEST_DIR)
INCLUDES  += -I$(GTEST_INC)


#################
# RULES SECTION #
#################

all: build_dir $(NET2SIM_BIN) $(KICAD_H_FILES) $(KICAD_SRC_FILES) $(DIGISIM_LIB)

test: all $(TEST_BIN)
	$(TEST_BIN)


# include the dependency files
-include $(NET2SIM_DEPS) $(KICAD_DEPS) $(DIGISIM_DEPS) $(TEST_DEPS)

# Rule to create build directory
.PHONY: build_dir
build_dir :
	$(HIDE) mkdir -p $(BUILD_DIR)

# Compile rules
define compileRules
.PRECIOUS: $(BUILD_DIR)/%.cpp.o
$(BUILD_DIR)/%.cpp.o : $(1)/%.cpp
	@echo "C++  $$(notdir $$<)"
	$(HIDE) $$(CXX) $$(CXXFLAGS) $$(INCLUDES) -c -o $$@ $$< -MMD
endef
$(foreach srcdir, $(SRC_DIRS), $(eval $(call compileRules, $(srcdir))))

# Link rules for binaries
$(NET2SIM_BIN) : $(NET2SIM_OBJS)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_BIN) : $(TEST_OBJS)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS)  -o $@ $^ $(GTEST_LIBS) -pthread

# Build rule for library
%.a : $(DIGISIM_OBJS)
	@echo "AR   $@"
	$(HIDE) $(AR) -rc $@ $^

# Build rules for kicad models
define modelBuildRule
$$(KICAD_GEN_DIR)/%.h : $$(KICAD_DIR)/$(strip $(1))/%.net
	@echo "NET  $$(notdir $$<)"
	$$(HIDE) $$(NET2SIM_BIN) -h $$(KICAD_GEN_DIR)/$(strip $(1)).h -c $$(KICAD_GEN_DIR)/$(strip $(1)).cpp  $$^
$$(KICAD_GEN_DIR)/%.cpp : $$(KICAD_DIR)/$(strip $(1))/%.net
	@echo "NET  $$(notdir $$<)"
	$$(HIDE) $$(NET2SIM_BIN) -h $$(KICAD_GEN_DIR)/$(strip $(1)).h -c $$(KICAD_GEN_DIR)/$(strip $(1)).cpp  $$^
endef
$(foreach model, $(KICAD_MODELS), $(eval $(call modelBuildRule, $(model))))

.PHONY: clean
clean:
	$(HIDE) rm -rf $(BUILD_DIR)
	$(HIDE) rm -f  $(NET2SIM_BIN) 
	$(HIDE) rm -f  $(KICAD_H_FILES)
	$(HIDE) rm -f  $(KICAD_SRC_FILES)
	$(HIDE) rm -f  $(DIGISIM_LIB)
	$(HIDE) rm -f  $(TEST_BIN)
