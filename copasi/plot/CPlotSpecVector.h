/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpecVector.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/01/14 16:59:29 $
   End CVS Header */

#if !defined PLOTSPEC_VECTOR
#define PLOTSPEC_VECTOR

#include <iostream> 
//#include <vector>
#include <string>
#include "utilities/CCopasiVector.h" 
//#include "CPlotSpec.h"

class CPlotSpec;
class PlotWindow;

class CPlotSpecVector: public CCopasiVectorN<CPlotSpec>
  {
  private:
    std::string mKey;

    std::istream* pSource;
    C_INT32 ncols;

    std::vector<C_FLOAT64> data;
    std::streampos position;

    enum inputType {NO_INPUT, FROM_STREAM};
    inputType inputFlag;

    std::vector<PlotWindow*> windows;

    bool initAllPlots();
    bool sendDataToAllPlots();
    bool updateAllPlots();

  public:
    CPlotSpecVector(const std::string & name = "noname",
                    const CCopasiContainer* pParent = NULL);

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
