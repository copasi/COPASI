/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/CPlotSpecification.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:00 $
   End CVS Header */

/**
 *  
 */

#ifndef COPASI_PLOT_SPECIFICATION
#define COPASI_PLOT_SPECIFICATION

#include <string>

#include "CPlotItem.h"
#include "utilities/CCopasiVector.h"

class CModel;

class CPlotSpecification : public CPlotItem
  {
  private:

    CCopasiVector<CPlotItem> items;
    bool mActive;

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

    void setActive(bool act) {mActive = act;}
    bool isActive() const {return mActive;}
  };

#endif
