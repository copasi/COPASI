/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpecVector.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/27 10:37:56 $
   End CVS Header */

#if !defined PLOTSPEC_VECTOR
#define PLOTSPEC_VECTOR

#include <iostream> 
//#include <vector>
#include <string>
#include "utilities/CCopasiVector.h"
#include "report/CReport.h"
#include "report/CReportDefinition.h"

#include "CPlotSpec.h"

class PlotWindow;
class CModel;

class CPlotSpecVector: public CCopasiVectorN<CPlotSpec>
  {
  private:
    std::string mKey;

    std::istream* pSource;
    //C_INT32 ncols;

    CReport mReport;
    CReportDefinition mRepDef;

    std::vector<CCopasiObjectName> mObjectNames;
    std::vector<CCopasiObject*> mObjects;

    std::vector<C_FLOAT64> data;
    std::streampos position;

    enum inputType {NO_INPUT, FROM_STREAM, FROM_OBJECTS};
    inputType inputFlag;

    std::vector<PlotWindow*> windows;

    bool initAllPlots();
    bool sendDataToAllPlots();
    bool updateAllPlots();

    //this generates mObjects from mObjectNames
    bool compile();

    void createDebugReport();

  public:
    CPlotSpecVector(const std::string & name = "PlotSpecs",
                    const CCopasiContainer* pParent = &RootContainer);

    ~CPlotSpecVector();

    CPlotSpec* createPlotSpec(const std::string & name);
    bool removePlotSpec(const std::string & key);

    //look up on which column in the data stream a specific object is
    C_INT32 getIndexFromCN(const CCopasiObjectName & name);

    void setSourceStream(std::istream* ps) {pSource = ps;};
    std::istream* getSourceStream() const {return pSource;};

    //void setNumColumns(C_INT32 n) {ncols = n;};
    //C_INT32 getNumColumns() const {return ncols;};

    bool initPlottingFromObjects();
    bool doPlotting();
    bool finishPlotting();

    void cleanup();

    const std::string& getKey();
  };

#endif
