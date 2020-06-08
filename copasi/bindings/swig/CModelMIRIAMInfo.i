// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the 
// University of Virginia, University of Heidelberg, and University 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and University of 
// of Connecticut School of Medicine. 
// All rights reserved. 

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., University of Heidelberg, and The University 
// of Manchester. 
// All rights reserved. 




%ignore CRDFTriplet::operator bool;
%ignore CRDFTriplet::operator <;

%{

#include "copasi/MIRIAM/CMIRIAMResource.h"
#include "copasi/MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFNode.h"
#include "copasi/MIRIAM/CRDFObject.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CRDFSubject.h"
#include "copasi/MIRIAM/CRDFTriplet.h"
#include "copasi/MIRIAM/CModelMIRIAMInfo.h"

%}

%ignore CMIRIAMInfo::getCreators() const;
%ignore CMIRIAMInfo::getReferences() const;
%ignore CMIRIAMInfo::getModifications() const;
%ignore CMIRIAMInfo::getBiologicalDescriptions() const;

%ignore CMIRIAMResources::updateMIRIAMResources(CProcessReport * pProcessReport);
%ignore CMIRIAMResourceObject::CMIRIAMResourceObject(CRDFNode * pNode);
%ignore CMIRIAMResourceObject::setNode;
%ignore CRDFGraph::getAboutNode;
%ignore CRDFGraph::getNameSpaceMap;
%ignore CRDFGraph::getBlankNodeMap;
%ignore CRDFGraph::getLocalResourceNodeMap;
%ignore CRDFGraph::getRemoteResourceNodes;
%ignore CRDFGraph::addTriplet;
%ignore CRDFGraph::removeTriplet;
%ignore CRDFGraph::destroyUnreferencedNode;
%ignore CRDFGraph::moveTriplet;
%ignore CRDFGraph::getTriplets;
%ignore CRDFGraph::getIncomingTriplets;
%ignore CRDFGraph::getParentSubjects;
%ignore CRDFGraph::getPredicatePath;
%ignore CRDFGraph::createAboutNode;

%ignore CRDFTriplet::CRDFTriplet;
%ignore CRDFTriplet::pSubject;
%ignore CRDFTriplet::Predicate;
%ignore CRDFTriplet::pObject;

%include "MIRIAM/CMIRIAMResource.h"
%include "MIRIAM/CRDFGraph.h"
#include "copasi/MIRIAM/CRDFNode.h"
#include "copasi/MIRIAM/CRDFObject.h"
#include "copasi/MIRIAM/CRDFPredicate.h"
#include "copasi/MIRIAM/CRDFSubject.h"
%include "MIRIAM/CRDFTriplet.h"
%include "MIRIAM/CModelMIRIAMInfo.h"



