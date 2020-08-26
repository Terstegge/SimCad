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
# Location if DIGISIM library
DIGISIM_DIR     = ../..
NET2SIM_BIN     = $(DIGISIM_DIR)/bin/Net2Sim
DIGISIM_LIB_DIR = $(DIGISIM_DIR)/lib
DIGISIM_LIB     = $(DIGISIM_LIB_DIR)/libDIGISIM.a

# Compiler options
CXX        =  g++  # or clang++
CXXFLAGS   = -std=c++17 -g
INCLUDES   = -I$(DIGISIM_DIR)/include/core
INCLUDES  += -I$(DIGISIM_DIR)/include/gates
INCLUDES  += -I$(DIGISIM_DIR)/include/twopoles
INCLUDES  += -I$(DIGISIM_DIR)/include/kicad
INCLUDES  += -I$(DIGISIM_DIR)/kicad/include

SRCS       = R2R-Ladder-DAC.cpp main.cpp
OBJS       = $(SRCS:.cpp=.o)
BIN        = R2R-Ladder-DAC

# Utility to control output (detailed if VERBOSE defined).
ifdef VERBOSE
HIDE :=
else
HIDE := @
endif

all: $(BIN)

# include the dependency files
-include $(OBJS:.o=.d)

# Build rule for C++ compiler
%.o : %.cpp
	@echo "C++  $(notdir $<)"
	$(HIDE) $(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $< -MMD

# Build rules for binaries
$(BIN) : $(OBJS) $(DIGISIM_LIB_DIR)/libDIGISIM.a
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS) -L$(DIGISIM_LIB_DIR) -o $@ $^ -lDIGISIM

# Build rule for cpp and h files
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
	$(HIDE) rm -f *.o *.d
	$(HIDE) rm -f $(BIN)
	$(HIDE) rm -f R2R-Ladder-DAC.h R2R-Ladder-DAC.cpp
	
