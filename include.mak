all: 	$(PRG)

OBJS	= $(OBJDIR)/CGlobals.o \
	  $(OBJDIR)/CCopasiException.o \
	  $(OBJDIR)/CCopasiMessage.o \
          $(OBJDIR)/CVersion.o
	  $(OBJDIR)/CReadConfig.o \
	  $(OBJDIR)/CWriteConfig.o \
	  $(OBJDIR)/CBaseIdentifier.o \
	  $(OBJDIR)/CBaseFunction.o \
	  $(OBJDIR)/CCompartment.o \
          $(OBJDIR)/CMetab.o \
	  $(OBJDIR)/CNodeK.o \
	  $(OBJDIR)/CKinFunction.o \
	  $(OBJDIR)/lexkk.o \
	  $(OBJDIR)/CMoiety.o \
	  $(OBJDIR)/CFunctionDB.o \
	  $(OBJDIR)/CStep.o \
	  $(OBJDIR)/utilities.o \
	  $(OBJDIR)/main.o



