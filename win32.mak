PRG    = test.exe

LINK    = link.exe
CXX	= cl.exe

CFLAGS  =/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"tmp.pch" /YX /FD /GZ /I"$(INCDIR)" /c 

LINKFLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"tmp.pdb" /debug /machine:I386 /out:"tmp.exe" /pdbtype:sept 

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include

include include.mak

$(PRG):	$(OBJDIR) $(OBJS)
	$(LINK) $(LINKFLAGS) -o $(PRG) $(OBJS)

$(OBJDIR): 
	-mkdir $(OBJDIR)

{$(SRCDIR)}.cpp{$(OBJDIR)}.o:
	$(CXX) $(CFLAGS) /Fo"$@" $< 

DOC: doc/html/index.html

doc/html/index.html: $(INCDIR)/*.h test.dox
	doxygen test.dox

clean:  
	-del /f test
        -rmdir /s /q $(OBJDIR)
	-rmdir /s /q debug
#	-rmdir /s /q doc









