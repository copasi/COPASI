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

all: 	test \
	doc/html/index.html

OBJS	= $(OBJDIR)/CCompartment.o \
	  $(OBJDIR)/CDatum.o \
	  $(OBJDIR)/CCopasiMessage.o \
	  $(OBJDIR)/CCopasiException.o \
	  $(OBJDIR)/CMetab.o \
	  $(OBJDIR)/CReadConfig.o  \
	  $(OBJDIR)/CWriteConfig.o  \
	  $(OBJDIR)/globals.o  \
          $(OBJDIR)/main.o

test: 	dependencies $(OBJDIR) $(OBJS)
	$(CXX) $(CFLAGS) -o test $(OBJS)

dependencies: $(SRCDIR)/*.cpp
	$(CC) -I./include -MM $^ | sed -e 's?\(.*\)\.o:?$(OBJDIR)/\1.o:?' \
	> ./dependencies

doc/html/index.html: $(INCDIR)/*.h
	doxygen test.dox

$(OBJDIR): 
	@test \( -d obj \) || mkdir $(OBJDIR)

clean:  
	rm -f test *.txt dependencies
	rm -rf debug release $(OBJDIR)
#	rm -rf doc 

include ./dependencies




