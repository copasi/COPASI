/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/COutputDefinitionVector.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:30:41 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
