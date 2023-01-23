.SUFFIXES: .cpp .obj .exe

PROGS = gw_gabriel1.exe gw_caterpillar1.exe
OBJECTS = mwg_drawing.obj

L     = LEDA

#OPTS = -nologo -MT -DWINMAIN
OPTS  = -nologo -MT

SYSLIBS = user32.lib gdi32.lib msimg32.lib comdlg32.lib shell32.lib advapi32.lib wsock32.lib

.cpp.obj: 
	cl $(OPTS) -I $L/incl -c $*.cpp 

.cpp.exe:
        cl $(OPTS) -I $L/incl $*.cpp $(OBJECTS) $L/leda.lib $(SYSLIBS)


all: $(OBJECTS) $(PROGS)

$(PROGS): $(OBJECTS)

clean: 
	del *.obj *.exe

