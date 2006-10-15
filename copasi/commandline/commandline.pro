######################################################################
# $Revision: 1.10 $ $Author: gauges $ $Date: 2006/10/15 06:25:19 $  
######################################################################

LIB = commandline

include(../lib.pri)
include(../common.pri)

#Input
HEADERS += CConfigurationFile.h \
           COptionParser.h \
           COptions.h

SOURCES += CConfigurationFile.cpp \
           COptionParser.cpp \
           COptions.cpp

contains(BUILD_PARSER, yes) {
  CLOPP = $$system(which clo++)
  count(CLOPP, 1) {
    1.target = COptionParser.cpp
    1.depends = COptionParser.xml
    1.commands = \
          rm $@ $*.h; \
          clo++ -o c++ $< && \
          cat $@ | \
          sed -e 's/compare([^,]*,[^,]*, *\([^,]*\) *,[^)]*)/compare(\1)/g' \
              > $@.tmp && \
          mv $@.tmp $@; \
          ../../cvs_admin/c++style $@; \
          ../../cvs_admin/c++style $*.h
        
    QMAKE_EXTRA_UNIX_TARGETS += 1
  }
}

contains(BUILD_OS, Linux){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)   
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
     
}

contains(BUILD_OS, Darwin){
    libCOPASI.target   = ../lib/libCOPASI.a
    libCOPASI.depends  = $(OBJECTS) $(OBJCOMP)
    libCOPASI.commands = ar crs $@ $(OBJECTS) $(OBJCOMP)  
    
    QMAKE_EXTRA_UNIX_TARGETS += libCOPASI

    POST_TARGETDEPS += ../lib/libCOPASI.a
        
}   

DISTFILES += \
             commandline.dsp \
             COptionParser.xml
