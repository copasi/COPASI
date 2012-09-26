// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "trajectory/CTimeSeries.h"
  
%}


%include "trajectory/CTimeSeries.h"


%extend CTimeSeries{

#if (defined SWIGJAVA || defined SWIGCSHARP)
    // needed for CellDesigner
    std::string getSBMLId(const unsigned C_INT32 & variable) const
    {
        std::cerr << "Calling getSBMLId(index) for instances of CTimeSeries is obsolete, please use getSBMLId(index,datamodel) instead." << std::endl;
        // we do this for the first model
        std::string result("");
        if(CCopasiRootContainer::getDatamodelList()->size() > 0 && (*CCopasiRootContainer::getDatamodelList())[0] != NULL)
        {
          const CCopasiDataModel* pDatamodel=(*CCopasiRootContainer::getDatamodelList())[0];
          result=self->getSBMLId((size_t)variable,pDatamodel);
        }
        return result;
    }
#endif // SWIGJAVA || CSHARP
};


