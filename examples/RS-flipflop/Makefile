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
NET2SIM_BIN     = $(DIGISIM_DIR)/Net2Sim/Net2Sim
DIGISIM_LIB     = $(DIGISIM_DIR)/libDIGISIM.a

# Compiler options
CXX        =  g++  # or clang++
CXXFLAGS   = -std=c++17 -g
INCLUDES   = -I$(DIGISIM_DIR)/include/core
INCLUDES  += -I$(DIGISIM_DIR)/include/gates
INCLUDES  += -I$(DIGISIM_DIR)/include/twopoles
INCLUDES  += -I$(DIGISIM_DIR)/include/kicad
INCLUDES  += -I$(DIGISIM_DIR)/kicad/include

SRCS       = RS-flipflop.cpp main.cpp
OBJS       = $(SRCS:.cpp=.o)
BIN        = RS-flipflop

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
$(BIN) : $(OBJS) $(DIGISIM_DIR)/libDIGISIM.a
	@echo "LD   $@"
	$(HIDE) $(CXX) $(CXXFLAGS) -L$(DIGISIM_DIR) -o $@ $^ -lDIGISIM

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
	$(HIDE) rm -f RS-flipflop.h RS-flipflop.cpp

	