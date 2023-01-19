.SUFFIXES: .cpp .obj .exe

L       = LEDA
OPTS    = -nologo -MT
SYSLIBS = user32.lib gdi32.lib msimg32.lib comdlg32.lib shell32.lib advapi32.lib wsock32.lib

.cpp.exe:
	cl $(OPTS) -I $L/incl $*.cpp $L/leda.lib $(SYSLIBS)


all: gw_gabriel1.exe gw_caterpillar.exe

clean: 
	del *.obj *.exe

