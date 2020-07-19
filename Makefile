
CXX        = g++  # oder clang++
CXXFLAGS   = -std=c++11

NET2SIM_DIR   = Net2Sim
NET2SIM_SRCS  = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS  = $(NET2SIM_SRCS:%.cpp=%.o)
NET2SIM_BIN   = bin/Net2Sim

KICAD_MODELS  = D-LATCH _74LS74 _74LS283
KICAD_H_FILES = $(addsuffix .h, $(addprefix include/, $(KICAD_MODELS)))
 

all:	$(NET2SIM_BIN) $(KICAD_H_FILES)

$(NET2SIM_BIN):$(NET2SIM_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.h:
	$(NET2SIM_BIN) -i kicad/$(notdir $(basename $@))/$(notdir $(basename $@)).net -o $@

clean:
	rm -f $(NET2SIM_OBJS) $(NET2SIM_BIN) $(KICAD_H_FILES) *~

