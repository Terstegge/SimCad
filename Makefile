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
BUILD_DIR  = BUILD
BIN_DIR    = bin
LIB_DIR    = lib

# Compiler options
CXX        =  g++  # or clang++
CXXFLAGS   = -std=c++17 -g
INCLUDES   = -Iinclude -Ikicad/include

# Utility to control output (detailed if VERBOSE defined).
ifdef VERBOSE
HIDE :=
else
HIDE := @
endif

# Net2Sim 
NET2SIM_DIR       = Net2Sim
NET2SIM_SRCS      = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS      = $(foreach obj, $(NET2SIM_SRCS), $(BUILD_DIR)/$(notdir $(obj)).o)
NET2SIM_BIN       = $(BIN_DIR)/Net2Sim
NET2SIM_DEPS      = $(NET2SIM_OBJS:.o=.d)
SRC_DIRS         += $(NET2SIM_DIR)

# KiCad models
KICAD_DIR         = kicad
KICAD_NET_FILES   = $(wildcard $(KICAD_DIR)/*/*.net)
KICAD_NET_DIRS    = $(dir $(KICAD_NET_FILES))
KICAD_MODELS      = $(notdir $(KICAD_NET_FILES:.net=))
KICAD_H_DIR       = $(KICAD_DIR)/include
KICAD_H_FILES     = $(addsuffix .h, $(addprefix $(KICAD_H_DIR)/, $(KICAD_MODELS)))
KICAD_SRC_DIR     = $(KICAD_DIR)/src
KICAD_SRC_FILES   = $(addsuffix .cpp, $(addprefix $(KICAD_SRC_DIR)/, $(KICAD_MODELS)))
KICAD_OBJS        = $(foreach obj, $(KICAD_SRC_FILES), $(BUILD_DIR)/$(notdir $(obj)).o)
KICAD_DEPS        = $(KICAD_OBJS:.o=.d)
SRC_DIRS         += $(KICAD_SRC_DIR)

# DigiSim library
DIGISIM_SRC_DIR   = src
DIGISIM_SRC_FILES = $(wildcard $(DIGISIM_SRC_DIR)/*.cpp)
DIGISIM_OBJS      = $(KICAD_OBJS)
DIGISIM_OBJS     += $(foreach obj, $(DIGISIM_SRC_FILES), $(BUILD_DIR)/$(notdir $(obj)).o)
DIGISIM_DEPS      = $(DIGISIM_OBJS:.o=.d)
DIGISIM_LIB       = $(LIB_DIR)/libDIGISIM.a
SRC_DIRS         += $(DIGISIM_SRC_DIR)


#################
# RULES SECTION #
#################

all: build_dir $(NET2SIM_BIN) $(KICAD_H_FILES) $(KICAD_SRC_FILES) $(DIGISIM_LIB)

# include the dependency files
-include $(NET2SIM_DEPS) $(KICAD_DEPS) $(DIGISIM_DEPS)

# Rule to create build directory
.PHONY: build_dir
build_dir :
	@echo "MKD  $(BUILD_DIR)"
	@mkdir -p $(BUILD_DIR)

# Compile rules
define compileRules
$(BUILD_DIR)/%.cpp.o : $(1)/%.cpp
	@echo "C++  $$(notdir $$<)"
	$(HIDE) $$(CXX) $$(CXXFLAGS) $$(INCLUDES) -c -o $$@ $$< -MMD
endef
$(foreach srcdir, $(SRC_DIRS), $(eval $(call compileRules, $(srcdir))))

# Build rules for binaries
$(NET2SIM_BIN) : $(NET2SIM_OBJS)
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS) -o $@ $^

# Build rule for library
%.a : $(DIGISIM_OBJS)
	@echo "AR   $@"
	$(HIDE) $(AR) -rc $@ $^

# Build rules for kicad models
define modelBuildRule
$$(KICAD_H_DIR)/%.h : $$(KICAD_DIR)/$(strip $(1))/%.net
	@echo "NET  $$(notdir $$<)"
	$$(HIDE) $$(NET2SIM_BIN) -h $$(KICAD_H_DIR)/$(strip $(1)).h -c $$(KICAD_SRC_DIR)/$(strip $(1)).cpp  $$^
$$(KICAD_SRC_DIR)/%.cpp : $$(KICAD_DIR)/$(strip $(1))/%.net
	@echo "NET  $$(notdir $$<)"
	$$(HIDE) $$(NET2SIM_BIN) -h $$(KICAD_H_DIR)/$(strip $(1)).h -c $$(KICAD_SRC_DIR)/$(strip $(1)).cpp  $$^
endef
$(foreach model, $(KICAD_MODELS), $(eval $(call modelBuildRule, $(model))))

.PHONY: clean
clean:
	$(HIDE) rm -rf $(BUILD_DIR)
	$(HIDE) rm -f  $(NET2SIM_BIN) 
	$(HIDE) rm -f  $(KICAD_H_DIR)/*
	$(HIDE) rm -f  $(KICAD_SRC_DIR)/*
	$(HIDE) rm -f  $(DIGISIM_LIB)
