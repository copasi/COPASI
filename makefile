SHELL	= /bin/sh
PRG	= test

CC	= gcc
CXX	= g++
CFLAGS	= -g $(INCDIR) -I. -DGCC 

LIBS	= -lnsl 

SRCDIR	= ./src
OBJDIR	= ./o
INCDIRS = ./include ./include/Model ./include/Function
INCDIR	= -I./include -I./include/Model -I./include/Function

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
	$(CC) $(INCDIR) -I. -MM $(SRCDIR)/*.cpp | \
	sed -e 's?\(.*\)\.o:?$(OBJDIR)/\1.o:?' > ./dependencies

clean:  
	rm -f $(PRG) *.txt dependencies
	rm -rf debug release $(OBJDIR)
#	rm -rf doc 

include ./dependencies
