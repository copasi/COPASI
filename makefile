SHELL	= /bin/sh
PRG	= test.exe

CC	= gcc
CXX	= g++
CFLAGS	= -g -I$(INCDIR) -DGCC 

LIBS	= -lnsl 

SRCDIR	= ./src
OBJDIR	= ./o
INCDIR	= ./include

include include.mak

$(PRG):	dependencies $(OBJDIR) $(OBJS)
	$(CXX) $(CFLAGS) -o $(PRG) $(OBJS)

$(OBJDIR): 
	-mkdir $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

DOC: doc/html/index.html

doc/html/index.html: $(INCDIR)/*.h test.dox
	doxygen test.dox

dependencies:
	$(CC) -I./include -MM $(SRCDIR)/*.cpp | \
	sed -e 's?\(.*\)\.o:?$(OBJDIR)/\1.o:?' > ./dependencies

clean:  
	rm -f $(PRG) *.txt dependencies
	rm -rf debug release $(OBJDIR)
#	rm -rf doc 

include ./dependencies
