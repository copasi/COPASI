/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:47 $
   End CVS Header */

#ifndef DATAMODELGUI_H
#define DATAMODELGUI_H

#include <qobject.h>

#include "DataModel.h"

#include "Tree.h"

class CMathModel;

class DataModelGUI : public DataModel
  {
  private:
    IndexedTree mTree; // create the  object of the tree

    CMathModel * mpMathModel;
    bool mMathModelUpdateScheduled;

    QApplication *mpApp;

    void linkDataModelToGUI();

  public:
    DataModelGUI();

    void populateData();

    void updateCompartments();
    void updateMetabolites();
    void updateReactions();
    void updateMoieties();
    void updateFunctions();
    void updateReportDefinitions();
    void updatePlots();

    const IndexedNode & getRootNode() const;

    void loadModel(const char* fileName);
    void createModel();
    void saveModel(const char* fileName);

    void importSBML(const char* fileName);
    void exportSBML(const char* fileName);

    CMathModel * getMathModel() {return mpMathModel;}
    bool updateMathModel();
    bool scheduleMathModelUpdate(const bool & update = true);

    void setQApp(QApplication* app);
    QApplication* getQApp() const;
  };

#endif
