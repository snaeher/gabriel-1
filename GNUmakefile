.SUFFIXES: .cpp .o .

PROGS = gw_gabriel1 gw_caterpillar1
OBJECTS = mwg_drawing.o


sys = $(shell leda.sys)

L       = $(LEDA)/LINK/$(sys)/g++
OPTS    = -O2 -fno-strict-aliasing
SYSLIBS = -lX11 -lXft

.cpp.o: 
	g++ $(OPTS) -I $L/incl -c $*.cpp 

.cpp:
	g++ $(OPTS) -I $L/incl $*.cpp -o $* $L/libleda.a $(OBJECTS) $(SYSLIBS)

all: $(OBJECTS) $(PROGS)


clean: 
	rm -f *.o $(PROGS)

