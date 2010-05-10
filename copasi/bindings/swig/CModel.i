// Begin CVS Header 
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/bindings/swig/CModel.i,v $ 
//   $Revision: 1.16.2.1 $ 
//   $Name:  $ 
//   $Author: gauges $ 
//   $Date: 2010/05/10 15:33:43 $ 
// End CVS Header 

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

%{

#include "model/CModel.h"

%}

%template(ObjectStdVector) std::vector<CCopasiObject*>;
typedef std::vector<CCopasiObject*> ObjectStdVector;

%ignore CModel::compileIfNecessary(CProcessReport* pProcessReport);
%ignore CModel::forceCompile(CProcessReport* pProcessReport);
%ignore CModel::VolumeUnitNames;
%ignore CModel::AreaUnitNames;
%ignore CModel::LengthUnitNames;
%ignore CModel::TimeUnitNames;
%ignore CModel::QuantityUnitOldXMLNames;
%ignore CModel::QuantityUnitNames;
%ignore CModel::ModelTypeNames;
// according to Stefan, the method to calculate the elasticities is no longer used
// and might actually not work at all
%ignore CModel::calculateElasticityMatrix(const C_FLOAT64&,const C_FLOAT64&);
%ignore CModel::getMetabolites() const;
%ignore CModel::getMetabolitesX() const;
%ignore CModel::getModelValues() const;
%ignore CModel::getReactions() const;
%ignore CModel::getEvents() const;
%ignore CModel::getCompartments() const;
%ignore CModel::getStateTemplate() const;

%include "model/CModel.h"

%extend CModel
{
    /**
     *  Get the number of compartments 
     *  @return C_INT32 getCompartments().size()
     */
    unsigned C_INT32 getNumCompartments() const
    {
      return self->getCompartments().size();
    }

    /**
     *  Get the number of reactions
     *  @return C_INT32 getReactions().size()
     */
    unsigned C_INT32 getNumReactions() const
    {
      return self->getReactions().size();
    }

    CReaction* getReaction(unsigned C_INT32 index)
    {
        return self->getReactions()[index];
    }

    CCompartment* getCompartment(unsigned C_INT32 index)
    {
        return self->getCompartments()[index];
    }

    CMetab* getMetabolite(unsigned C_INT32 index)
    {
        return self->getMetabolites()[index];
    }

    CModelValue* getModelValue(unsigned C_INT32 index)
    {
        return self->getModelValues()[index];
    }

    CMoiety* getMoiety(unsigned C_INT32 index)
    {
        return self->getMoieties()[index];
    }

    bool forceCompile()
    {
        return $self->forceCompile(NULL);
    };

    bool compileIfNecessary()
    {
        return $self->compileIfNecessary(NULL);
    };

    void applyInitialValues()
    {
        $self->compileIfNecessary(NULL);
        $self->applyInitialValues();
        $self->updateNonSimulatedValues();
    }

    void updateInitialValues(const std::vector<CCopasiObject*>& v)
    {
        std::set<const CCopasiObject*> changedObjects;
        changedObjects.insert(v.begin(),v.end());
        std::vector<Refresh*> refreshes=$self->buildInitialRefreshSequence(changedObjects);
        std::vector<Refresh*>::iterator refreshIt = refreshes.begin(), refreshEndit = refreshes.end();
        while (refreshIt != refreshEndit)
            (**refreshIt++)();
    };

    CModelValue* getModelValue(const std::string& name)
    {
        return $self->getModelValues()[name];
    }

    // for backwards compatibility
   unsigned C_INT32 getNumIndependentMetabs() const 
   {
        return $self->getNumIndependentReactionMetabs();
   }

    // for backwards compatibility
   unsigned C_INT32 getNumDependentMetabs() const 
   {
        return $self->getNumDependentReactionMetabs();
   }
}



