
LIB = sbmlimport
include(../lib.pri)

# Input
HEADERS += StdException.h \
           ConverterASTNode.h \
           SBMLImporter.h \
           SBMLExporter.h
           
           
           
SOURCES += StdException.cpp \
           ConverterASTNode.cpp \
           SBMLImporter.cpp \
           SBMLExporter.cpp


