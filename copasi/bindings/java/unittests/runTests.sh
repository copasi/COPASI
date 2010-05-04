#!/bin/bash

JUNITPATH=/usr/share/java/junit.jar
CLASSPATH=.:../copasi.jar:$JUNITPATH

javac -g -classpath $CLASSPATH -d . *.java
java -d32 -Djava.library.path=.. -classpath $CLASSPATH junit.textui.TestRunner org.COPASI.unittests.RunTests
