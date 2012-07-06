
set(UI_LIBS libCOPASIUI )

link_directories(${CMAKE_BINARY_DIR}/copasi)

set(SE_LIBS  libCOPASI)
             #copasiDM
             #MIRIAM
             #commandline
             #compareExpressions
             #crosssection
             #elementaryFluxModes
             #function
             #layout
             #lna
             #lyap
             #math
             #model
             #moieties
             #odepack++
             #optimization
             #fitting
             #plot
             #randomGenerator
             #report
             #sbmlimport
             #sbmlunit
             #scan
             #sensitivities
             #steadystate
             #trajectory
             #tss
             #tssanalysis
             #utilities
             #copasiXML)

			 set(SE_DEPENDENCIES  libCOPASI)
# set(SE_DEPENDENCIES  CopasiDataModel
#                      MIRIAM
#                      commandline
#                      compareExpressions
#                      crosssection
#                      elementaryFluxModes
#                      function
#                      layout
#                      lna
#                      lyap
#                      math
#                      model
#                      moieties
#                      odepack++
#                      optimization
#                      parameterFitting
#                      plot
#                      randomGenerator
#                      report
#                      sbml
#                      sbmlunit
#                      scan
#                      sensitivities
#                      steadystate
#                      trajectory
#                      tss
#                      tssanalysis
#                      utilities
#                      xml)
