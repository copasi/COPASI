// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *
 */

#ifndef COPASI_PLOT_SPECIFICATION
#define COPASI_PLOT_SPECIFICATION

#include <string>

#include "plot/CPlotItem.h"
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

protected:
  CPlotSpecification(const CPlotSpecification & src);

public:
  CPlotSpecification(const std::string & name = "NoName",
                     const CCopasiContainer * pParent = NO_PARENT,
                     const CPlotItem::Type & type = plot2d);

  CPlotSpecification(const CPlotSpecification & src,
                     const CCopasiContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CPlotSpecification();

  virtual void cleanup();

  const CCopasiVector<CPlotItem> & getItems() const {return items;};

  CCopasiVector<CPlotItem> & getItems() {return items;};

  CPlotItem* createItem(const std::string & name, CPlotItem::Type type);

  bool createDefaultPlot(const CModel* model);

  void setActive(const bool & active);

  const bool & isActive() const;

  bool isLogX() const;
  bool isLogY() const;

  void setLogX(bool l);
  void setLogY(bool l);
};

#endif
