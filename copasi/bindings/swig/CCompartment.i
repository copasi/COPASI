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

#include "copasi/model/CCompartment.h"  
#include <assert.h>  
%}

%ignore CCompartment::load;
%ignore CCompartment::getDeletedObjects;

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CCompartment::getMetabolites() const;

#endif // SWIGJAVA || CSHARP

%include "copasi/model/CCompartment.h"

%extend CCompartment{

    /**
     * This method is there for backwards compatibility and will be
     * removed eventually.
     */
    bool removeMetabolite(CMetab* metab)
    {
       CModel* pModel=dynamic_cast<CModel*>($self->getObjectParent()->getObjectParent());
       assert(pModel!=NULL);
       return pModel->removeMetabolite(metab->getKey());
    }
}
