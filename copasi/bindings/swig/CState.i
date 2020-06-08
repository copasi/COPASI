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

#include <limits>
#include "copasi/model/CState.h"

%}


%ignore CStateTemplate::getEntities() const;
%ignore CStateTemplate::beginIndependent() const;
%ignore CStateTemplate::endIndependent() const;
%ignore CStateTemplate::beginDependent() const;
%ignore CStateTemplate::endDependent() const;
%ignore CStateTemplate::beginFixed() const;
%ignore CStateTemplate::endFixed() const;
%ignore CStateTemplate::getEntities();
%ignore CStateTemplate::beginIndependent();
%ignore CStateTemplate::endIndependent();
%ignore CStateTemplate::beginDependent();
%ignore CStateTemplate::endDependent();
%ignore CStateTemplate::beginFixed();
%ignore CStateTemplate::endFixed();
%ignore CStateTemplate::reorder;
%ignore CStateTemplate::setUserOrder;
%ignore CState::getEntities() const;
%ignore CState::beginIndependent() const;
%ignore CState::endIndependent() const;
%ignore CState::beginDependent() const;
%ignore CState::endDependent() const;
%ignore CState::beginFixed() const;
%ignore CState::endFixed() const;
%ignore CState::getEntities();
%ignore CState::beginIndependent();
%ignore CState::endIndependent();
%ignore CState::beginDependent();
%ignore CState::endDependent();
%ignore CState::beginFixed();
%ignore CState::endFixed();
     
%ignore CState::check; // not implemented

#if (defined SWIGJAVA || defined SWIGCSHARP)
// remove some const methods to get rid of warnings
%ignore CState::operator =;

#endif // SWIGJAVA || CSHARP


%include "model/CState.h"

%extend CStateTemplate
{
    const CModelEntity *const getEntity(unsigned C_INT32 index)
    {
        return (index<$self->size())?$self->getEntities()[index]:NULL;
    }

    const CModelEntity *const getIndependent(unsigned C_INT32 index)
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

    const CModelEntity *const getDependent(unsigned C_INT32 index)
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

    const CModelEntity *const getFixed(unsigned C_INT32 index)
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
/*
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

  void setIndependent(unsigned C_INT32 index, C_FLOAT64 val)
  {
    if(index < $self->getNumIndependent())
    {
      $self->beginIndependent()[index] = val;
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

  void setDependent(unsigned C_INT32 index, C_FLOAT64 val)
  {
    if(index < $self->getNumDependent())
    {
      $self->beginDependent()[index] = val;
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

  void setFixed(unsigned C_INT32 index, C_FLOAT64 val)
  {
    if(index < $self->getNumFixed())
    {
      $self->beginFixed()[index] = val;
    }
  }
}
*/

