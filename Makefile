
# Compiler options
CXX        =  g++  # oder clang++
CXXFLAGS   = -std=c++17 -g -Iinclude -Ikicad/include -Ofast

# Net2Sim variables
NET2SIM_DIR      = Net2Sim
NET2SIM_SRCS     = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS     = $(NET2SIM_SRCS:%.cpp=%.o)
NET2SIM_BIN      = $(NET2SIM_DIR)/Net2Sim

# KiCad model variables
KICAD_NET_FILES  = $(wildcard kicad/*/*.net)
KICAD_MODELS     = $(notdir $(KICAD_NET_FILES:.net=))
KICAD_H_FILES    = $(addsuffix .h,   $(addprefix kicad/include/, $(KICAD_MODELS)))
KICAD_CPP_FILES  = $(wildcard kicad/src/*.cpp)
KICAD_CPP_FILES += $(subst include/,src/, $(subst .h,.cpp, $(KICAD_H_FILES)))

# DigiSim variables
DIGISIM_DIR   = src
DIGISIM_SRCS  = $(wildcard $(DIGISIM_DIR)/*.cpp) $(KICAD_CPP_FILES)
DIGISIM_OBJS  = $(DIGISIM_SRCS:%.cpp=%.o)
DIGISIM_BIN   = bin/main


all:	$(NET2SIM_BIN) $(KICAD_H_FILES) $(DIGISIM_BIN)

# Build rules for binaries and libraries
$(NET2SIM_BIN):$(NET2SIM_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(DIGISIM_BIN):$(DIGISIM_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build rules for kicad models
define modelBuildRule
kicad/include/%.h : $(1)/%.net
	$(NET2SIM_BIN) -c $$(subst .h,.cpp,$$(subst include,src,$$@)) -h $$@ $$^
kicad/src/%.cpp : kicad/$(strip $(1))/%.net
	$(NET2SIM_BIN) -c $$@ -h $$(subst .cpp,.h,$$(subst src,include,$$@)) $$^
endef
$(foreach model, $(KICAD_MODELS), $(eval $(call modelBuildRule, kicad/$(model))))

clean:
	rm -f $(NET2SIM_OBJS) $(NET2SIM_BIN) $(KICAD_H_FILES) $(DIGISIM_OBJS) $(DIGISIM_BIN) *~

