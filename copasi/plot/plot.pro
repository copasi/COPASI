SOURCES	+= \
	plotwidget1.cpp \
  curvegroupbox.cpp \
  doublerect.cpp \
  zoomplot.cpp \
	CopasiPlot.cpp \
  plotwindow.cpp \
	main.cpp

HEADERS	+= plotwidget1.h \
	crvspecscrlview.h \
  curvegroupbox.h \
  doublerect.h \
  zoomplot.h \
	CopasiPlot.h \
	plotspec.h \
	plotwindow.h

TARGET       = copasiplot
MOC_DIR      = moc
OBJECTS_DIR  = obj
DEPENDPATH   = ../include


linux-g++:TMAKE_CXXFLAGS += -fno-exceptions 


#FORMS	= plotwidget1.ui
#FORMS	= curvegroupbox.ui
TEMPLATE	=app
CONFIG	+= qt warn_on debug release thread
INCLUDEPATH	+= ../include
unix:LIBS	+= -lqwt
LANGUAGE	= C++
