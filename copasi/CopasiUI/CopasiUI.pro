######################################################################
# $Revision: 1.1 $ $Author: shoops $ $Date: 2003/05/19 12:45:54 $  
######################################################################

include(../common.pri)

TEMPLATE = app

DEPENDPATH += .. 
INCLUDEPATH += ..

# The order of libs is important 
tmpLIBS = $${LIBS}
LIBS = -L../lib \
       -Wl,-lelementaryFluxModes \
       -Wl,-lcopasiXML \
       -Wl,-lmathmodel \
       -Wl,-lmodel \
       -Wl,-lfunction \
       -Wl,-loutput \
       -Wl,-lreport \
       -Wl,-loptimization \
       -Wl,-lscan \
       -Wl,-lsteadystate \
       -Wl,-ltrajectory \
       -Wl,-lrandomGenerator \
       -Wl,-lutilities \
       -Wl,-loutput \
       -Wl,-lfunction \
       -Wl,-lmodel
LIBS += $${tmpLIBS}

# Input
HEADERS += CompartmentsWidget.h \
           CompartmentsWidget1.h \
           CompartmentSymbols.h \
           ConstantSymbols.h \
           copasiui3window.h \
           copasiWidget.h \
           CReactionInterface.h \
           DataModel.h \
           DifferentialEquations.h \
           FixedMetaboliteSymbols.h \
           FunctionSymbols.h \
           FunctionWidget.h \
           FunctionWidget1.h \
           listviews.h \
           MetabolitesWidget.h \
           MetabolitesWidget1.h \
           MetaboliteSymbols.h \
           ModelWidget.h \
           ModesWidget.h \
           MoietiesWidget.h \
           MoietyWidget.h \
           MoietyWidget1.h \
           MyLineEdit.h \
           MyTable.h \
           ObjectBrowser.h \
           ObjectBrowserItem.h \
           objectdebug.h \
           objectdebug.ui.h \
           Observer.h \
           parametertable.h \
           ReactionsWidget.h \
           ReactionsWidget1.h \
           ScanWidget.h \
           SteadyStateWidget.h \
           StretchTable.h \
           Subject.h \
           TrajectoryWidget.h \
           Tree.h

# INTERFACES += CompartmentsWidget.ui \
#               FunctionWidget1.ui \
#               MetabolitesWidget1.ui \
#               MoietyWidget1.ui \
#               ObjectBrowser.ui \
#               objectdebug.ui \
#               ReactionsWidget1.ui \
#               SteadyStateWidget.ui \
#               TrajectoryWidget.ui

SOURCES += CompartmentsWidget.cpp \
           CompartmentsWidget1.cpp \
           CompartmentSymbols.cpp \
           ConstantSymbols.cpp \
           copasiui3window.cpp \
           copasiWidget.cpp \
           CReactionInterface.cpp \
           DifferentialEquations.cpp \
           FixedMetaboliteSymbols.cpp \
           FunctionSymbols.cpp \
           FunctionWidget.cpp \
           FunctionWidget1.cpp \
           listviews.cpp \
           main.cpp \
           MetabolitesWidget.cpp \
           MetabolitesWidget1.cpp \
           MetaboliteSymbols.cpp \
           ModelWidget.cpp \
           ModesWidget.cpp \
           MoietiesWidget.cpp \
           MoietyWidget.cpp \
           MoietyWidget1.cpp \
           MyLineEdit.cpp \
           MyTable.cpp \
           ObjectBrowser.cpp \
           ObjectBrowserItem.cpp \
           objectdebug.cpp \
           Observer.cpp \
           parametertable.cpp \
           ReactionsWidget.cpp \
           ReactionsWidget1.cpp \
           ScanWidget.cpp \
           SteadyStateWidget.cpp \
           StretchTable.cpp \
           Subject.cpp \
           TrajectoryWidget.cpp

