TEMPLATE = subdirs

include(../common.pri)

contains(ENABLE_JAVA,yes){
SUBDIRS += java
}

contains(ENABLE_PYTHON,yes){
SUBDIRS += python
}
