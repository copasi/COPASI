####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = CopasiUI

CopasiUI_SOURCES = \
	main.cpp \
	MyTable.cpp \
	Observer.cpp \
	Subject.cpp \
	CompartmentsWidget.cpp 	moc_CompartmentsWidget1.cpp \
	CompartmentsWidget1.cpp	moc_CompartmentsWidget.cpp \
	MetabolitesWidget.cpp	moc_MetabolitesWidget.cpp \
	MetabolitesWidget1.cpp	moc_MetabolitesWidget1.cpp \
	MoietyWidget.cpp	moc_MoietyWidget.cpp \
	MoietyWidget1.cpp	moc_MoietyWidget1.cpp \
	ReactionsWidget.cpp	moc_ReactionsWidget.cpp \
	ReactionsWidget1.cpp	moc_ReactionsWidget1.cpp \
	copasiui3window.cpp	moc_copasiui3window.cpp \
	listviews.cpp		moc_listviews.cpp

EXTRA_DIST = \
	main.cpp \
	Tree.h \
	MyTable.h MyTable.cpp \
	Observer.h Observer.cpp \
	Subject.h Subject.cpp \
	CompartmentsWidget.h CompartmentsWidget.cpp moc_CompartmentsWidget1.cpp \
	CompartmentsWidget1.h CompartmentsWidget1.cpp moc_CompartmentsWidget.cpp \
	MetabolitesWidget.h MetabolitesWidget.cpp moc_MetabolitesWidget.cpp \
	MetabolitesWidget1.h MetabolitesWidget1.cpp moc_MetabolitesWidget1.cpp \
	MoietyWidget.h MoietyWidget.cpp moc_MoietyWidget.cpp \
	MoietyWidget1.h MoietyWidget1.cpp moc_MoietyWidget1.cpp \
	ReactionsWidget.h ReactionsWidget.cpp moc_ReactionsWidget.cpp \
	ReactionsWidget1.h ReactionsWidget1.cpp moc_ReactionsWidget1.cpp \
	copasiui3window.h copasiui3window.cpp moc_copasiui3window.cpp \
	listviews.h listviews.cpp moc_listviews.cpp

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = CopasiUI

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

# the library search path.
LIBS = $(LIB_QT) \
	-lelementaryFluxModes \
	-lmodel \
	-lfunction \
	-loutput \
	-lsteadystate \
	-ltrajectory \
	-lutilities \
	-loutput \
	-lfunction \
	-lmodel \
	-lmkl_lapack \
	-lmkl_p3 \
        -lg2c \
        -lpthread

#  Use this for standard clapack
#	-llapack \
#	-lblas \
#	-lF77 \
#	-lfl

#  Use this for the intel performance library under linux
#	-lmkl_lapack \
#	-lmkl_p3 \
#	-lg2c \
#	-lpthread \

# the library search path.
LDFLAGS = $(all_libraries) $(USER_LDFLAGS)\
	-L../elementaryFluxModes \
	-L../function \
	-L../model \
	-L../output \
	-L../steadystate \
	-L../trajectory \
	-L../utilities
