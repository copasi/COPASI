/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/COutputDefinitionVector.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/18 09:13:16 $
   End CVS Header */

#if !defined OUTPUTSPECIFICATION_VECTOR
#define OUTPUTSPECIFICATION_VECTOR

#include "CPlotSpecification.h"
#include "utilities/CCopasiVector.h"

class COutputDefinitionVector : public CCopasiVectorN<CPlotSpecification>
  {
  private:
    std::string mKey;

  public:
    COutputDefinitionVector(const std::string & name = "OutputDefinitions",
                            const CCopasiContainer* pParent = &RootContainer);

    ~COutputDefinitionVector();

    CPlotSpecification* createPlotSpec(const std::string & name,
                                       CPlotItem::Type type = CPlotItem::plot2d);
    bool removePlotSpec(const std::string & key);

    void cleanup();

    const std::string& getKey();
  };

#endif
