/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec2Vector.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:09:48 $
   End CVS Header */

#if !defined PLOTSPECIFICATION_VECTOR
#define PLOTSPECIFICATION_VECTOR

#include <iostream>
#include <string>
#include "utilities/CCopasiVector.h"
#include "CPlotSpecification.h"
#include "utilities/CopasiTime.h"

class PlotWindow;

class CPlotSpec2Vector: public CCopasiVectorN<CPlotSpecification>
  {
  private:
    std::string mKey;

    std::vector<CCopasiObjectName> mObjectNames;
    std::vector<CCopasiObject*> mObjects;

    std::vector<C_FLOAT64> data;

    enum inputType {NO_INPUT, FROM_STREAM, FROM_OBJECTS};
    inputType inputFlag;

    //this maps the key of a plot spec to a plot window
    std::map<std::string, PlotWindow*> windowMap;

    //this is a list of active windows for a specific run
    std::vector<PlotWindow*> windows;

    CCopasiTimeVariable mTime;

    bool initAllPlots();
    bool sendDataToAllPlots();
    bool updateAllPlots();

    //this generates mObjects from mObjectNames
    bool compile();

  public:
    CPlotSpec2Vector(const std::string & name = "PlotSpecifications",
                     const CCopasiContainer* pParent = &RootContainer);

    ~CPlotSpec2Vector();

    CPlotSpecification* createPlotSpec(const std::string & name,
                                       CPlotItem::Type type = CPlotItem::plot2d);
    bool removePlotSpec(const std::string & key);

    //look up on which column in the data stream a specific object is
    //also adds the object to the data stream if necessary
    C_INT32 getIndexFromCN(const CCopasiObjectName & name);

    bool initPlottingFromObjects();
    bool doPlotting();
    bool finishPlotting();

    bool doPlottingSeparator();

    void cleanup();

    const std::string& getKey();
  };

#endif
