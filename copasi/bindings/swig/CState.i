// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CState.i,v $ 
//   $Revision: 1.6.16.4 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2008/11/18 10:37:24 $ 
// End CVS Header 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include <limits>
#include "model/CState.h"

%}


%ignore CStateTemplate::getEntities() const;
%ignore CStateTemplate::beginIndependent() const;
%ignore CStateTemplate::endIndependent() const;
%ignore CStateTemplate::beginDependent() const;
%ignore CStateTemplate::endDependent() const;
%ignore CStateTemplate::beginFixed() const;
%ignore CStateTemplate::endFixed() const;
%ignore CState::getEntities() const;
%ignore CState::beginIndependent() const;
%ignore CState::endIndependent() const;
%ignore CState::beginDependent() const;
%ignore CState::endDependent() const;
%ignore CState::beginFixed() const;
%ignore CState::endFixed() const;
     
%ignore CState::check; // not implemented

#ifdef SWIGJAVA
// remove some const methods to get rid of warnings
%ignore CState::operator =;

#endif // SWIGJAVA


%include "model/CState.h"

%extend CStateTemplate
{
    CModelEntity* getEntity(unsigned C_INT32 index)
    {
        return (index<$self->size())?$self->getEntities()[index]:NULL;
    }

    CModelEntity* getIndependent(unsigned C_INT32 index)
    {
        if(index < $self->getNumIndependent())
        {
            return $self->beginIndependent()[index];
        }
        else
        {
            return NULL;
        }
    }

    CModelEntity* getDependent(unsigned C_INT32 index)
    {
        if(index < $self->getNumDependent())
        {
            return $self->beginDependent()[index];
        }
        else
        {
            return NULL;
        }
    }

    CModelEntity* getFixed(unsigned C_INT32 index)
    {
        if(index < $self->getNumFixed())
        {
            return $self->beginFixed()[index];
        }
        else
        {
            return NULL;
        }
    }
}

%extend CState
{
    C_FLOAT64 getIndependent(unsigned C_INT32 index)
    {
        if(index < $self->getNumIndependent())
        {
            return $self->beginIndependent()[index];
        }
        else
        {
            return std::numeric_limits<C_FLOAT64>::quiet_NaN();
        }
    }

    C_FLOAT64 getDependent(unsigned C_INT32 index)
    {
        if(index < $self->getNumDependent())
        {
            return $self->beginDependent()[index];
        }
        else
        {
            return std::numeric_limits<C_FLOAT64>::quiet_NaN();
        }
    }

    C_FLOAT64 getFixed(unsigned C_INT32 index)
    {
        if(index < $self->getNumFixed())
        {
            return $self->beginFixed()[index];
        }
        else
        {
            return std::numeric_limits<C_FLOAT64>::quiet_NaN();
        }
    }
}


