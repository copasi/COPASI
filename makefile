SHELL = /bin/sh

SRCDIR = ./src
OBJDIR = ./obj
INCDIR = ./include

CC	= gcc
CXX	= g++
CFLAGS = -g -I$(INCDIR) -DGCC 

LIBS        = -lnsl 


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

all: 	test doc/html/index.html

OBJS	= $(OBJDIR)/CCompartment.o \
	  $(OBJDIR)/CDatum.o \
	  $(OBJDIR)/CCopasiMessage.o \
	  $(OBJDIR)/CCopasiException.o \
	  $(OBJDIR)/CReadConfig.o  \
	  $(OBJDIR)/CWriteConfig.o  \
          $(OBJDIR)/main.o

test: 	dependencies $(OBJDIR) $(OBJS)
	$(CXX) $(CFLAGS) -o test $(OBJS)

dependencies: $(SRCDIR)/*.cpp $(INCDIR)/*.h
	@touch ./dependencies
	makedepend -f./dependencies -- $(CFLAGS) \
	-I/usr/lib/gcc-lib/i386-slackware-linux/egcs-2.91.66/include  \
	-I/usr/include/g++-2 -- $^
	@rm ./dependencies.bak

doc/html/index.html: $(INCDIR)/*.h
	doxygen test.dox

$(OBJDIR): 
	@test \( -d obj \) || mkdir $(OBJDIR)

clean:  
	rm -f test test.txt dependencies 
	rm -r -f Debug
	rm -r -f Release
	rm -r -f $(OBJDIR)

include ./dependencies




