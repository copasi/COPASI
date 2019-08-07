// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "copasi/trajectory/CTimeSeries.h"
  
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
        if(CRootContainer::getDatamodelList()->size() > 0 && &(*CRootContainer::getDatamodelList())[0] != NULL)
        {
          const CDataModel* pDatamodel=&(*CRootContainer::getDatamodelList())[0];
          result=self->getSBMLId((size_t)variable,pDatamodel);
        }
        return result;
    }
#endif // SWIGJAVA || CSHARP
};


