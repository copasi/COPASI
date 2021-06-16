# Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the 
# University of Virginia, University of Heidelberg, and University 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and University of 
# of Connecticut School of Medicine. 
# All rights reserved. 

# Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

###############################################################################
#
# Description       : CMake build script for COPASI
# Original author(s): Ralph Gauges <ralph.gauges@bioquant.uni-heidelberg.de>
#                     Frank Bergmann <fbergman@caltech.edu>
#
# This file is part of COPASI.  Please visit http://COPASI.org for more
# information about COPASI, and the latest version of COPASI.
#
# 
# 
#
###############################################################################


SET(FORMS_BARCHART
)
SET(HEADERS_BARCHART

)
SET(SOURCES_BARCHART
)

if (QT5_USE_DATAVISUALIZATION)
SET(FORMS_BARCHART ${FORMS_BARCHART}

)
SET(HEADERS_BARCHART ${HEADERS_BARCHART}
barChart/CQ3DBarsModifier.h
)
SET(SOURCES_BARCHART ${SOURCES_BARCHART}
barChart/CQ3DBarsModifier.cpp
)

else()
SET(FORMS_BARCHART ${FORMS_BARCHART}
barChart/CQBaseWidget.ui
)
SET(HEADERS_BARCHART ${HEADERS_BARCHART}
barChart/qwt3dBars.h
barChart/qwt3dColor.h
barChart/qwt3dPlot.h
barChart/qwt3dScale.h
barChart/CQBaseWidget.h
)
SET(SOURCES_BARCHART ${SOURCES_BARCHART}
barChart/qwt3dBars.cpp
barChart/qwt3dColor.cpp
barChart/qwt3dPlot.cpp
barChart/qwt3dScale.cpp
barChart/CQBaseWidget.cpp
)

endif()

# create source group for IDEs
source_group(barChart FILES ${FORMS_BARCHART} ${HEADERS_BARCHART} ${SOURCES_BARCHART})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_BARCHART})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_BARCHART})
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_BARCHART})
