/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/05 12:54:12 $
   End CVS Header */

/**
 *  
 */

#ifndef COPASI_PLOT_SPECIFICATION
#define COPASI_PLOT_SPECIFICATION

#include <string>

//#include "utilities/CCopasiParameterGroup.h"
#include "CPlotItem.h" 
//#include "report/CCopasiObjectName.h"
#include "utilities/CCopasiVector.h"

class CModel;

class CPlotSpecification : public CPlotItem
  {
  private:

    CCopasiVector<CPlotItem> items;

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

  public:
    CPlotSpecification(const std::string & name = "NoName",
                       const CCopasiContainer * pParent = NULL,
                       const CPlotItem::Type & type = plot2d);

    CPlotSpecification(const CPlotSpecification & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CPlotSpecification();

    virtual void cleanup();

    const CCopasiVector<CPlotItem> & getItems() const {return items;};

    CPlotItem* createItem(const std::string & name, CPlotItem::Type type);

    bool createDefaultPlot(const CModel* model);
  };

#endif
