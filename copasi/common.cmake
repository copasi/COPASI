# Copyright (C) 2012 - 2015 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 


set(UI_LIBS libCOPASIUI )

link_directories(${CMAKE_BINARY_DIR}/copasi)

set(SE_LIBS  libCOPASISE-static)
set(SE_DEPENDENCIES  libCOPASISE-static)
