#!/bin/bash

JUNITPATH=/usr/share/java/junit.jar
CLASSPATH=.:../copasi.jar:$JUNITPATH

javac -classpath $CLASSPATH -d . *.java
java -Djava.library.path=.. -classpath $CLASSPATH junit.textui.TestRunner org.COPASI.unittests.RunTests
