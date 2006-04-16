/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CPlotSpec2Vector.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/16 17:43:46 $
   End CVS Header */

#if !defined PLOTSPECIFICATION_VECTOR
#define PLOTSPECIFICATION_VECTOR

#include <iostream>
#include <string> 
//#include "CPlotSpecification.h"
#include "utilities/CopasiTime.h"
#include "report/CCopasiObject.h"
#include "COutputDefinitionVector.h"

#ifdef XXXX

class PlotWindow;

class CPlotSpec2Vector : public CCopasiObject
  {
  private:
    //std::string mKey;

    std::vector<C_FLOAT64> data;

    //CCopasiVectorN<CPlotSpecification> * mpPlotDefinitionList;
    COutputDefinitionVector * mpPlotDefinitionList;

    enum inputType {NO_INPUT, FROM_STREAM, FROM_OBJECTS};
    inputType inputFlag;

    //this maps the key of a plot spec to a plot window
    std::map<std::string, PlotWindow*> mPlotMap;

    //this is a list of active windows for a specific run
    std::vector< PlotWindow * > mActivePlots;

    /**
     * List of plots generated prior to execution
     */
    std::vector< PlotWindow * > mHeaderPlots;

    /**
     * List of plots generated during to execution
     */
    std::vector< PlotWindow * > mBodyPlots;

    /**
     * List of plots generated after execution
     */
    std::vector< PlotWindow * > mFooterPlots;

    CCopasiTimeVariable mTime;

    bool initAllPlots();
    void sendDataToAllPlots();
    void updateAllPlots();
    void finishAllPlots();

  public:
    CPlotSpec2Vector(const std::string & name = "PlotSpecifications");

    //CPlotSpec2Vector();

    ~CPlotSpec2Vector();

    //    CPlotSpecification* createPlotSpec(const std::string & name,
    //                                       CPlotItem::Type type = CPlotItem::plot2d);
    //    bool removePlotSpec(const std::string & key);

    //look up on which column in the data stream a specific object is
    //also adds the object to the data stream if necessary
    // C_INT32 getIndexFromCN(const CCopasiObjectName & name);

    /**
     * compile the object list from name vector
     * @param std::vector< CCopasiContainer * > listOfContainer
     * (default: CCopasiContainer::EmptyList)
     * @return bool success
     */
    bool compile(std::vector< CCopasiContainer * > listOfContainer =
                   CCopasiContainer::EmptyList);

    void initPlotting();
    void doPlotting();
    void finishPlotting();

    void doSeparator();

    void cleanup();

    //const std::string& getKey();

    bool setPlotDefinitionList(COutputDefinitionVector * pPlotDefinitionList);
    CCopasiVectorN< CPlotSpecification > * getPlotDefinitionList();
  };
#endif // XXXX

#endif
