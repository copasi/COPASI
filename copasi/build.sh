#!/bin/bash

find . -name Makefile -exec rm {} \;
qmake $@

