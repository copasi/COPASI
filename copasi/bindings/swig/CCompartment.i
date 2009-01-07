// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CCompartment.i,v $ 
//   $Revision: 1.6 $ 
//   $Name:  $ 
//   $Author: shoops $ 
//   $Date: 2009/01/07 18:51:30 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "model/CCompartment.h"  
#include <assert.h>  
%}


#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CCompartment::getMetabolites() const;

#endif // SWIGJAVA

%include "model/CCompartment.h"

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
