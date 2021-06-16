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

set(FORMS_LAYOUTUI)

set(HEADERS_LAYOUTUI 
  layoutUI/BezierCurve.h
  layoutUI/CArrow.h
  layoutUI/CCompartmentGraphNode.h
  layoutUI/CDataEntity.h
  layoutUI/CGraphCurve.h
  layoutUI/CGraphNode.h
  layoutUI/CLabel.h
  layoutUI/CQAutolayoutWizard.h
  layoutUI/CQCurrentValueTable.h
  layoutUI/CQLayoutThread.h
  layoutUI/CQPlayerControlWidget.h
  layoutUI/CQSpringLayoutParameterWindow.h
  layoutUI/CSimSummaryInfo.h
  layoutUI/CVisParameters.h


)
set(SOURCES_LAYOUTUI 
  layoutUI/BezierCurve.cpp
  layoutUI/CArrow.cpp
  layoutUI/CQAutolayoutWizard.cpp
  layoutUI/CCompartmentGraphNode.cpp
  layoutUI/CDataEntity.cpp
  layoutUI/CGraphCurve.cpp
  layoutUI/CGraphNode.cpp
  layoutUI/CLabel.cpp
  layoutUI/CQLayoutThread.cpp
  layoutUI/CQPlayerControlWidget.cpp
  layoutUI/CQSpringLayoutParameterWindow.cpp
  layoutUI/CSimSummaryInfo.cpp
  layoutUI/CVisParameters.cpp

)

if (${WITH_LEGACY_OPENGL})

set(FORMS_LAYOUTUI ${FORMS_LAYOUTUI}
   layoutUI/CQScreenshotDialog.ui
   layoutUI/FontChooser.ui
   layoutUI/NodeSizePanel.ui
   layoutUI/ParaPanel.ui
)


set(HEADERS_LAYOUTUI  ${HEADERS_LAYOUTUI}
  layoutUI/CQFontRenderer.h
  layoutUI/CQGLLayoutPainter.h
  layoutUI/CQGLLayoutViewer.h
  layoutUI/CQGLNetworkPainter.h
  layoutUI/CQGLViewport.h
  layoutUI/CQQtImageTexturizer.h
  layoutUI/CQScreenshotOptionsDialog.h
  layoutUI/FontChooser.h
  layoutUI/NodeSizePanel.h
  layoutUI/ParaPanel.h
  layoutUI/RGTextureSpec.h
  
  layoutUI/CQNewMainWindow.h
  layoutUI/CQLayoutMainWindow.h
)

set (SOURCES_LAYOUTUI  ${SOURCES_LAYOUTUI}
  layoutUI/CQQtImageTexturizer.cpp
  layoutUI/CQCurrentValueTable.cpp
  layoutUI/CQFontRenderer.cpp
  layoutUI/CQGLLayoutPainter.cpp
  layoutUI/CQGLLayoutViewer.cpp
  layoutUI/CQGLNetworkPainter.cpp
  layoutUI/CQGLViewport.cpp
  layoutUI/CQScreenshotOptionsDialog.cpp
  layoutUI/FontChooser.cpp
  layoutUI/NodeSizePanel.cpp
  layoutUI/ParaPanel.cpp
  layoutUI/RGTextureSpec.cpp
  layoutUI/CQLayoutMainWindow.cpp
  layoutUI/CQNewMainWindow.cpp
)

endif()


# create source group for IDEs
source_group(layoutUI FILES ${FORMS_LAYOUTUI} ${HEADERS_LAYOUTUI} ${SOURCES_LAYOUTUI})

# add files to main COPASI sources
set(COPASI_UI_SOURCES ${COPASI_UI_SOURCES} ${SOURCES_LAYOUTUI})
set(COPASI_UI_FORMS   ${COPASI_UI_FORMS}     ${FORMS_LAYOUTUI})
if (HEADERS_LAYOUTUI)
set(COPASI_UI_HEADERS ${COPASI_UI_HEADERS} ${HEADERS_LAYOUTUI})
endif()
