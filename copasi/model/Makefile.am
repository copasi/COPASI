####### kdevelop will overwrite this part!!! (begin)##########
noinst_LIBRARIES = libmodel.a

libmodel_a_SOURCES = \
	CCompartment.cpp \
	CMetab.cpp \
	CModel.cpp \
	CMoiety.cpp \
	CReaction.cpp \
	CChemEq.cpp \
	CChemEqElement.cpp \
	CScanInputFlexLexer.cpp \
	CSpecLine.cpp \
	CSpec2Model.cpp

EXTRA_DIST = \
	model.h \
	CCompartment.h	CCompartment.cpp \
	CMetab.h	CMetab.cpp \
	CModel.h	CModel.cpp \
	CMoiety.h	CMoiety.cpp \
	CReaction.h	CReaction.cpp \
	CChemEq.h	CChemEq.cpp \
	CChemEqElement.h	CChemEqElement.cpp \
	CSpecLine.h	CSpecLine.cpp \
	CScanInputFlexLexer.lpp	CScanInputFlexLexer.cpp \
	CSpec2Model.h	CSpec2Model.cpp

####### kdevelop will overwrite this part!!! (end)############

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

%.cpp: %.lpp
	$(LEX) -t $< | grep -v unistd.h > $@
