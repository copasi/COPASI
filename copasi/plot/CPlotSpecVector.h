/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpecVector.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/04/19 08:55:43 $
   End CVS Header */

#if !defined PLOTSPEC_VECTOR
#define PLOTSPEC_VECTOR

#include <iostream> 
//#include <vector>
#include <string>
#include "utilities/CCopasiVector.h"
#include "report/CReport.h" 
//#include "CPlotSpec.h"

#include "CPlotSpec.h"
;
class PlotWindow;

class CPlotSpecVector: public CCopasiVectorN<CPlotSpec>
  {
  private:
    std::string mKey;

    std::istream* pSource;
    C_INT32 ncols;

    CReport mReport;

    std::vector<C_FLOAT64> data;
    std::streampos position;

    enum inputType {NO_INPUT, FROM_STREAM};
    inputType inputFlag;

    std::vector<PlotWindow*> windows;

    bool initAllPlots();
    bool sendDataToAllPlots();
    bool updateAllPlots();

  public:
    CPlotSpecVector(const std::string & name = "PlotSpecs",
                    const CCopasiContainer* pParent = &RootContainer);

    ~CPlotSpecVector();

    //    const std::vector< CReportDefinition*>* getReportDefinitionsAddr();

    bool addNewPlotSpec(const std::string name /*, const std::string comment*/);

    void setSourceStream(std::istream* ps) {pSource = ps;};
    std::istream* getSourceStream() const {return pSource;};

    void setNumColumns(C_INT32 n) {ncols = n;};
    C_INT32 getNumColumns() const {return ncols;};

    bool initPlottingFromStream();
    bool doPlotting();

    void cleanup();

    const std::string& getKey();
  };

#endif
