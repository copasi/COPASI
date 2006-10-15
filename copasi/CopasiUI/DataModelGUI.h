/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModelGUI.h,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 06:57:33 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef DATAMODELGUI_H
#define DATAMODELGUI_H

#include <qobject.h>

#include "CopasiUI/Tree.h"
#include "plot/COutputHandlerPlot.h"

//class CMathModel;
class QTimer;

class DataModelGUI
  {
  private:
    IndexedTree mTree; // create the  object of the tree

    //CMathModel * mpMathModel;
    //bool mMathModelUpdateScheduled;

    QApplication *mpApp;

    void linkDataModelToGUI();

    COutputHandlerPlot mOutputHandlerPlot;

  public:
    DataModelGUI();

    void populateData();

    void updateCompartments();
    void updateMetabolites();
    void updateReactions();
    void updateModelValues();
    void updateMoieties();
    void updateFunctions();
    void updateReportDefinitions();
    void updatePlots();

    const IndexedNode * getRootNode() const;
    const IndexedNode * getNode(const int & id) const;

    bool loadModel(const std::string & fileName);
    bool createModel();
    bool saveModel(const std::string & fileName, bool overwriteFile = false);

    bool importSBML(const std::string & fileName);
    bool exportSBML(const std::string & fileName, bool overwriteFile , int sbmlLevel, int sbmlVersion, bool exportIncomplete);
    bool exportMathModel(const std::string & fileName, const std::string & filter, bool overwriteFile = false);

    COutputDefinitionVector & getPlotDefinitionList();

    //CMathModel * getMathModel() {return mpMathModel;}
    //bool updateMathModel();
    //bool scheduleMathModelUpdate(const bool & update = true);

    void setQApp(QApplication* app);
    QApplication* getQApp() const;
  };

#endif
