all: 	$(PRG)

OBJS	= \
          $(OBJDIR)/CBaseFunction.o \
          $(OBJDIR)/CBaseIdentifier.o \
          $(OBJDIR)/CCompartment.o \
          $(OBJDIR)/CCopasiException.o \
          $(OBJDIR)/CCopasiMessage.o \
          $(OBJDIR)/CFunctionDB.o \
          $(OBJDIR)/CGlobals.o \
          $(OBJDIR)/CKinFunction.o \
          $(OBJDIR)/CMassAction.o \
          $(OBJDIR)/CMetab.o \
          $(OBJDIR)/CModel.o \
          $(OBJDIR)/CMoiety.o \
          $(OBJDIR)/CNodeK.o \
          $(OBJDIR)/CODESolver.o \
          $(OBJDIR)/CReadConfig.o \
          $(OBJDIR)/CStep.o \
          $(OBJDIR)/CTrajectory.o \
          $(OBJDIR)/CNewton.o \
          $(OBJDIR)/CSS_Solution.o \
          $(OBJDIR)/CVersion.o \
          $(OBJDIR)/CWriteConfig.o \
          $(OBJDIR)/Clsoda.o \
          $(OBJDIR)/lexkk.o \
          $(OBJDIR)/main.o \
          $(OBJDIR)/utilities.o
