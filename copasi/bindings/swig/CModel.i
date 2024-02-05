// Copyright (C) 2019 - 2024 by Pedro Mendes, Rector and Visitors of the 
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

#include <copasi/utilities/CUnitComponent.h>
#include <copasi/utilities/CUnit.h>
#include <copasi/utilities/CValidatedUnit.h>
#include <copasi/utilities/CUnitValidator.h>
#include "copasi/math/CMathObject.h"
#include "copasi/math/CMathEvent.h"
#include "copasi/math/CMathDependencyGraph.h"
#include "copasi/math/CMathReaction.h"
#include "copasi/math/CMathDelay.h"
#include "copasi/math/CMathHistory.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"
#include <copasi/model/CModelExpansion.h>

%}

%template(ObjectStdVector) std::vector<CDataObject*>;
typedef std::vector<CDataObject*> ObjectStdVector;
%template(StringUnitMap) std::map< std::string, CUnit >;
typedef std::map< std::string, CUnit > StringUnitMap;
%template(StringDoubleMap) std::map< std::string, double >;
typedef std::map< std::string, double > StringDoubleMap;

%ignore CUnit::getSymbolComponents;
%ignore CUnit::SymbolComponent;
%rename(mul)             CUnit::operator*;
%rename(isEqual)         CUnit::operator==;
%rename(isEqual)         CUnitComponent::operator==;


%ignore CModel::getInitialUpdateSequence;
%ignore CModel::getTransientUpdateSequence;
%ignore CModel::load;
%ignore CModel::compileIfNecessary(CProcessReport* pProcessReport);
%ignore CModel::forceCompile(CProcessReport* pProcessReport);
%ignore CModel::ModelTypeNames;
%ignore CModel::appendDependentModelObjects;
%ignore CModel::appendDependentReactions;
%ignore CModel::appendDependentMetabolites;
%ignore CModel::appendDependentCompartments;
%ignore CModel::appendDependentModelValues;
%ignore CModel::appendDependentEvents;
%ignore CModel::removeDependentModelObjects;
%ignore CModel::getUptoDateObjects;


%ignore CMathContainer::relocateValue;
%ignore CMathContainer::relocateObject;
%ignore CMathHistoryCore::array() const;
// issue 2225: C_INT is either int or long depending on
// architecture, but we need it to be the same for universal
// bindings
%ignore CMathContainer::processRoots(const bool & equality,
         const CVector< C_INT > & rootsFound);
%ignore CMathContainer::processRoots(const CVector< C_INT > & rootsFound);

%rename(assign) CMathHistoryCore::operator =;

%ignore CMathContainer::getValues() const;
%ignore CMathContainer::getInitialState() const;
%ignore CMathContainer::getReactions() const;
%ignore CModel::getActiveModelParameterSet() const;
%ignore CModel::getMathContainer() const;
%ignore CCopasiParameterGroup::getElementTemplates() const;


// according to Stefan, the method to calculate the elasticities is no longer used
// and might actually not work at all
%ignore CModel::calculateElasticityMatrix(const C_FLOAT64&,const C_FLOAT64&);
%ignore CModel::getModelParameterSet() const;
%ignore CModel::getMetabolites() const;
%ignore CModel::getMetabolitesX() const;
%ignore CModel::getModelValues() const;
%ignore CModel::getReactions() const;
%ignore CModel::getEvents() const;
%ignore CModel::getCompartments() const;
//%ignore CModel::getStateTemplate() const;
%ignore CModel::processQueue;
%ignore CModel::processRoots;
%ignore CModel::calculateDerivatives;
%ignore CModel::calculateDerivativesX;
%ignore CModel::getListOfInitialRefreshes;
%ignore CModel::getListOfSimulatedRefreshes;
%ignore CModel::getListOfNonSimulatedRefreshes;
%ignore CModel::getListOfConstantRefreshes;
%ignore CModel::buildInitialRefreshSequence;
%ignore CModel::getRootFinders;
%ignore CModel::getL;
%ignore CModel::getModelParameterSets() const;

// suppress warnings on nested structures
%warnfilter(325) CLinkMatrixView;

#ifdef SWIGR
// since enums in R are mapped to strings, it seems to confuse swig
// if a string is passed to one of the setXXXUnit methods in CModel
// because it doesn't know whether to pass it on as a string or to translate it
// to the enum
%rename (setTimeUnitFromString) CModel::setTimeUnit(const std::string & name);
%rename (setVolumeUnitFromString) CModel::setVolumeUnit(const std::string & name);
%rename (setAreaUnitFromString) CModel::setAreaUnit(const std::string & name);
%rename (setLengthUnitFromString) CModel::setLengthUnit(const std::string & name);
%rename (setQuantityUnitFromString) CModel::setQuantityUnit(const std::string & name);
#endif // SWIGR

%ignore operator<;
%ignore   CUnitComponent::CUnitComponent(CBaseUnit::Kind kind = CBaseUnit::item,
                 double multiplier = 1,
                 int scale = 0,
                 double exponent = 1,
                 bool isMultiplierAvogadro = false);
%ignore CUnitComponent::getKind;
%ignore CUnitComponent::setKind;
%ignore operator=; 

%template(CUnitStdVector) std::vector<CUnit>;
%template(CValidatedUnitStdVector) std::vector<CValidatedUnit>;

%include <copasi/utilities/CUnitComponent.h>
%include <copasi/utilities/CUnit.h>
%include <copasi/utilities/CValidatedUnit.h>
%include <copasi/utilities/CUnitValidator.h>
%include "copasi/math/CMathObject.h"
%include "copasi/math/CMathEvent.h"
%include "copasi/math/CMathDependencyGraph.h"
%include "copasi/math/CMathReaction.h"
%include "copasi/math/CMathDelay.h"
%include "copasi/math/CMathHistory.h"
%include "copasi/math/CMathContainer.h"

%include "model/CModel.h"



%catches(CCopasiException) CModel::compile();
%catches(CCopasiException) CModel::compileEvents();
%catches(CCopasiException) CModel::compileIfNecessary;
%catches(CCopasiException) CModel::convert2NonReversible;
%catches(CCopasiException) CModel::initializeMetabolites;

%extend CModel
{
   
   bool setQuantityUnit(const std::string & name)
   {
     return self->setQuantityUnit(name, CCore::Framework::Concentration);
   }
   
   /**
    *  Get the number of compartments 
    *  @return C_INT32 getCompartments().size()
    */
   unsigned C_INT32 getNumCompartments() const
   {
     return (unsigned C_INT32)self->getCompartments().size();
   }
   
   /**
    *  Get the number of reactions
    *  @return C_INT32 getReactions().size()
    */
   unsigned C_INT32 getNumReactions() const
   {
     return (unsigned C_INT32)self->getReactions().size();
   }
   
   CReaction* getReaction(unsigned C_INT32 index)
   {
     if (index >= self->getReactions().size())
       return NULL;
     try
     {
       return &self->getReactions()[index];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   CReaction* getReaction(const std::string& name)
   {
     try
     {
       return &self->getReactions()[name];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   CCompartment* getCompartment(unsigned C_INT32 index)
   {
     if (index >= self->getCompartments().size())
       return NULL;
   
     try
     {
       return &self->getCompartments()[index];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   CCompartment* getCompartment(const std::string& name)
   {
     try
     {
       return &self->getCompartments()[name];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   
   CMetab* getMetabolite(unsigned C_INT32 index)
   {  
     if (index >= self->getMetabolites().size())
       return NULL;
   
     try
     {
       return &self->getMetabolites()[index];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   CMetab* getMetabolite(const std::string& name)
   {  
     return $self->findMetabByName(name);
   }
   
   CModelValue* getModelValue(unsigned C_INT32 index)
   {
     if (index >= self->getModelValues().size())
       return NULL;
   
     try
     {
       return &self->getModelValues()[index];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   const CMoiety* getMoiety(unsigned C_INT32 index)
   {
     if (index >= self->getMoieties().size())
       return NULL;
   
     try
     {
       return &self->getMoieties()[index];
     }
     catch (...)
     {
       return NULL;
     }
   }
   
   bool forceCompile()
   {
     return $self->forceCompile(NULL);
   }
   
   bool compileIfNecessary()
   {
     return $self->compileIfNecessary(NULL);
   }
   
   void updateInitialValues(const std::vector<CDataObject*>& v, bool refreshParameterSet=true)
   {
     std::set<const CDataObject*> changedObjects;
     changedObjects.insert(v.begin(),v.end());
		 
		 $self->updateInitialValues(changedObjects, refreshParameterSet);
   };
   
   CModelValue* getModelValue(const std::string& name)
   {
     try
     {
       return &$self->getModelValues()[name];
     }
     catch(...)
     {
       return NULL;
     }
   }
   
   CEvent* getEvent(const std::string& name)
   {
     try
     {
       return &$self->getEvents()[name];
     }
     catch(...)
     {
       return NULL;
     }
   }
   
   // for backwards compatibility
   unsigned C_INT32 getNumIndependentMetabs() const 
   {
     std::cerr << "Calling getNumIndependentMetabs on CModel instances is obsolete, please use getNumIndependentReactionMetabs instead." << std::endl;
     return (unsigned C_INT32)$self->getNumIndependentReactionMetabs();
   }
   
   // for backwards compatibility
   unsigned C_INT32 getNumDependentMetabs() const 
   {
     std::cerr << "Calling getNumDependentMetabs on CModel instances is obsolete, please use getNumDependentReactionMetabs instead." << std::endl;
     return (unsigned C_INT32)$self->getNumDependentReactionMetabs();
   }
   
   // for backward compatibility
   void setComments(const std::string& notes)
   {
     std::cerr << "Calling setComments on CModel instances is obsolete, please use setNotes instead." << std::endl;
     self->setNotes(notes);
   }
   
   // for backward compatibility
   const std::string& getComments() const
   {
     std::cerr << "Calling getComments on CModel instances is obsolete, please use getNotes instead." << std::endl;
     return self->getNotes();
   }
   
   // more convenience methods
   unsigned C_INT32 getNumEvents() const
   {
     return (unsigned C_INT32)$self->getEvents().size();
   }
   
   CEvent* getEvent(unsigned C_INT32 index)
   {
     if (index >= self->getEvents().size())
       return NULL;
   
     try
     {
       return &$self->getEvents()[index];
     }
     catch(...)
     {
       return NULL;
     }
   
   }
}


#if defined(SWIGPYTHON) || defined (SWIGRUBY)

%feature("flatnested", "1");

%rename (CModelExpansion_SetOfModelElements) CModelExpansion::SetOfModelElements;
%rename (CModelExpansion_ElementsMap) CModelExpansion::ElementsMap;
#endif

%include <copasi/model/CModelExpansion.h>

#if defined(SWIGPYTHON) || defined (SWIGRUBY)

%feature("flatnested", "0");
#endif
