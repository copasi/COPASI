/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModel.h,v $
   $Revision: 1.52 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:30 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/DataModel.h                 Modified on : 28th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef DATAMODEL_H
#define DATAMODEL_H

#include "copasi.h"

class CReadConfig;

class CModel;
class CSteadyStateTask;
class CTrajectoryTask;
class CScanTask;
class CReportDefinitionVector;
class CPlotSpecVector;
class COptFunction;

//******************************************************************************

class DataModel
  {
  protected:
    CModel * model;
    bool mChanged;

    CSteadyStateTask* steadystatetask;
    CTrajectoryTask* trajectorytask;
    CScanTask* scantask;
    CReportDefinitionVector* reportdefinitions;
    CPlotSpecVector* plotspecs;
    COptFunction* pOptFunction;

  public:
    DataModel();

    void loadModel(const char* fileName);
    void createModel();
    void saveModel(const char* fileName);

    void importSBML(const char* fileName);
    void exportSBML(const char* fileName);

    CModel* getModel() {return model;}

    bool isChanged() const;
    void changed(const bool & changed = true);

    inline CSteadyStateTask* getSteadyStateTask() {return steadystatetask;}
    inline CTrajectoryTask* getTrajectoryTask() {return trajectorytask;}
    inline CReportDefinitionVector* getReportDefinitionVectorAddr(){return reportdefinitions;}
    inline CPlotSpecVector* getPlotSpecVectorAddr(){return plotspecs;}
  };

#endif
