.SUFFIXES: .cpp .o .

PROGS : gw_gabriel1 gw_caterpillar


sys = $(shell leda.sys)

L       = $(LEDA)/LINK/$(sys)/g++
OPTS    = -O2 -fno-strict-aliasing
SYSLIBS = -lX11 -lXft

.cpp:
	g++ $(OPTS) -I $L/incl $*.cpp -o $* $L/libleda.a $(SYSLIBS)

all: gw_gabriel1 gw_caterpillar


clean: 
	rm -f *.o gw_gabriel1 gw_caterpillar

