
CXX        = g++  # oder clang++
CXXFLAGS   = -std=c++11

NET2SIM_DIR  = Net2Sim/src
NET2SIM_SRCS = $(wildcard $(NET2SIM_DIR)/*.cpp)
NET2SIM_OBJS = $(NET2SIM_SRCS:%.cpp=%.o)
NET2SIM_BIN  = bin/Net2Sim

all:	$(NET2SIM_BIN)

$(NET2SIM_BIN):$(NET2SIM_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f bin/* *~ $(NET2SIM_OBJS)

