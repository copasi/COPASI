####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = CopasiUI

CopasiUI_SOURCES = \
	CompartmentsWidget.cpp \
	listviews.cpp \
	CompartmentsWidget1.cpp \
	main.cpp \
	MetabolitesWidget.cpp \
	moc_CompartmentsWidget.cpp \
	MetabolitesWidget1.cpp \
	moc_CompartmentsWidget1.cpp \
	moc_MetabolitesWidget.cpp \
	MoietyWidget.cpp \
	moc_MetabolitesWidget1.cpp \
	MoietyWidget1.cpp \
	MyTable.cpp \
	moc_MoietyWidget.cpp \
	Observer.cpp \
	moc_MoietyWidget1.cpp \
	ReactionsWidget.cpp \
	moc_ReactionsWidget.cpp \
	ReactionsWidget1.cpp \
	moc_ReactionsWidget1.cpp \
	Subject.cpp \
	moc_copasiui3window.cpp \
	copasiui3window.cpp \
	moc_listviews.cpp

# matrix_SOURCES = matrix.cpp

EXTRA_DIST = \
	CompartmentsWidget.h	CompartmentsWidget.cpp \
	Observer.h Observer.cpp \
	moc_MetabolitesWidget.cpp \
	CompartmentsWidget.h	CompartmentsWidget1.cpp \
	ReactionsWidget.h	ReactionsWidget.cpp \
	moc_MoietiesWidget.cpp \
	MetabolitesWidget.h	MetabolitesWidget.cpp \
	ReactionsWidget1.h	ReactionsWidget1.cpp \
	moc_MoietyWidget.cpp \
	MetabolitesWidget1.h	MetabolitesWidget1.cpp \
	Subject.h	Subject.cpp \
	moc_ReactionsWidget.cpp \
	MoietiesWidget.h		MoietiesWidget.cpp \
	copasiui3window.h	copasiui3window.cpp \
	moc_ReactionsWidget1.cpp \
	MoietyWidget.h 		MoietyWidget.cpp \
	listviews.h listviews.cpp \
	moc_copasiui3window.cpp \
	MoietyWidget1.h 		MoietyWidget1.cpp \
	main.cpp \
	moc_listviews.cpp \
	MyTable.h			MyTable.cpp \
	moc_CompartmentsWidget.cpp

####### kdevelop will overwrite this part!!! (end)############
bin_PROGRAMS = CopasiUI

# set the include path found by configure
INCLUDES= $(all_includes) -I$(top_srcdir)/copasi $(USER_INCLUDES)

# the library search path.
LIBS = \
	-lelementaryFluxModes \
	-lfunction \
	-lmodel \
	-loutput \
	-lsteadystate \
	-ltrajectory \
	-lutilities \
	-loutput \
	-lqt \
	-lqui \
	-lmkl_lapack \
	-lmkl_p3 \
	-lg2c \
	-lpthread \
	-lXft \
	-lfreetype \
	-lXrender \
	-lSM \
	-lICE \
	-lXinerama \
	-lXext \
	-lX11 \
	-lc

# the library search path.
LDFLAGS = -all-static \
	-L../elementaryFluxModes \
	-L../function \
	-L../model \
	-L../output \
	-L../steadystate \
	-L../trajectory \
	-L../utilities \
	-L/usr/X11R6/lib \
	-L$(QTDIR)/lib \
	$(USER_LDFLAGS)

LDADD = \
	../elementaryFluxModes/libelementaryFluxModes.a \
	../function/libfunction.a \
	../model/libmodel.a \
	../output/liboutput.a \
	../steadystate/libsteadystate.a \
	../trajectory/libtrajectory.a \
	../utilities/libutilities.a

#SUBDIRS = \
#        function \
#        output \
#        model \
#        steadystate \
#        trajectory \
#        utilities

#all-recursive install-data-recursive install-exec-recursive \
#installdirs-recursive install-recursive uninstall-recursive  \
#check-recursive installcheck-recursive info-recursive dvi-recursive: $(SUBDIRS)

#$(SUBDIRS): ../
#	@test -d $@ || ln -s ../$@ $@
