// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CTimeSeries.i,v $ 
//   $Revision: 1.4.32.3 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2011/09/08 15:40:31 $ 
// End CVS Header 

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "trajectory/CTimeSeries.h"
  
%}


%include "trajectory/CTimeSeries.h"


%extend CTimeSeries{

#ifdef SWIGJAVA
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
#endif // SWIGJAVA
};


