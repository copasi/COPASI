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
#	doc/html/index.html

OBJS	= $(OBJDIR)/CCompartment.o \
	  $(OBJDIR)/CCopasiException.o \
	  $(OBJDIR)/CCopasiMessage.o \
	  $(OBJDIR)/CDatum.o \
	  $(OBJDIR)/CKinetics.o \
	  $(OBJDIR)/CKinFunction.o \
	  $(OBJDIR)/CMetab.o \
	  $(OBJDIR)/CNodeK.o \
	  $(OBJDIR)/CReadConfig.o  \
	  $(OBJDIR)/CStep.o \
	  $(OBJDIR)/CWriteConfig.o  \
	  $(OBJDIR)/globals.o  \
	  $(OBJDIR)/lexkk.o  \
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




