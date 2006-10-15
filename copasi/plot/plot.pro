######################################################################
# $Revision: 1.18 $ $Author: gauges $ $Date: 2006/10/15 06:25:23 $  
######################################################################

LIB = plot

include(../lib.pri)
include(../common.pri)

CONFIG += qt

HEADERS += CHistogram.h \
           plotwidget1.h \
           CopasiPlot.h \
           COutputHandlerPlot.h \
           CPlotItem.h \
           CPlotSpecification.h \
           COutputDefinitionVector.h \
           plotwindow.h \
           scrollbar.h \
           scrollzoomer.h

SOURCES += CHistogram.cpp \
           CopasiPlot.cpp \
           plotwidget1.cpp \
           plotwindow.cpp \
           COutputHandlerPlot.cpp \
           CPlotItem.cpp \
           CPlotSpecification.cpp \
           COutputDefinitionVector.cpp \
           scrollbar.cpp \
           scrollzoomer.cpp

FORMS +=  curve2dwidget.ui
FORMS +=  HistoWidget.ui

HEADERS += curve2dwidget.ui.h
HEADERS +=  HistoWidget.ui.h

INCLUDEPATH += $${QWT_PATH}/include


contains(BUILD_OS, Linux){
    GUIOBJECTS += COutputHandlerPlot.o
    GUIOBJECTS += CopasiPlot.o
    GUIOBJECTS += HistoWidget.o
    GUIOBJECTS += curve2dwidget.o
    GUIOBJECTS += plotwidget1.o
    GUIOBJECTS += plotwindow.o
    GUIOBJECTS += scrollbar.o
    GUIOBJECTS += scrollzoomer.o

    OBJECTS += CoutputDefinitionVector.o
    OBJECTS += CPlotItem.o
    OBJECTS += CPlotSpecification.o

    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)   
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASIGUI

    POST_TARGETDEPS += ../lib/libCOPASI.a
    POST_TARGETDEPS += ../lib/libCOPASIGUI.a
     
}

contains(BUILD_OS, Darwin){

    GUIOBJECTS += COutputHandlerPlot.o
    GUIOBJECTS += CopasiPlot.o
    GUIOBJECTS += HistoWidget.o
    GUIOBJECTS += curve2dwidget.o
    GUIOBJECTS += plotwidget1.o
    GUIOBJECTS += plotwindow.o
    GUIOBJECTS += scrollbar.o
    GUIOBJECTS += scrollzoomer.o

    OBJECTS += CoutputDefinitionVector.o
    OBJECTS += CPlotItem.o
    OBJECTS += CPlotSpecification.o


    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $$OBJECTS $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $$OBJECTS  

    libCOPASIGUI.target   = ../lib/libCOPASIGUI.a
    libCOPASIGUI.depends  = $$GUIOBJECTS $(OBJCOMP)
    libCOPASIGUI.commands = ar crs $@ $$GUIOBJECTS $(GUIOBJCOMP)  
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASIGUI

    POST_TARGETDEPS += ../lib/libCOPASI.a
    POST_TARGETDEPS += ../lib/libCOPASIGUI.a
        
}   


DISTFILES += plot.dsp
DISTFILES += QwtLicense
