# Begin CVS Header 
#   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $ 
#   $Revision: 1.12 $ 
#   $Name:  $ 
#   $Author: shoops $ 
#   $Date: 2010/02/03 17:59:26 $ 
# End CVS Header 

# Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual 
# Properties, Inc., University of Heidelberg, and The University 
# of Manchester. 
# All rights reserved. 

macx:debug {
    COPASI_LIBS_SE += commandline
#ifdef COPASI_LICENSE_COM
    contains(USE_LICENSE, COM) {
      COPASI_LIBS_SE += commercial
    }
#endif // COPASI_LICENSE_COM

    COPASI_LIBS_SE += compareExpressions
    COPASI_LIBS_SE += copasiDM
    COPASI_LIBS_SE += copasiXML
    COPASI_LIBS_SE += crosssection
    COPASI_LIBS_SE += elementaryFluxModes
    COPASI_LIBS_SE += fitting
    COPASI_LIBS_SE += function
    COPASI_LIBS_SE += layout
    COPASI_LIBS_SE += lna
    COPASI_LIBS_SE += lyap
    COPASI_LIBS_SE += MIRIAM
    COPASI_LIBS_SE += math
    COPASI_LIBS_SE += model
    COPASI_LIBS_SE += moieties
    COPASI_LIBS_SE += odepack++
    COPASI_LIBS_SE += optimization
    COPASI_LIBS_SE += plot
    COPASI_LIBS_SE += randomGenerator
    COPASI_LIBS_SE += report
    COPASI_LIBS_SE += sbmlimport
    COPASI_LIBS_SE += sbmlunit
    COPASI_LIBS_SE += scan
    COPASI_LIBS_SE += sensitivities
    COPASI_LIBS_SE += steadystate
    COPASI_LIBS_SE += trajectory
    COPASI_LIBS_SE += tss
    COPASI_LIBS_SE += tssanalysis
    COPASI_LIBS_SE += utilities
    
    contains(DEFINES, HAVE_MML) {
      COPASI_LIBS_UI += mml
    }

    COPASI_LIBS_UI += barChart
    COPASI_LIBS_UI += layoutUI
    COPASI_LIBS_UI += MIRIAMUI
    COPASI_LIBS_UI += plotUI
    COPASI_LIBS_UI += tex
    COPASI_LIBS_UI += UI
    COPASI_LIBS_UI += wizard
    
  } else {
    COPASI_LIBS_SE += COPASISE
    COPASI_LIBS_UI += COPASIUI
  }
