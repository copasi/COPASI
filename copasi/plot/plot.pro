SOURCES	+= \
	plotwidget1.cpp \
  curvegroupbox.cpp \
  doublerect.cpp \
  zoomplot.cpp \
	CopasiPlot.cpp \
  plotwindow.cpp \
	main.cpp


LIB = plot
include(../lib.pri)
CONFIG += qt

HEADERS += plotwidget1.h \
           crvspecscrlview.h \
           curvegroupbox.h \
           doublerect.h \
           zoomplot.h \
           CopasiPlot.h \
           plotspec.h \
           plotwindow.h

SOURCES += CopasiPlot.cpp \
           curvegroupbox.cpp \
           doublerect.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           zoomplot.cpp \
