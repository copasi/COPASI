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

all: 	test 

OBJS	= $(OBJDIR)/CCompartment.o \
	  $(OBJDIR)/CReadConfig.o  \
	  $(OBJDIR)/CDatum.o \
          $(OBJDIR)/main.o

test: 	dependencies mkdir $(OBJS)
	$(CXX) $(CFLAGS) -o test $(OBJS)

SRCS =  $(SRCDIR)/main.cpp \
	$(SRCDIR)/CCompartment.cpp \
        $(SRCDIR)/CDatum.cpp \
	$(SRCDIR)/CReadConfig.cpp

dependencies: $(SRCS) $(INCDIR)/*.h
	@touch ./dependencies
	makedepend -f./dependencies -- $(CFLAGS) \
	-I/usr/lib/gcc-lib/i386-slackware-linux/egcs-2.91.66/include  \
	-I/usr/include/g++-2 -- $^
	@rm ./dependencies.bak

mkdir:  
	@test \( -d obj \) || mkdir $(OBJDIR)

clean:  
	rm -f test test.txt dependencies 
	rm -r -f Debug
	rm -r -f Release
	rm -r -f $(OBJDIR)

include ./dependencies




